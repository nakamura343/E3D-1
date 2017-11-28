#include "EMeshUtil.h"
#include "EUtil.h"
#include "EMaterial.h"

namespace E3D
{
	EString ReadString(std::ifstream& in, EInt size)
	{
		EString ss;
		//��ȡһ��
		if (size == -1)
		{
			EChar c;
			while (in.read(&c, sizeof(EChar)) && c != '\n' && c != '\r')
				ss += c;
		}
		else
		{
			EChar c[256];
			in.read(c, sizeof(EChar) * size);
			ss.append(c);
		}

		return ss;
	}

	EUShort ReadChunk(std::ifstream& in)
	{
		EUShort id;
		in.read((EChar*)& id, sizeof(EUShort));

		EUInt length;
		in.read((EChar*)& length, sizeof(EUInt));

		return id;
	}

	EBool ReadBool(std::ifstream& in)
	{
		EBool re = false;
		in.read((EChar*)& re, sizeof(EBool));
		return re;
	}

	EUInt ReadInt(std::ifstream& in)
	{
		EUInt re;
		in.read((char*)& re, sizeof(EUInt));
		return re;
	}

	EUShort ReadShort(std::ifstream& in)
	{
		EUShort re;
		in.read((EChar*)& re, sizeof(EUShort));
		return re;
	}

