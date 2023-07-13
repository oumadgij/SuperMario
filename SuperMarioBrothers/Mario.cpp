#include "Mario.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Define.h"

#define SMALL_MARIO_SIZE 32
#define BIG_MARIO_WIDTH_SIZE 32
#define BIG_MARIO_HEIGTH_SIZE 64

Mario::Mario()
{
	//TO DO いつか消す
	m = 0;
	flg = false;
	//ここまで
	Location.x = 6 * 32;
	Location.y = 11 * 32;
	Speed = 2.5f;
	XSize = BIG_MARIO_WIDTH_SIZE;
	YSize = BIG_MARIO_HEIGTH_SIZE;
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
		//画面から出ないようにする
		if (0 < Location.x-Speed)
		{
			//左に移動
			Location.x -= Speed;
			move = MOVE_VECTOR::LEFT;
		}
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
	DrawFormatString(10, 10, 0xffffff, "左上のステージ位置\nX %d Y %d", static_cast<int>(Location.x / BLOCK_SIZE), static_cast<int>(Location.y / BLOCK_SIZE));
	DrawFormatString(10, 50, 0xffffff, "右下のステージ位置\nX %d Y %d", static_cast<int>((Location.x + XSize) / BLOCK_SIZE), static_cast<int>((Location.y + YSize) / BLOCK_SIZE));
	DrawFormatString(400, 10, 0xffffff, "X %f Y %f", Location.x, Location.y);
	DrawFormatString(10, 100, 0xffffff, "1：左 2：右 3：上 4：下\n動く方向 %d", static_cast<int>(move));
	if (flg)
	{
		DrawBox(Location.x, Location.y, Location.x + XSize, Location.y + YSize, 0xff0000, FALSE);
	}
	else
	{
		DrawBox(Location.x, Location.y, Location.x + XSize, Location.y + YSize, 0x0000ff, FALSE);
	}
#endif // !DEBUG
}

void Mario::Hit()
{
}