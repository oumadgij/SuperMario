#include "DxLib.h"
#include "GameMain.h"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);  //âÊñ ÉÇÅ[ÉhÇÃïœçX
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager SceneMng(new GameMain());

	while ((SceneMng.Update() != nullptr)&&(ProcessMessage() == 0))
	{
		ClearDrawScreen();

		SceneMng.Draw();

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}