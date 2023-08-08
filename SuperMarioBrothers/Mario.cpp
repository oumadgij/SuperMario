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
	flg = false;
	Jumping = true;
	//ここまで
	XSize = SMALL_MARIO_SIZE;
	YSize = SMALL_MARIO_SIZE;
	Location.x = 3 * BLOCK_SIZE;
	Location.y = 12 * BLOCK_SIZE+YSize/2;
	//Location.y = 11 * BLOCK_SIZE + BLOCK_SIZE;
	Speed = 0.0f;
	Inertia = 0.2f;
	AnimWait = 0;
	State = STATE::SMALL;
	//State = STATE::BIG;
	Move = MOVE_VECTOR::STOP;
	mState = MOVE_STATE::WALK;
	LoadDivGraph("1-1image/Mario/dekamario.png", 10, 10, 1, 32, 64, b_marioImg);
	LoadDivGraph("1-1image/Mario/mario.png", 9, 9, 1, 32, 32, s_marioImg);
}

void Mario::Update()
{
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
		Turn = true;
	}
	//右移動
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)
		|| MARGIN < PadInput::GetThumbLX())
	{
		Move = MOVE_VECTOR::RIGHT;
		Speed += Inertia;
		Turn = false;
	}
	//ジャンプ
	if (Jumping && PadInput::OnClick(XINPUT_BUTTON_B))
	{
		PreparingJump();
		Move = MOVE_VECTOR::UP;
	}
	else if (jState == JUMP_STATE::GROUND)//ジャンプを可能にする
	{
		Jumping = true;
	}
	if (jState == JUMP_STATE::SKY               //ジャンプしていてBボタンを離した時
		&& PadInput::OnRelese(XINPUT_BUTTON_B)) //降下する
	{
		Move = MOVE_VECTOR::DOWN;
		kasokudo += Fallkasokudo;
	}
	
	//しゃがみ
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN) 
		|| PadInput::GetThumbLY() < -MARGIN)
	{
		if (State == STATE::BIG || State == STATE::FIRE)
		{
			aIndex = 1;
		}
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
	if (jState==JUMP_STATE::SKY)
	{
		Jump();
	}

	/*移動する*/
	if (Move == MOVE_VECTOR::STOP)//入力していない時
	{
		Speed = 0;
	}
	Location.x += Speed;
	if (Location.x < 0) //画面から出ないようにする
	{
		Location.x = 0;
	}
	if (320.0f < Location.x)
	{
		Location.x = 320.0f;
	}

	/*アニメーション*/
	Animation();

#define DEBUG
#ifndef DEBUG
	if (PadInput::OnClick(XINPUT_BUTTON_LEFT_SHOULDER))
	{
		if (1 < ++mari) mari = 0;
	}

	if (mari == 0)
	{
		State = STATE::BIG;
		Location.x = 6 * BLOCK_SIZE;
		Location.y = 11 * BLOCK_SIZE;
	}
	if (mari == 1)
	{
		State = STATE::SMALL;
		Location.x = 6 * BLOCK_SIZE;
		Location.y = 12 * BLOCK_SIZE;
	}
#endif // !DEBUG

}

void Mario::Draw() const
{
	if (State == STATE::SMALL)
	{
		DrawRotaGraphF(Location.x, Location.y, 1, 0, s_marioImg[aIndex],TRUE, Turn);
	}
	else
	{
		DrawRotaGraphF(Location.x, Location.y, 1, 0, b_marioImg[aIndex], TRUE, Turn);
	}

	if (flg)
	{
		DrawBox(Location.x - XSize / 2, Location.y - YSize / 2, Location.x + XSize / 2, Location.y + YSize / 2, 0xff0000, FALSE);
	}
	else
	{
		DrawBox(Location.x - XSize / 2, Location.y - XSize / 2, Location.x + XSize / 2, Location.y + YSize / 2, 0x0000ff, FALSE);
	}

#define DEBUG
#ifdef DEBUG
	/*DrawFormatString(10, 10, 0xffffff, "左上のステージ位置\nX %d Y %d", static_cast<int>((Location.x-XSize/2) / BLOCK_SIZE), static_cast<int>((Location.y-YSize/2) / BLOCK_SIZE));
	DrawFormatString(10, 50, 0xffffff, "右下のステージ位置\nX %d Y %d", static_cast<int>((Location.x + XSize/2) / BLOCK_SIZE), static_cast<int>((Location.y + YSize/2) / BLOCK_SIZE));*/
	DrawFormatString(400, 10, 0x000000, "X %f Y %f", Location.x, Location.y);
	DrawFormatString(10, 100, 0x000000, "1：左 2：右 3：上 4：下\n動く方向 %d", static_cast<int>(Move));
	DrawFormatString(10, 140, 0x000000, "0:default 1：ground 2：sky\njstate %d", static_cast<int>(jState));
	DrawFormatString(0, 180, 0x000000, "HitBlock[0] %d 座標 %d", HitBlock[0], HitBlock[0] * BLOCK_SIZE);
	DrawFormatString(0, 220, 0x000000, "HitBlock[1] %d 座標 %d", HitBlock[1], HitBlock[1] * BLOCK_SIZE);
	DrawFormatString(0, 260, 0x000000, "1：左 2：右 3：上 4：下\nSide %d", (int)side);
	//DrawFormatString(10, 180, 0xffffff, "0:Stop 1:Walk 2:Dash\n mState %d", static_cast<int>(mState));
	DrawFormatString(300, 30, 0x000000, "kasoku %f speed %f \nYspeed %f Acceleration %f", kasokudo, Speed, YSpeed,IncrementalAccelerationData[index]);

	if (flg)
	{
		DrawBox(Location.x-XSize/2, Location.y-YSize/2, Location.x + XSize/2, Location.y + YSize/2, 0xff0000, FALSE);
	}
	else
	{
		DrawBox(Location.x - XSize / 2, Location.y - XSize / 2, Location.x + XSize / 2, Location.y + YSize / 2, 0x0000ff, FALSE);
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
		Location.x = vec.x - BLOCK_SIZE / 2;
		flg = false;
		break;
	case HIT_SIDE::RIGHT: //右側
		Location.x = vec.x + BLOCK_SIZE / 2;
		flg = false;
		break;
	case HIT_SIDE::TOP:   //上側
		Location.y = vec.y - YSize / 2;
		Move = MOVE_VECTOR::STOP;
		jState = JUMP_STATE::GROUND;
		Jumping = false;
		flg = false;

		break;
	case HIT_SIDE::UNDER: //下側
		Location.y = vec.y + YSize;
		//降下準備
		Move = MOVE_VECTOR::DOWN;
		kasokudo += MaxFallSpeed;
		break;
	}
}

