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
	////TO DO いつか消す
	//flg = false;
	////ここまで
	Jumping = true;
	XSize = SMALL_MARIO_SIZE;
	YSize = SMALL_MARIO_SIZE;
	Location.x = 3 * BLOCK_SIZE;
	Location.y = 12 * BLOCK_SIZE + YSize / 2;
	Speed = 0.0f;
	Inertia = 0.2f;
	AnimWait = 0;
	Life = 3;
	State = STATE::SMALL;
	SaveState = STATE::SMALL;
	Move = MOVE_VECTOR::STOP;
	mState = MOVE_STATE::WALK;
	if (LoadImages() == -1)
	{
		throw;
	}
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
	if (Move!=MOVE_VECTOR::DOWN && Jumping && PadInput::OnClick(XINPUT_BUTTON_B))
	{
		PreparingJump();
		Move = MOVE_VECTOR::UP;
	}
	else if (!IsAir)//ジャンプを可能にする
	{
		Jumping = true;
	}  //ジャンプしていてBボタンを離した時
	if (IsAir && PadInput::OnRelese(XINPUT_BUTTON_B)) //降下する
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
	if (IsAir)
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

	/*スターの時間が切れたら元の状態に戻す*/
	if (State == STATE::STAR_BIG || State == STATE::STAR_SMALL)
	{
		if (--StarLimit < 0)
		{
			State = SaveState;
		}
	}
#define DEBUG
#ifndef DEBUG
#endif // !DEBUG

}

