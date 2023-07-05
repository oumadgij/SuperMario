#pragma once
#include "DxLib.h"

#define BUTTONS 16
#define MARGIN 32767*0.25

class PadInput
{
private:
	static char NowKey[BUTTONS];  //����̓��̓L�[
	static char OldKey[BUTTONS];  //�O��̓��̓L�[
	static int OldX, OldY;
	static XINPUT_STATE Input;
	static int InputX, InputY;
	static int FlgX, FlgY;

public:
	static void UpdateKey();  //���̓L�[�擾
	static void SticControl();  //�X�e�B�b�N���͎擾
	static int GetThumbLX() { return Input.ThumbLX; }
	static int GetThumbLY() { return Input.ThumbLY; }
	static int GetFlgX() { return FlgX; }
	static int GetFlgY() { return FlgY; }

	//�{�^�����������u��
	static bool OnClick(int inputKey)
	{
		bool ret = (NowKey[inputKey] == 1 && OldKey[inputKey] == 0);

		return ret;
	}
	//�{�^���������Ă����
	static bool OnPressed(int inputKey)
	{
		bool ret = (NowKey[inputKey] == 1);
		return ret;
	}

	//�{�^���𗣂����u��
	static bool OnRelese(int inputKey)
	{
		bool ret = (OldKey[inputKey] == 1 && NowKey[inputKey] == 0);

		return ret;
	}
};

