#include "PadInput.h"

char PadInput::NowKey[BUTTONS];
char PadInput::OldKey[BUTTONS];
XINPUT_STATE PadInput::Input;
int PadInput::InputX = -1;
int PadInput::InputY = -1;
int PadInput::OldX = -1;
int PadInput::OldY = -1;
int PadInput::FlgX = 0;
int PadInput::FlgY = 0;

//to do
int PadInput::oldKey;
int PadInput::nowKey;
//‚±‚±‚Ü‚Å

void PadInput::UpdateKey()
{
	/*GetJoypadXInputState(DX_INPUT_PAD1, &Input);
	for (int i = 0; i < BUTTONS; i++)
	{
		OldKey[i] = NowKey[i];
		NowKey[i] = Input.Buttons[i];
	}

	InputX = Input.ThumbLX;
	InputY = Input.ThumbLY;*/

	oldKey = nowKey;
	nowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

void PadInput::SticControl()
{

	if (MARGIN < OldX && MARGIN < InputX)
	{
		FlgX = 1;
	}
	else if (OldX < -MARGIN && InputX < -MARGIN)
	{
		FlgX = 1;
	}
	else
	{
		FlgX = 0;
	}

	if (MARGIN < OldY && MARGIN < InputY)
	{
		FlgY = 1;
	}
	else if (OldY < -MARGIN && InputY < -MARGIN)
	{
		FlgY = 1;
	}
	else
	{
		FlgY = 0;
	}

	OldX = InputX;
	OldY = InputY;
}
