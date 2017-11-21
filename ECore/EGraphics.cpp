#include "EGraphics.h"
#include "EUtil.h"

namespace E3D
{
	EBitmap::EBitmap(const EString& filename)
		: name(filename)
		, pixels(nullptr)
	{
		//���ʽű������Ȼ�ȡĬ��·��
		hBitmap = (HBITMAP)::LoadImage(GHInstance, GetPath(filename).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (hBitmap != nullptr)
		{
			bitmapHDC = ::CreateCompatibleDC(nullptr);
			::SelectObject(bitmapHDC, (HGDIOBJ)hBitmap);
			::GetObject(hBitmap, sizeof(BITMAP), &bitmap);

			width = bitmap.bmWidth;
			height = bitmap.bmHeight;
			pitch = bitmap.bmHeight;
			valid = true;

			pixels = new EColor[width * height];
			for (EInt i = 0; i < getHeight(); ++i)
			{
				for (EInt j = 0; j < getWidth(); ++j)
				{
					COLORREF color = ::GetPixel(bitmapHDC, i, j);
					pixels[j * width + i] = EColor(GetRValue(color), GetGValue(color), GetBValue(color));
				}
			}
		}
	}

	//��������
	EBitmap::~EBitmap()
	{
		DeleteObject(hBitmap);
		DeleteObject(bitmapHDC);
		SafeDeleteArray(pixels);
	}

	//��ȡ����
	EColor EBitmap::getPixel(EInt x, EInt y)
	{
		return pixels[y * pitch + x];
	}

	HINSTANCE GHInstance;

	HBITMAP				EGraphics::GBufferedHandle;
	HBITMAP				EGraphics::GBufferedHDC;
	HBRUSH				EGraphics::GBgBrush;
	HPEN				EGraphics::GPen;
	HINSTANCE			EGraphics::GInstance;
	RECT				EGraphics::GBufferSize;
	DIBSECTION			EGraphics::GDIBSection;
	BYTE*				EGraphics::GDatas;
	EInt				EGraphics::GPitch;

	EFloat*				EGraphics::GZBuffer;

	//��ʼ����ͼϵͳ
	bool EGraphics::initGraphics(HINSTANCE hinstance)
	{
		GBufferedHDC = ::CreateCompatibleDC(nullptr);

		/////////////
		BITMAPINFO info						= {0};
		info.bmiHeader.biSize				= sizeof(info.bmiHeader);
		info.bmiHeader.biWidth = SCREEN_WIDTH;
		info.bmiHeader.biHeight = -SCREEN_HEIGHT;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biSizeImage = SCREEN_WIDTH * SCREEN_HEIGHT * 32 / 8;
		
		//����һ���ڴ�������ȡ������ָ��
		void* pBits = nullptr;
		GBufferedHandle = ::CreateDIBSection(GBufferedHDC, &info, DIB_RGB_COLORS, &pBits, nullptr, 0);
		::SelectObject(GBufferedHDC, GBufferedHandle);

		//�����dib.dsBm.bmBits����ָ��hdib������
		::GetObject(GBufferedHandle, sizeof(DIBSECTION), &GDIBSection);
		GDatas = (BYTE*)GDIBSection.dsBm.bmBits;
		GPitch = GDIBSection.dsBm.bmWidthBytes;

		//����ˢ������Ĵ�С
		::SetRect(&GBufferSize, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		//GPen = (HPEN)::GetStockObject(WHITE_PEN)
		GPen = ::CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		::SelectObject(GBufferedHDC, GPen);

		GBgBrush = ::CreateSolidBrush(RGB(0, 0, 0));
		::SelectObject(GBufferedHDC, GBgBrush);

		//��������
		HFONT hfnt = (HFONT)::GetStockObject(OEM_FIEXD_FONT);
		::SelectObject(GBufferedHDC, hfnt);
		//�������ֱ���Ϊ͸��ɫ
		::SetBkMode(GBufferedHDC, TRANSPARENT);

		GZBuffer = new EFloat[SCREEN_WIDTH * SCREEN_HEIGHT];
		memset(GZBuffer, 0, sizeof(EFloat) * SCREEN_WIDTH * SCREEN_HEIGHT);

		return;
	}

	//�رջ�ͼϵͳ
	void EGraphics::shutdownGraphics()
	{
		::DeleteObject(GPen);
		::DeleteObject(GBgBrush);
		::DeleteObject(GBufferedHandle);
		::DeleteDC(GBufferedHDC);
	}

	//��յ�ǰ����������������ɫ����Ϊ��ɫ
	void EGraphics::clearBuffer(const EColor& c)
	{
		::FillRect(GBufferedHDC, &GBufferSize, GBgBrush);
		//������Ȼ���
		//ע�⣬����meemsetֻ�ܶ�Int���͵�������г�ʼ��������ֱ��ʹ����Int����
		//��û��ʹ��float���ͣ�Ӧ��ʹ��float
		::memset(GZBuffer, 0, sizeof(EFloat) * SCREEN_WIDTH * SCREEN_HEIGHT);
	}

	//�ڵ�ǰ�������ڻ���һ����
	void EGraphics::drawLine(EInt x0, EInt y0, EInt x1, EInt y1, const EColor& c)
	{
		::SelectObject(GBufferedHDC, GetStockObject(DC_PEN));
		::SetDCPenColor(GBufferedHDC, RGB(c.r, c.g, c.b));
		
		::MoveToEx(GBufferedHDC, x0, y0, nullptr);
		::LineTo(GBufferedHDC, x1, y1);

		//::DeleteObject(hPen);
	}

	//�����ַ���
	void EGraphics::drawString(const EString& str, EInt x, EInt y, const EColor& c)
	{
		::SetTextColor(GBufferedHDC, RGB(c.r, c.g, c.b));
		::TextOut(GBufferedHDC, x, y, str.c_str(), str.lenght());
	}

	void EGraphics::fillTraignle(EInt x0, EInt y0, EInt y0, EInt x1, EInt y1, EInt x2, EInt y2, const Color& c)
	{

	}

	void EGraphics::enableSmoothingMode(EBool enable)
	{

	}

	//���Z���ֵ
	EBool EGraphics::checkZ(EInt x, EInt y, EFloat z)
	{
		//����ZӦ��ʹ��float�������洢�����ʹ��int���ͣ���ô�ᵼ�¾��ȶ�ʧ������������
		EInt index = y * SCREEN_WIDTH + x;
		EFloat divZ = 1.0f / z;
		
		//�����ǻ���1/Z���Ƚ�
		if (GZBuffer[index] > divZ)
			return false;

		GZBuffer[index] = divZ;
		return true;
	}

	void EGraphics::setPixel(EInt x, EInt y, /*EFloat z,*/const EColor& c)
	{
		//���ﱾ��Ӧ�ü���Zֵ�� ��Ϊ�˱����Image���صĶ�ȡ����Z�������˳���
		//��ˣ��ڵ���setPixel֮ǰӦ���checkZ������true�ٵ���setPixel

		BYTE* pSrcPix = GDatas + (GPitch * y);
		pSrcPix += x * 4;
		//��ɫ��ֵ����,�����죬͸����
		pSrcPix[0] = c.b;
		pSrcPix[1] = c.g;
		pSrcPix[2] = c.r;
		pSrcPix[3] = c.a;
	}

	EColor EGraphics::getPixel(EInt x, EInt y)
	{
		//ָ��ÿ�����ڴ�����ǰ�ƶ�һ������
		BYTE* pSrcPix = GDatas + (GPitch * y);
		pSrcPix += x * 4;
		return EColor(pSrcPix[2], pSrcPix[1], pSrcPix[0]);
	}

	//���Ѿ����ƺõĻ������ݽ���Graphics����Ļ�ϻ��ƣ�������ǰ����������Ϊ��һ��������
	void EGraphics::fillBuffer(HDC hdc)
	{
		::BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GBufferedHDC, 0, 0, SRCCOPY)
	}
}