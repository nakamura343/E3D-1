#include "EGraphics.h"
#include "EWindow.h"
#include "EMeshUtil.h"
#include "EUtil.h"
#include "EGame.h"
#include "res/resource.h"

using namespace E3D;

int WINAPI WinMain(
	HINSTANCE hInstance,		//��ǰʵ���ľ��
	HINSTANCE hPrevInstance,//��ǰʵ���ľ��
	LPSTR lpCmdLine,		//������
	int nCmdShow			//��ʾ״̬
)
{
	InitLog("E3D.Log");

	Log("Init Graphics...");
	EGraphics::initGraphics(hInstance);
	Log("Graphics Load Successed!");

	EGameWindow::GWindow = new EGameWindow("E3D[3DTankWar]", hInstance);
	EGameWindow::GWindow->showWindow(true);

	//������Ϸ��Сͼ��
	HWND hwnd = EGameWindow::GWindow->getHWnd();
	LONG iconID = (LONG)LoadIcon(::GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_TANKWAR));
	::SetClassLong(hwnd, GCL_HICON, iconID);

	EGame* game = new EGame;
	EGameWindow::GWindow->setCanvasListener(game);
	EGameWindow::GWindow->addInputListener(game);
	EGameWindow::GWindow->startLoop();

	Log("Shutdown Graphics...");
	EGraphics::shutdownGraphics();

	CloseLog();

	return;
}
