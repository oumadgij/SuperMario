#include "Mario.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Define.h"
#include <math.h>

#define SMALL_MARIO_SIZE 32
#define BIG_MARIO_WIDTH_SIZE 32
#define BIG_MARIO_HEIGTH_SIZE 64
#define WALK_MAXSPEED 3.2f
#define DASH_MAXSPEED 4.8f

Mario::Mario()
{
	//TO DO いつか消す
	m = 0;
	flg = false;
	JumpStartPosition = 0.0f;
	Jumping = false;
	//ここまで
	Location.x = 6 * BLOCK_SIZE;
	Location.y = 12 * BLOCK_SIZE;
	MAX_SMALL_JUMP = Location.y - SMALL_MARIO_SIZE;
	Speed = 0.0f;
	Inertia = 0.2f;
	XSize = SMALL_MARIO_SIZE;
	YSize = SMALL_MARIO_SIZE;
	State = STATE::SMALL;
	Move = MOVE_VECTOR::STOP;
	mState = MOVE_STATE::WALK;
	//LoadDivGraph("1-1image/Mario/dekamario.png", 10, 10, 1, 32, 64, marioImg);
	LoadDivGraph("1-1image/Mario/mario.png", 9, 9, 1, 32, 32, marioImg);
}

void Mario::Update()
{
	m = 0;

	/*移動方向を決める*/
	//ダッシュ
	if (PadInput::OnPressed(XINPUT_BUTTON_A))
	{
		mState = MOVE_STATE::DASH;
	}
	else
	{
		mState = MOVE_STATE::WALK;
	}
	//左移動
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT)
		|| PadInput::GetThumbLX() < -MARGIN)
	{
		Move = MOVE_VECTOR::LEFT;
		Speed -= Inertia;
	}
	//右移動
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)
		|| MARGIN < PadInput::GetThumbLX())
	{
		Move = MOVE_VECTOR::RIGHT;
		Speed += Inertia;
	}
	//ジャンプ
	if ((Jumping == false) &&  PadInput::OnPressed(XINPUT_BUTTON_B))//PAD_INPUT_UP
	{
		Jumping = true;
		PreparingJump();
	}
	if (PadInput::OnRelese(XINPUT_BUTTON_B))//PAD_INPUT_UP
	{
		Move = MOVE_VECTOR::DOWN;
		kasokudo = -0.437;
		InitialSpeed = 4;

	}
	//しゃがみ
	if ((State == STATE::BIG || State == STATE::FIRE)
		&& (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN) || PadInput::GetThumbLY() < -MARGIN))
	{
		m = 1;
	}

	/*スピードを制限する*/
	SpeedUp();

	/*入力を止めた時に少し進んで止まる*/
	if (PadInput::OnRelese(XINPUT_BUTTON_DPAD_LEFT)
		|| -MARGIN < PadInput::GetThumbLX())
	{
		if (PadInput::OnRelese(XINPUT_BUTTON_DPAD_RIGHT)
			|| PadInput::GetThumbLX() < MARGIN)
		{
			SpeedReduction();
		}
	}

	/*ジャンプする*/
	if (Jumping)
	{
		Jump();
	}

	/*移動する*/
	if (Move == MOVE_VECTOR::STOP)  //動いていない、画面に
	{
		Speed = 0;
	}

	Location.x += Speed;

	if (Location.x < 0) //画面から出ないようにする
	{
		Location.x = 0;
	}

