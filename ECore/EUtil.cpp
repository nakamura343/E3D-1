#include "EUtil.h"

namespace E3D
{
	std::ofstream* GLogStream = nullptr;

	bool InitLog(const EString& filename)
	{
		if (GLogStream == nullptr)
		{
			GLogStream = new std::ofstream();
			GLogStream->open(filename.c_str());
			if (GLogStream->good())
				return true;

			return false;
		}
		return true;
	}

	void Log(const EChar* string, ...)
	{
		if (GLogStream == nullptr)
			return;

		EChar buffer[256];

		//��֤���߶���Ϊ��
		if (!string || !GLogStream)
			return;

		va_list arglist; //�ɱ�����б�
		//������ջ�ϵĿɱ�Ĳ�����ӡ����ַ���
		va_start(arglist, string);
		vsprintf_s(buffer, string, arglist);
		va_end(arglist);

		EString info(buffer);
		//�����Ϣ��
		*GLogStream << info << std::endl;
		GLogStream->flush();
	}

	void CloseLog()
	{
		GLogStream->close();
		SafeDelete(GLogStream);
	}

}