void Mario::Draw() const
{
	switch (State)
	{
	case STATE::SMALL:
		DrawRotaGraphF(Location.x, Location.y, 1, 0, sMario[aIndex], TRUE, Turn);
		break;
	case STATE::BIG:
		DrawRotaGraphF(Location.x, Location.y, 1, 0, bMario[aIndex], TRUE, Turn);
		break;
	case STATE::FIRE:
		DrawRotaGraphF(Location.x, Location.y, 1, 0, fMario[aIndex], TRUE, Turn);
		break;
	case STATE::STAR_SMALL:
		DrawRotaGraphF(Location.x, Location.y, 1, 0, Star_sMario[aIndex + H * 8], TRUE, Turn);
		break;
	case STATE::STAR_BIG:
		DrawRotaGraphF(Location.x, Location.y, 1, 0, Star_bMario[aIndex + H * 9], TRUE, Turn);
		break;
	}

#define DEBUG
#ifndef DEBUG
	if (flg)
	{
		DrawBox(Location.x - XSize / 2, Location.y - YSize / 2, Location.x + XSize / 2, Location.y + YSize / 2, 0xff0000, FALSE);
	}
	else
	{
		DrawBox(Location.x - XSize / 2, Location.y - XSize / 2, Location.x + XSize / 2, Location.y + YSize / 2, 0x0000ff, FALSE);
	}
	DrawFormatString(0, 90, 0xffffff, "M左上のステージ位置\nX %d Y %d", static_cast<int>((Location.x-XSize/2) / BLOCK_SIZE), static_cast<int>((Location.y-YSize/2) / BLOCK_SIZE));
	DrawFormatString(0, 130, 0xffffff, "M右下のステージ位置\nX %d Y %d", static_cast<int>((Location.x + XSize/2) / BLOCK_SIZE), static_cast<int>((Location.y + YSize/2) / BLOCK_SIZE));
	//DrawFormatString(400, 10, 0x000000, "X %f Y %f", Location.x, Location.y);
	/*DrawFormatString(10, 100, 0x000000, "1：左 2：右 3：上 4：下\n動く方向 %d", static_cast<int>(Move));
	DrawFormatString(10, 140, 0x000000, "0:default 1：ground 2：sky\njstate %d", static_cast<int>(jState));
	DrawFormatString(0, 260, 0x000000, "1：左 2：右 3：上 4：下\nSide %d", (int)side);*/
	//DrawFormatString(10, 180, 0xffffff, "0:Stop 1:Walk 2:Dash\n mState %d", static_cast<int>(mState));
	//DrawFormatString(300, 30, 0x000000, "kasoku %f speed %f \nYspeed %f Acceleration %f", kasokudo, Speed, YSpeed,IncrementalAccelerationData[index]);

	//DrawFormatString(0, 260, 0x000000, "マリオ 中央\nX %d Y %d", (int)Location.x/BLOCK_SIZE,(int)Location.y/BLOCK_SIZE);

	DrawCircle(Location.x, Location.y, 3, 0x00ff00, TRUE, 2);

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

void Mario::Hit(int item_type)
{
	switch (item_type)
	{
	case 1: //キノコ
		YSize = BIG_MARIO_HEIGTH_SIZE;
		XSize = BIG_MARIO_WIDTH_SIZE;
		//状態を変更する
		if (State == STATE::STAR_SMALL)
		{
			State = STATE::STAR_BIG;
		}
		else
		{
			State = STATE::BIG;
			Location.y = Location.y - BLOCK_SIZE / 2;
		}
		break;
	case 2: //1UPキノコ
		++Life;
		break;
	case 5: //フラワー
		if (State == STATE::SMALL)//マリオが小さい時
		{
			YSize = BIG_MARIO_HEIGTH_SIZE;
			XSize = BIG_MARIO_WIDTH_SIZE;
		}

		//状態を変更する
		//スター状態の時SaveStateを変更する
		if (State == STATE::STAR_SMALL || State == STATE::STAR_BIG)
		{
			SaveState = STATE::FIRE;
		}
		else
		{
			State = STATE::FIRE;
		}
		break;
	case 6: //スター
		if (State == STATE::SMALL)//マリオが小さい時
		{
			SaveState = State;
			State = STATE::STAR_SMALL;
			StarLimit = 720;
		}
		else
		{
			SaveState = State;
			State = STATE::STAR_BIG;
			StarLimit = 720;
		}
		break;
	}
}

void Mario::HitStage(int h_block, int w_block
	, int hit_side, int scroll)
{
	VECTOR vec;

	vec.y = static_cast<float>(h_block * BLOCK_SIZE);
	vec.x = static_cast<float>(w_block * BLOCK_SIZE);

	switch (hit_side) //当たったブロックの辺の位置
	{
	case 1:  //左側
		Location.x = vec.x - BLOCK_SIZE / 2;
		break;
	case 2: //右側
		Location.x = vec.x + BLOCK_SIZE / 2;
		break;
	case 3:   //上側
		Location.y = vec.y - YSize / 2;
		Move = MOVE_VECTOR::STOP;
		IsAir = false;
		Jumping = false;
		break;
	case 4: //下側
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
	IsAir = true;
	//Location.y += MaxFallSpeed;
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
	IsAir = true;
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
}

void Mario::Animation()
{
	//ジャンプしている時
	if (IsAir)
	{
		if (State == STATE::SMALL || State == STATE::STAR_SMALL)
		{
			aIndex = 5;
		}
		else
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
				if (State == STATE::SMALL || State == STATE::STAR_SMALL)
				{
					if (3 < ++aIndex)
					{
						aIndex = 1;
					}
				}
				else
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
				if (State == STATE::SMALL || State == STATE::STAR_SMALL)
				{
					if (3 < ++aIndex)
					{
						aIndex = 1;
					}
				}
				else
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
			if (State == STATE::SMALL || State == STATE::STAR_SMALL)
			{
				aIndex = 4;
			}
			else
			{
				aIndex = 5;
			}
		}
		if (Move == MOVE_VECTOR::LEFT
			&& 0 < Speed)
		{
			if (State == STATE::SMALL || State == STATE::STAR_SMALL)
			{
				aIndex = 4;
			}
			else
			{
				aIndex = 5;
			}
		}
	}
	else
	{
		aIndex = 0;
	}

	//スター状態の時、マリオをちかちかさせる
	if (State == STATE::STAR_BIG || State == STATE::STAR_SMALL)
	{
		//スター状態終了2秒前
		if (StarLimit < DownSpeedTime)
		{
			if (AnimSpeed / 2 < ++StarTime)
			{
				if (3 < ++H)
				{
					H = 0;
				}
				StarTime = 0;
			}
		}
		else
		{
			if (AnimSpeed / 6 < ++StarTime)
			{
				if (3 < ++H)
				{
					H = 0;
				}
				StarTime = 0;
			}
		}
	}
}

int Mario::LoadImages()
{
	if (LoadDivGraph("1-1image/Mario/dekamario.png", 10, 10, 1, 32, 64, bMario) == -1) return -1;
	if (LoadDivGraph("1-1image/Mario/mario.png", 9, 9, 1, 32, 32, sMario) == -1) return -1;
	if (LoadDivGraph("1-1image/Mario/faiyamario.png", 9, 9, 1, 32, 64, fMario) == -1) return -1;
	if (LoadDivGraph("1-1image/Mario/starmario.png", 36, 9, 4, 32, 64, Star_bMario) == -1) return -1;
	if (LoadDivGraph("1-1image/Mario/starsmallmario.png", 32, 8, 4, 32, 32, Star_sMario) == -1) return -1;
	return 0;
}
