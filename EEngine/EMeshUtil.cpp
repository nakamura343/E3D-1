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
			while (!in.eof() && (SUBMESH == M_SUBMESH))
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
				while (!in.eof() && GEOMETRY_VERTEX_ELEMENT == M_GEOMETRY_VERTEX_ELEMENT)
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
					GEOMETRY_VERTEX_ELEMENT = ReadChunk(in):
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

				//��ȡ�������� 179ҳ

			}
		}

	}
}