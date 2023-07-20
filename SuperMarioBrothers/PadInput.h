#pragma once
#include "DxLib.h"

#define BUTTONS 16
#define MARGIN 32767*0.25

class PadInput
{
private:
	static char NowKey[BUTTONS];  //今回の入力キー
	static char OldKey[BUTTONS];  //前回の入力キー
	static int OldX, OldY;
	static XINPUT_STATE Input;
	static int InputX, InputY;
	static int FlgX, FlgY;

	/*todo  消す  */
	static int nowKey, oldKey;
	/*ここまで*/

public:
	static void UpdateKey();  //入力キー取得
	static void SticControl();  //スティック入力取得
	static int GetThumbLX() { return Input.ThumbLX; }
	static int GetThumbLY() { return Input.ThumbLY; }
	static int GetFlgX() { return FlgX; }
	static int GetFlgY() { return FlgY; }

	////ボタンを押した瞬間
	//static bool OnClick(int inputKey)
	//{
	//	bool ret = (NowKey[inputKey] == 1 && OldKey[inputKey] == 0);

	//	return ret;
	//}
	////ボタンを押している間
	//static bool OnPressed(int inputKey)
	//{
	//	bool ret = (NowKey[inputKey] == 1);
	//	return ret;
	//}

	////ボタンを離した瞬間
	//static bool OnRelese(int inputKey)
	//{
	//	bool ret = (OldKey[inputKey] == 1 && NowKey[inputKey] == 0);

	//	return ret;
	//}

	//ボタンを押した瞬間だけを判定
	static bool OnClick(int inputKey)
	{
		int keyFlag = nowKey & ~oldKey;
		bool ret = (keyFlag & inputKey);
		return ret;
	}

	//ボタンを押している間
	static bool OnPressed(int inputKey)
	{
		bool ret = (nowKey & inputKey);
		return ret;
	}

	//ボタンを離した瞬間
	static bool OnRelese(int inputKey)
	{
		int keyFlag = oldKey & ~nowKey;
		bool ret = (keyFlag & inputKey);
		return ret;
	}
};