#define DEBUG
#ifndef DEBUG
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_UP))
	{
		Location.y -= Speed;
		Move = MOVE_VECTOR::JUMP;
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN))
	{
		Location.y += Speed;
		Move = MOVE_VECTOR::DOWN;
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
	DrawFormatString(10, 100, 0xffffff, "1：左 2：右 3：上 4：下\n動く方向 %d", static_cast<int>(Move));
	DrawFormatString(10, 140, 0xffffff, "1：左 2：右 3：上 4：下\n当たった方向 %d", static_cast<int>(side));

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

void Mario::HitStage()
{
	VECTOR vec;

	vec.y = static_cast<float>(HitBlock[0] * BLOCK_SIZE);
	vec.x = static_cast<float>(HitBlock[1] * BLOCK_SIZE);

	switch (side) //当たったブロックの辺の位置
	{
	case HIT_SIDE::LEFT:  //左側
		Location.x = vec.x - BLOCK_SIZE;
		break;
	case HIT_SIDE::RIGHT: //右側
		Location.x = vec.x + BLOCK_SIZE;
		break;
	case HIT_SIDE::TOP:   //上側
		Location.y = vec.y - YSize;
		break;
	case HIT_SIDE::UNDER: //下側
		Location.y = vec.y + BLOCK_SIZE;
		//降下準備
		Move = MOVE_VECTOR::DOWN;
		kasokudo = -0.437;
		InitialSpeed = 4;
		break;
	}

	Move = MOVE_VECTOR::STOP;
	flg = false;
}

//スピードを上げる
void Mario::SpeedUp()
{
	//スピードの制限を掛ける
	if (mState == MOVE_STATE::WALK)
	{
		if (WALK_MAXSPEED < Speed)
		{
			Speed = WALK_MAXSPEED;
		}
		if (Speed < -WALK_MAXSPEED)
		{
			Speed = -WALK_MAXSPEED;
		}
	}
	if (mState == MOVE_STATE::DASH)
	{
		if (DASH_MAXSPEED < Speed)
		{
			Speed = DASH_MAXSPEED;
		}
		if (Speed < -DASH_MAXSPEED)
		{
			Speed = -DASH_MAXSPEED;
		}
	}
}

//スピードを下げる
void Mario::SpeedReduction()
{
	if (mState == MOVE_STATE::WALK)
	{
		if (Speed < -0.2f)
		{
			Speed += 0.2f;
		}
		else if (0.2f < Speed)
		{
			Speed -= 0.2f;
		}
		else
		{
			Speed = 0.0f;
			mState = MOVE_STATE::STOP;
		}
	}
	if (mState == MOVE_STATE::DASH)
	{
		if (Speed < -0.15f)
		{
			Speed += 0.15f;
		}
		else if (0.15f < Speed)
		{
			Speed -= 0.15f;
		}
		else
		{
			Speed = 0.0f;
			mState = MOVE_STATE::STOP;
		}
	}
}

//ジャンプする前の準備
void Mario::PreparingJump()
{
	kasokudo = 0.125f;
	InitialSpeed = -4.0f;
	index = 0;
	time = 0.016f;
	Move = MOVE_VECTOR::JUMP;
}

//ジャンプする
void Mario::Jump()
{
	//初速を代入する
	if (120 < sec++)
	{
		if (Move == MOVE_VECTOR::JUMP)
		{
			kasokudo += IncrementalAcceleration[index++];
		}
		if (Move == MOVE_VECTOR::DOWN)
		{
			kasokudo += FallAcceleration[index++];
		}
		sec = 0;

		if (4 < index)
		{
			index = 0;
		}
	}

	//降下速度を調整する
	if ((Move == MOVE_VECTOR::DOWN) && kasokudo == MaxFallSpeed)
	{
		kasokudo = MaxFallSpeed;
	}

	//距離を求める    1フレーム = 0.016秒
	//Y座標
	Location.y += InitialSpeed * time + 0.5 * kasokudo * pow(time, 2);
	//X座標
	//Location.x += 0.5 * Inertia * pow(time, 2) + Speed * time;

	//下降するタイミングを判断
	if (Location.y < 150)//MAX_SMALL_JUMP
	{
		Location.y = 150;//MAX_SMALL_JUMP
		kasokudo = -0.437;
		InitialSpeed = 4;
	}

	//地面に着地したか判断
	float Ground = 12 * BLOCK_SIZE;
	if (Ground < Location.y)
	{
		Location.y = Ground;
		Jumping = false;
	}

	time += 0.01;
}

////初速を代入する
//if (120 < sec++)
//{
//	if (Move == MOVE_VECTOR::JUMP)
//	{
//		kasokudo += IncrementalAcceleration[index++];
//	}
//	if (Move == MOVE_VECTOR::DOWN)
//	{
//		kasokudo += FallAcceleration[index++];
//	}
//	sec = 0;
//
//	if (4 < index)
//	{
//		index = 0;
//	}
//}
//
////降下速度を調整する
//if ((Move == MOVE_VECTOR::DOWN) && kasokudo == MaxFallSpeed)
//{
//	kasokudo = MaxFallSpeed;
//}
//
////距離を求める    1フレーム = 0.016秒
////Y座標
//Location.y += InitialSpeed * 1.5 + 0.5 * kasokudo * pow(0.016, 2);
////X座標
//Location.x += 0.5 * Inertia * pow(0.016, 2) + Speed * 0.016;
//
////下降するタイミングを判断
//if (Location.y < 150)//MAX_SMALL_JUMP
//{
//	Location.y = 150;//MAX_SMALL_JUMP
//	kasokudo = -0.437;
//	InitialSpeed = 4;
//}
//
////地面に着地したか判断
//float Ground = 12 * BLOCK_SIZE;
//if (Ground < Location.y)
//{
//	Location.y = Ground;
//	Jumping = false;
//}