void Mario::Fall()
{
	Move = MOVE_VECTOR::DOWN;
	Location.y += MaxFallSpeed;
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
		if (Speed < -0.06f)
		{
			Speed += 0.06f;
		}
		else if (0.06f < Speed)
		{
			Speed -= 0.06f;
		}
		else
		{
			Speed = 0.0f;
			if (Move != MOVE_VECTOR::UP)
			{
				Move = MOVE_VECTOR::STOP;
			}
		}
	}
	if (mState == MOVE_STATE::DASH)
	{
		if (Speed < -0.03f)
		{
			Speed += 0.03f;
		}
		else if (0.03f < Speed)
		{
			Speed -= 0.03f;
		}
		else
		{
			Speed = 0.0f;
			if (Move != MOVE_VECTOR::UP)
			{
				Move = MOVE_VECTOR::STOP;
			}
		}
	}
}

//ジャンプする前の準備
void Mario::PreparingJump()
{
	Jumping = false;
	jState = JUMP_STATE::SKY;
	sec = 0;

	index = 0;
	if ( /*0.109*/4.8f<= Speed) index++;
	if (/*0.097*/ 3.4f<= Speed) index++;
	if (/*0.062*/ 3.2f<= Speed)index++;
	if (/*0.035*/ 0.2f<= Speed)index++;

	kasokudo = IncrementalAccelerationData[index];
	IncrementalAcceleration = IncrementalAccelerationData[index];
	Fallkasokudo = FallAcceleration[index];
	YSpeed = InitialSpeed[index];
	XSpeed = Speed;
}

//ジャンプする
void Mario::Jump()
{
	if (Move == MOVE_VECTOR::UP)
	{
		if (60 < ++sec)
		{
			kasokudo += IncrementalAcceleration;
			sec = 0;
		}
	}
	else
	{
		if (60 < ++sec)
		{
			kasokudo += Fallkasokudo;
			sec = 0;
		}
	}

	//距離を求める    1フレーム = 0.016秒
	//Y座標
	YSpeed += kasokudo;
	if (MaxFallSpeed < YSpeed) YSpeed = MaxFallSpeed;

	Location.y += YSpeed;

	//X座標
	Location.x += XSpeed * 0.016;

	//下降するタイミングを判断
	if (0 < YSpeed)
	{
		kasokudo += Fallkasokudo;
		Move = MOVE_VECTOR::DOWN;
	}

	float Ground = 0.0f;
	//地面に着地したか判断
	if (State == STATE::SMALL)
	{
		Ground = 12 * BLOCK_SIZE+BLOCK_SIZE/2;
	}
	else
	{
		Ground = 12 * BLOCK_SIZE+BLOCK_SIZE;
	}
	
	if (Ground < Location.y)
	{
		Location.y = Ground;
		Jumping = false;
		jState = JUMP_STATE::GROUND;
	}
}

void Mario::Animation()
{
	//ジャンプしている時
	if (jState == JUMP_STATE::SKY)
	{
		if (State == STATE::SMALL)
		{
			aIndex = 5;
		}
		else if (State == STATE::BIG)
		{
			aIndex = 6;
		}
	}//歩いている時
	else if (Move != MOVE_VECTOR::STOP)
	{
		if (mState == MOVE_STATE::WALK)
		{
			if (AnimSpeed < ++AnimWait)
			{
				if (State == STATE::SMALL)
				{
					if (3 < ++aIndex)
					{
						aIndex = 1;
					}
				}
				else if (State == STATE::BIG)
				{
					if (4 < ++aIndex)
					{
						aIndex = 2;
					}
				}

				AnimWait = 0;
			}
		}
		else if (mState == MOVE_STATE::DASH)
		{
			if ((AnimSpeed / 2) < ++AnimWait)
			{
				if (State == STATE::SMALL)
				{
					if (3 < ++aIndex)
					{
						aIndex = 1;
					}
				}
				else if (State == STATE::BIG)
				{
					if (4 < ++aIndex)
					{
						aIndex = 2;
					}
				}
				AnimWait = 0;
			}
		}
		//入力方向から反対に入力した時に
		//マリオが急ブレーキ掛けた体制をとる
		if (Move == MOVE_VECTOR::RIGHT
			&& Speed < 0)
		{
			if (State == STATE::SMALL)
			{
				aIndex = 4;
			}
			else if (State == STATE::BIG)
			{
				aIndex = 5;
			}
		}
		if (Move == MOVE_VECTOR::LEFT
			&& 0 < Speed)
		{
			if (State == STATE::SMALL)
			{
				aIndex = 4;
			}
			else if (State == STATE::BIG)
			{
				aIndex = 5;
			}
		}
	}
	else
	{
		aIndex = 0;
	}
}