	EObject4D* LoadOgreMesh(const EString& meshName, const EVector4D& worldPos, const EVector4D& scale)
	{
		std::ifstream in;
		//ģ���ļ������Ȼ�ȡĬ��·��
		in.open(GetPath(meshName).c_str(), std::ios_base::binary | std::ios_base::in);
		if (in.bad())
		{
			in.close();
			return nullptr;
		}

		EString name = GetNameFromPath(meshName);
		//���ز���
		ParseMaterialScript(name + ".meterial");

		EObject4D* head = nullptr;
		{
			//����ͷ��Ϣ
			EUShort HEADER = ReadShort(in);
			//����汾��
			EString Version = ReadString(in);

			//������
			EUShort MESH = ReadChunk(in);
			//��Ƥ����
			EBool SkekeallyAnimated = ReadBool(in);

			//��������
			EUShort SUBMESH = ReadChunk(in);
			EObject4D* curObject = nullptr;
			while (!in.eof() && (SUBMESH == (EUShort)OGREMESHID::M_SUBMESH))
			{
				std::vector<EUInt> indexArray;
				std::vector<EFloat> vertexArray;

				if (head == nullptr)
				{
					head = new EObject4D;
					curObject = head;
				}
				else
				{
					curObject->nextObject = new EObject4D;
					curObject = curObject->nextObject;
				}

				curObject->name = name;
				curObject->state = EOBJECT_STATE_ACTIVE | EOBJECT_STATE_VISIBLE;

				//��������
				curObject->worldPosition = worldPos;
				curObject->scale = scale;

				//������Ϣ
				EString Materia = ReadString(in);
				//��ȡ����εĲ���
				curObject->materialName = Materia;

				//�����Ƿ���
				EBool UseSharedVertices = ReadBool(in);

				//�޷��Ŷ�������
				EUInt indexCount = ReadInt(in);
				//��ȡģ�Ͷ���θ���
				curObject->polyonNumber = indexCount / 3;
				curObject->polyonList.reserve(indexCount / 3);

				//�����Ƿ�32λ
				EBool indexes32Bit = ReadBool(in);
				if (indexes32Bit)
				{
					//�洢��Ķ�������
					std::vector<EUInt> faceVertexIndices = ReadArray<EUInt>(in, indexCount);
					//��ȡģ�Ͷ�������
					indexArray.assign(faceVertexIndices.begin(), faceVertexIndices.end());
				}
				else
				{
					//�洢�涥������
					std::vector<EUShort> faceVertexIndices = ReadArray<EUShort>(in, indexCount);
					//��ȡģ�Ͷ�������
					indexArray.assign(faceVertexIndices.begin(), faceVertexIndices.end());
				}

				//���񼸺���Ϣ
				EUShort GEOMETRY = ReadChunk(in);

				//��������
				EUInt vertexCount = ReadInt(in);

				//ģ�Ͷ������
				curObject->vertexNumber = vertexCount;
				curObject->localList.reserve(vertexCount);
				curObject->transformList.reserve(vertexCount);

				//���񼸺ζ�������
				EUShort GEOMETRY_VERTEX_DECLARATION = ReadChunk(in);
				//���񼸺ζ���Ԫ��
				EUShort GEOMETRY_VERTEX_ELEMENT = ReadChunk(in);
				while (!in.eof() && GEOMETRY_VERTEX_ELEMENT == (EUShort)OGREMESHID::M_GEOMETRY_VERTEX_ELEMENT)
				{
					//����Դ������
					EUShort source = ReadShort(in);
					//��������
					EUShort type = ReadShort(in);
					//��������
					EUShort semantic = ReadShort(in);
					//�ڻ����е�ƫ��ֵ
					EUShort offset = ReadShort(in);
					//��ɫ��������������ֵ
					EUShort index = ReadShort(in);
					GEOMETRY_VERTEX_ELEMENT = ReadChunk(in);
				}

				//���㻺��
				EUShort GEOMETRY_VETTEX_BUFFER = GEOMETRY_VERTEX_ELEMENT;
				//�������󶨵��û�����
				EUShort bindIndex = ReadShort(in);

				//ÿ�������С��������������������һ��
				EUShort vertexSize = ReadShort(in);

				//���ζ��㻺������
				EUShort GEOMETRY_VERTEX_BUFFER_DATA = ReadChunk(in);

				EInt vertexNum = vertexSize / sizeof(EFloat);
				//���ݻ����С
				EInt bufferSize = vertexCount * vertexNum;

				//��ȡ��������
				vertexArray = ReadArray<EFloat>(in, bufferSize);

				for (EInt i = 0; i < (EInt)vertexArray.size(); i += vertexNum)
				{
					EVertex4D vex;
					//��������
					vex.x = vertexArray[i];
					vex.y = vertexArray[i + 1];
					vex.z = vertexArray[i + 2];

					//����UV
					vex.u = vertexArray[i + 6];
					vex.v = vertexArray[i + 7];

					curObject->localList.push_back(vex);
					curObject->transformList.push_back(vex);
				}

				for (EInt i = 0; i < curObject->polyonNumber; ++i)
				{
					EInt index = i * 3;
					EPolyon4D poly;
					poly.state = EPOLY_STATE_ACTIVE;
					poly.attribute = EPOLY_ATTR_VERTEX_NORMAL | EPOLY_ATTR_VERTEX_POSITION | EPOLY_ATTR_VERTEX_UV;
					poly.verIndex[0] = indexArray[index];
					poly.verIndex[1] = indexArray[index + 1];
					poly.verIndex[2] = indexArray[index + 2];

					//���ｫ�任��Ķ���ָ�뽻��ÿ������Σ���Ϊ�˷�ֹ�任֮�󶥵���������������Ķ�������
					poly.verList = &curObject->transformList;
					curObject->polyonList.push_back(poly);
				}

				//������λ��
				EUShort SUBMESH_OPERATION = ReadChunk(in);
				//��������
				EUShort operationType = ReadShort(in);

				SUBMESH = ReadChunk(in);
			}

			//�����Χ��
			EUShort MESH_BOUNDS = SUBMESH;
			if (MESH_BOUNDS == (EUShort)OGREMESHID::M_MESH_BOUNDS)
			{
				//��С��Χ�к�����Χ�м�����뾶
				std::vector<EFloat> bounds = ReadArray<EFloat>(in, 7);
				head->minBoundingBox = EVector4D(bounds[0], bounds[1], bounds[2]);
				head->maxBoundingBox = EVector4D(bounds[3], bounds[4], bounds[6]);
				head->avgRadius = (head->maxBoundingBox - head->minBoundingBox).length() / 2;

				EFloat minR = head->minBoundingBox.length();
				EFloat maxR = head->maxBoundingBox.length();
				head->maxRadius = maxR > minR ? maxR : minR;

				//�����������б�
				EUShort SUBMESH_NAME_TABLE = ReadChunk(in);
				if (SUBMESH_NAME_TABLE == (EUShort)OGREMESHID::M_SUBMESH_NAME_TABLE)
				{
					//�����������б�Ԫ��
					EUShort SUBMESH_NAME_TABLE_ELEMENT = ReadChunk(in);
					while (!in.eof() && SUBMESH_NAME_TABLE_ELEMENT == (EUShort)OGREMESHID::M_SUBMESH_NAME_TABLE_ELEMENT)
					{
						//���ֺ�����
						EShort index = ReadShort(in);
						EString name = ReadString(in);
						SUBMESH_NAME_TABLE_ELEMENT = ReadChunk(in);
					}
				}

			}
		}
		in.close();
		return head;
	}
}