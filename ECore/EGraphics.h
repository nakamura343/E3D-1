#pragma once

#include "ECommon.h"
#include <Windows.h>

//ͼ����Ⱦ�ײ��ʵ��
namespace E3D
{
	extern HINSTANCE GHInstace;

	//ͼƬ��װ������ͼƬʹ�õ�GDI+��ͼƬ��װ��
	//��������������з�װ����ƽ̨��صĶ�������
	class EBitmap
	{
	public:
		EInt width, height;

		EBitmap(const EString& filename);
		~EBitmap();

		inline EString getName() const { return name; }
		inline bool isValid() const { return valid; }
		EColor getPixel(EInt x, EInt y);
		inline EInt getHeight() const { return height; }
		inline EInt getWidth() const { return height; }

	private:
		EString		name;
		HBITMAP		hBitmap;
		BITMAP		bitmap;
		HDC			bitmapHDC;

	public:
		EColor		*pixels;
		EInt		pitch;
		EBool		valid;
	};




}