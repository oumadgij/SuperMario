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
	////TO DO ��������
	//flg = false;
	////�����܂�
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
	/*�ړ����������߂�*/
	//�_�b�V��
	if (PadInput::OnPressed(XINPUT_BUTTON_A))
	{
		mState = MOVE_STATE::DASH;
	}
	else
	{
		mState = MOVE_STATE::WALK;
	}
	//���ړ�
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT)
		|| PadInput::GetThumbLX() < -MARGIN)
	{
		Move = MOVE_VECTOR::LEFT;
		Speed -= Inertia;
		Turn = true;
	}
	//�E�ړ�
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)
		|| MARGIN < PadInput::GetThumbLX())
	{
		Move = MOVE_VECTOR::RIGHT;
		Speed += Inertia;
		Turn = false;
	}
	//�W�����v
	if (Move!=MOVE_VECTOR::DOWN && Jumping && PadInput::OnClick(XINPUT_BUTTON_B))
	{
		PreparingJump();
		Move = MOVE_VECTOR::UP;
	}
	else if (!IsAir)//�W�����v���\�ɂ���
	{
		Jumping = true;
	}  //�W�����v���Ă���B�{�^���𗣂�����
	if (IsAir && PadInput::OnRelese(XINPUT_BUTTON_B)) //�~������
	{
		Move = MOVE_VECTOR::DOWN;
		kasokudo += Fallkasokudo;
	}
	
	//���Ⴊ��
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN) 
		|| PadInput::GetThumbLY() < -MARGIN)
	{
		if (State == STATE::BIG || State == STATE::FIRE)
		{
			aIndex = 1;
		}
	}

	/*�X�s�[�h�𐧌�����*/
	SpeedUp();

	/*���͂��~�߂����ɏ����i��Ŏ~�܂�*/
	if (PadInput::OnRelese(XINPUT_BUTTON_DPAD_LEFT)
		|| -MARGIN < PadInput::GetThumbLX())
	{
		if (PadInput::OnRelese(XINPUT_BUTTON_DPAD_RIGHT)
			|| PadInput::GetThumbLX() < MARGIN)
		{
			SpeedReduction();
		}
	}

	/*�W�����v����*/
	if (IsAir)
	{
		Jump();
	}

	/*�ړ�����*/
	if (Move == MOVE_VECTOR::STOP)//���͂��Ă��Ȃ���
	{
		Speed = 0;
	}
	Location.x += Speed;
	if (Location.x < 0) //��ʂ���o�Ȃ��悤�ɂ���
	{
		Location.x = 0;
	}
	if (320.0f < Location.x)
	{
		Location.x = 320.0f;
	}

	/*�A�j���[�V����*/
	Animation();

	/*�X�^�[�̎��Ԃ��؂ꂽ�猳�̏�Ԃɖ߂�*/
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
	DrawFormatString(0, 90, 0xffffff, "M����̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((Location.x-XSize/2) / BLOCK_SIZE), static_cast<int>((Location.y-YSize/2) / BLOCK_SIZE));
	DrawFormatString(0, 130, 0xffffff, "M�E���̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((Location.x + XSize/2) / BLOCK_SIZE), static_cast<int>((Location.y + YSize/2) / BLOCK_SIZE));
	//DrawFormatString(400, 10, 0x000000, "X %f Y %f", Location.x, Location.y);
	/*DrawFormatString(10, 100, 0x000000, "1�F�� 2�F�E 3�F�� 4�F��\n�������� %d", static_cast<int>(Move));
	DrawFormatString(10, 140, 0x000000, "0:default 1�Fground 2�Fsky\njstate %d", static_cast<int>(jState));
	DrawFormatString(0, 260, 0x000000, "1�F�� 2�F�E 3�F�� 4�F��\nSide %d", (int)side);*/
	//DrawFormatString(10, 180, 0xffffff, "0:Stop 1:Walk 2:Dash\n mState %d", static_cast<int>(mState));
	//DrawFormatString(300, 30, 0x000000, "kasoku %f speed %f \nYspeed %f Acceleration %f", kasokudo, Speed, YSpeed,IncrementalAccelerationData[index]);

	//DrawFormatString(0, 260, 0x000000, "�}���I ����\nX %d Y %d", (int)Location.x/BLOCK_SIZE,(int)Location.y/BLOCK_SIZE);

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
	case 1: //�L�m�R
		YSize = BIG_MARIO_HEIGTH_SIZE;
		XSize = BIG_MARIO_WIDTH_SIZE;
		//��Ԃ�ύX����
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
	case 2: //1UP�L�m�R
		++Life;
		break;
	case 5: //�t�����[
		if (State == STATE::SMALL)//�}���I����������
		{
			YSize = BIG_MARIO_HEIGTH_SIZE;
			XSize = BIG_MARIO_WIDTH_SIZE;
		}

		//��Ԃ�ύX����
		//�X�^�[��Ԃ̎�SaveState��ύX����
		if (State == STATE::STAR_SMALL || State == STATE::STAR_BIG)
		{
			SaveState = STATE::FIRE;
		}
		else
		{
			State = STATE::FIRE;
		}
		break;
	case 6: //�X�^�[
		if (State == STATE::SMALL)//�}���I����������
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

	switch (hit_side) //���������u���b�N�̕ӂ̈ʒu
	{
	case 1:  //����
		Location.x = vec.x - BLOCK_SIZE / 2;
		break;
	case 2: //�E��
		Location.x = vec.x + BLOCK_SIZE / 2;
		break;
	case 3:   //�㑤
		Location.y = vec.y - YSize / 2;
		Move = MOVE_VECTOR::STOP;
		IsAir = false;
		Jumping = false;
		break;
	case 4: //����
		Location.y = vec.y + YSize;
		//�~������
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

//�X�s�[�h���グ��
void Mario::SpeedUp()
{
	//�X�s�[�h�̐������|����
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

//�X�s�[�h��������
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

//�W�����v����O�̏���
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

//�W�����v����
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

	//���������߂�    1�t���[�� = 0.016�b
	//Y���W
	YSpeed += kasokudo;
	if (MaxFallSpeed < YSpeed) YSpeed = MaxFallSpeed;

	Location.y += YSpeed;

	//X���W
	Location.x += XSpeed * 0.016;

	//���~����^�C�~���O�𔻒f
	if (0 < YSpeed)
	{
		kasokudo += Fallkasokudo;
		Move = MOVE_VECTOR::DOWN;
	}
}

void Mario::Animation()
{
	//�W�����v���Ă��鎞
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
	}//�����Ă��鎞
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
		//���͕������甽�΂ɓ��͂�������
		//�}���I���}�u���[�L�|�����̐����Ƃ�
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

	//�X�^�[��Ԃ̎��A�}���I����������������
	if (State == STATE::STAR_BIG || State == STATE::STAR_SMALL)
	{
		//�X�^�[��ԏI��2�b�O
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
