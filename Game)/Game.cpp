#include "UIMaster.h"
#include "Camera.h"
using namespace sf;

int main()
{
	//закрывает консоль при запуске приложения
	HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);

	GameManager gameManager;
	Map map;
	UIMaster windowMaster;

	windowMaster.CreateMenu(map, gameManager);
	
	return 0;
}