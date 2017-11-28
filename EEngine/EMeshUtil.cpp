#include "EMeshUtil.h"
#include "EUtil.h"
#include "EMaterial.h"

namespace E3D
{
	EString ReadString(std::ifstream& in, EInt size)
	{
		EString ss;
		//读取一行
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
		//模型文件，首先获取默认路径
		in.open(GetPath(meshName).c_str(), std::ios_base::binary | std::ios_base::in);
		if (in.bad())
		{
			in.close();
			return nullptr;
		}

		EString name = GetNameFromPath(meshName);
		//加载材质
		ParseMaterialScript(name + ".meterial");

		EObject4D* head = nullptr;
		{
			//网格头信息
			EUShort HEADER = ReadShort(in);
			//网格版本号
			EString Version = ReadString(in);

			//网格标记
			EUShort MESH = ReadChunk(in);
			//蒙皮骨骼
			EBool SkekeallyAnimated = ReadBool(in);

			//子网格标记
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

				//设置坐标
				curObject->worldPosition = worldPos;
				curObject->scale = scale;

				//材质信息
				EString Materia = ReadString(in);
				//读取多边形的材质
				curObject->materialName = Materia;

				//顶点是否共享
				EBool UseSharedVertices = ReadBool(in);

				//无符号顶点数量
				EUInt indexCount = ReadInt(in);
				//获取模型多边形个数
				curObject->polyonNumber = indexCount / 3;
				curObject->polyonList.reserve(indexCount / 3);

				//索引是否32位
				EBool indexes32Bit = ReadBool(in);
				if (indexes32Bit)
				{
					//存储面的顶点索引
					std::vector<EUInt> faceVertexIndices = ReadArray<EUInt>(in, indexCount);
					//读取模型顶点索引
					indexArray.assign(faceVertexIndices.begin(), faceVertexIndices.end());
				}
				else
				{
					//存储面顶点索引
					std::vector<EUShort> faceVertexIndices = ReadArray<EUShort>(in, indexCount);
					//读取模型顶点索引
					indexArray.assign(faceVertexIndices.begin(), faceVertexIndices.end());
				}

				//网格几何信息
				EUShort GEOMETRY = ReadChunk(in);

				//顶点数量
				EUInt vertexCount = ReadInt(in);

				//模型顶点个数
				curObject->vertexNumber = vertexCount;
				curObject->localList.reserve(vertexCount);
				curObject->transformList.reserve(vertexCount);

				//网格几何顶点申明
				EUShort GEOMETRY_VERTEX_DECLARATION = ReadChunk(in);
				//网格几何顶点元素
				EUShort GEOMETRY_VERTEX_ELEMENT = ReadChunk(in);
				while (!in.eof() && GEOMETRY_VERTEX_ELEMENT == M_GEOMETRY_VERTEX_ELEMENT)
				{
					//绑定资源缓冲区
					EUShort source = ReadShort(in);
					//顶点类型
					EUShort type = ReadShort(in);
					//顶点语义
					EUShort semantic = ReadShort(in);
					//在缓存中的偏移值
					EUShort offset = ReadShort(in);
					//颜色和纹理坐标索引值
					EUShort index = ReadShort(in);
					GEOMETRY_VERTEX_ELEMENT = ReadChunk(in):
				}

				//顶点缓存
				EUShort GEOMETRY_VETTEX_BUFFER = GEOMETRY_VERTEX_ELEMENT;
				//把索引绑定到该缓存中
				EUShort bindIndex = ReadShort(in);

				//每个顶点大小必须与索引的声明保持一致
				EUShort vertexSize = ReadShort(in);

				//几何顶点缓存数据
				EUShort GEOMETRY_VERTEX_BUFFER_DATA = ReadChunk(in);

				EInt vertexNum = vertexSize / sizeof(EFloat);
				//数据缓存大小
				EInt bufferSize = vertexCount * vertexNum;

				//读取顶点数据 179页

			}
		}

	}
}