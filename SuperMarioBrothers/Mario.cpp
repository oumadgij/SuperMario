#include "Mario.h"
#include "DxLib.h"
#include "PadInput.h"

#define BIGMARIO_WIDTH_SIZE 32
#define BIGMARIO_HEIGTH_SIZE 64

Mario::Mario()
{
	//TO DO いつか消す
	m = 0;
	flg = false;
	//ここまで
	Location.x = 6 * BIGMARIO_WIDTH_SIZE;
	Location.y = 10 * 32 + 32;   //BIGMARIO_HEIGTH_SIZE
	Speed = 2.5f;
	XSize = BIGMARIO_WIDTH_SIZE;
	YSize = BIGMARIO_HEIGTH_SIZE;
	state = STATE::BIG;
	move = MOVE_VECTOR::STOP;
	LoadDivGraph("1-1image/Mario/dekamario.png", 10, 10, 1, 32, 64, marioImg);
	//LoadDivGraph("1-1image/Mario/mario.png", 9, 9, 1, 32, 32, marioImg);
}

void Mario::Update()
{
	m = 0;
	move = MOVE_VECTOR::STOP;
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT)
		|| PadInput::GetThumbLX() < -MARGIN)
	{
		//左に移動
		Location.x -= Speed;
		move = MOVE_VECTOR::LEFT;
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)
		|| MARGIN < PadInput::GetThumbLX())
	{
		//右に移動
		Location.x += Speed;
		move = MOVE_VECTOR::RIGHT;
	}
	if ((state == STATE::BIG || state == STATE::FIRE)
		&& (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN) || PadInput::GetThumbLY() < -MARGIN))
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
		move = MOVE_VECTOR::JUMP;
	}

#define DEBUG
#ifdef DEBUG
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_UP))
	{
		Location.y -= Speed;
		move = MOVE_VECTOR::JUMP;
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN))
	{
		Location.y += Speed;
		move = MOVE_VECTOR::DOWN;
	}
#endif // !DEBUG

}

void Mario::Draw() const
{
	DrawGraph(static_cast<int>(Location.x), static_cast<int>(Location.y), marioImg[m], TRUE);

#define DEBUG
#ifdef DEBUG
	DrawFormatString(10, 50, 0xffffff, "X %f Y %f", Location.x, Location.y);
	DrawFormatString(10, 100, 0xffffff, "1：左 2：右 3：上 4：下\nHit %d", static_cast<int>(move));
	if (flg)
	{
		DrawBox(Location.x, Location.y, Location.x + XSize, Location.y + YSize, 0xff0000, FALSE);
	}
	else
	{
		DrawBox(Location.x, Location.y, Location.x + XSize, Location.y + YSize, 0x0000ff, FALSE);
	}
	DrawPixel(Location.x + XSize, Location.y + YSize, 0xffffff);
#endif // !DEBUG
}

void Mario::Hit(int stagex, int stagey)
{
	float X = 0.f;

	if (stagex != 0)
	{
		switch (move)  //何処方向に進んでいたか
		{
		case MOVE_VECTOR::LEFT:  //左
			//X= (stagex+1) * 32;
			Location.x = static_cast<float>((stagex + 1) * 32);
			break;
		case MOVE_VECTOR::RIGHT:  //右
			//X = (stagex-1) * 32 + 32;
			Location.x = static_cast<float>((stagex - 1) * 32 + 32);
			break;
		}

		/*Location.x = X;*/
	}
	float Y = 0.f;
	if (stagey != 0)
	{
		switch (move)
		{
		case MOVE_VECTOR::JUMP:
			//Y = (stagey+1) * 32 + 32;
			Location.y = static_cast<float>((stagey + 1) * 32 + 32);
			break;
		case MOVE_VECTOR::DOWN:
			//Y = (stagey - 1) * 32 + BIGMARIO_HEIGTH;
			Location.y = static_cast<float>((stagey - 1) * 32 + BIGMARIO_HEIGTH_SIZE);
			break;
		}

		//Location.y = Y;
	}
}