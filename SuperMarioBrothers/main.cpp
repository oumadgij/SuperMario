#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"
#include "Define.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);  //画面モードの変更
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //描画範囲を設定

	SceneManager SceneMng(new GameMain());

	while ((SceneMng.Update() != nullptr)&&(ProcessMessage() == 0)&&(PadInput::OnClick(XINPUT_BUTTON_BACK) == 0))
	{
		ClearDrawScreen();

		PadInput::UpdateKey();

		SceneMng.Draw();

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}