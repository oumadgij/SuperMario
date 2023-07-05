#include "Mario.h"
#include "DxLib.h"
#include "PadInput.h"

Mario::Mario()
{
	//TO DO
	m = 0;
	n = 0;
	//ここまで
	x = 6 * 32;
	y = 10 * 32;
	state = STATE::BIG;
	LoadDivGraph("1-1image/Mario/dekamario.png", 10, 10, 1, 32, 64, marioImg);
	//LoadDivGraph("1-1image/Mario/mario.png", 9, 9, 1, 32, 32, marioImg);
}

void Mario::Update()
{
	m = 0;
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT)
		|| PadInput::GetThumbLX() < -MARGIN)
	{
		//左に移動
		x -= 5;
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)
		|| MARGIN < PadInput::GetThumbLX())
	{
		//右に移動
		x += 5;
	}
	if ((state == STATE::BIG || state == STATE::FIRE)
		&& (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN) || MARGIN < PadInput::GetThumbLY()))
	{
		//しゃがみ
		m = 1;
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_A))
	{
		//ダッシュ
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_B))
	{
		//ジャンプ
	}
}

void Mario::Draw() const
{
	DrawGraph(x, y, marioImg[m], TRUE);
}
