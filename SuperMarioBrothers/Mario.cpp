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
	//TO DO ��������
	m = 0;
	flg = false;
	Jumping = true;
	//�����܂�
	Location.x = 6 * BLOCK_SIZE;
	Location.y = 12 * BLOCK_SIZE;
	//Location.y = 11 * BLOCK_SIZE;
	Speed = 0.0f;
	Inertia = 0.2f;
	XSize = SMALL_MARIO_SIZE;
	YSize = SMALL_MARIO_SIZE;
	State = STATE::SMALL;
	Move = MOVE_VECTOR::STOP;
	mState = MOVE_STATE::WALK;
	LoadDivGraph("1-1image/Mario/dekamario.png", 10, 10, 1, 32, 64, b_marioImg);
	LoadDivGraph("1-1image/Mario/mario.png", 9, 9, 1, 32, 32, s_marioImg);
}

void Mario::Update()
{
	m = 0;

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
	}
	//�E�ړ�
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)
		|| MARGIN < PadInput::GetThumbLX())
	{
		Move = MOVE_VECTOR::RIGHT;
		Speed += Inertia;
	}
	//�W�����v
	if (Jumping && PadInput::OnClick(XINPUT_BUTTON_B))
	{
		PreparingJump();
	}
	else if (jState == JUMP_STATE::GROUND)//�W�����v���\�ɂ���
	{
		Jumping = true;
	}
	if (jState == JUMP_STATE::SKY               //�W�����v���Ă���B�{�^���𗣂�����
		&& PadInput::OnRelese(XINPUT_BUTTON_B)) //�~������
	{
		Move = MOVE_VECTOR::DOWN;
		kasokudo += Fallkasokudo;
	}

	//���Ⴊ��
	if ((State == STATE::BIG || State == STATE::FIRE)
		&& (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN) || PadInput::GetThumbLY() < -MARGIN))
	{
		m = 1;
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
	if (jState==JUMP_STATE::SKY)
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
	//DrawGraph(static_cast<int>(Location.x), static_cast<int>(Location.y), s_marioImg[m], TRUE);

	if (State == STATE::SMALL)
	{
		DrawGraph(static_cast<int>(Location.x), static_cast<int>(Location.y), s_marioImg[m], TRUE);
	}
	else
	{
		DrawGraph(static_cast<int>(Location.x), static_cast<int>(Location.y), b_marioImg[m], TRUE);
	}

#define DEBUG
#ifdef DEBUG
	DrawFormatString(10, 10, 0xffffff, "����̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>(Location.x / BLOCK_SIZE), static_cast<int>(Location.y / BLOCK_SIZE));
	DrawFormatString(10, 50, 0xffffff, "�E���̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((Location.x + XSize) / BLOCK_SIZE), static_cast<int>((Location.y + YSize) / BLOCK_SIZE));
	DrawFormatString(400, 10, 0xffffff, "X %f Y %f", Location.x, Location.y);
	DrawFormatString(10, 100, 0xffffff, "1�F�� 2�F�E 3�F�� 4�F��\n�������� %d", static_cast<int>(Move));
	DrawFormatString(10, 140, 0xffffff, "1�F�� 2�F�E 3�F�� 4�F��\n������������ %d", static_cast<int>(side));
	//DrawFormatString(10, 180, 0xffffff, "�}���I�̏�� %d", static_cast<int>(State));
	DrawFormatString(300, 30, 0xffffff, "kasoku %f speed %f \nYspeed %f Acceleration %f", kasokudo, Speed, YSpeed,IncrementalAccelerationData[index]);

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

	switch (side) //���������u���b�N�̕ӂ̈ʒu
	{
	case HIT_SIDE::LEFT:  //����
		Location.x = vec.x - BLOCK_SIZE;
		flg = false;
		break;
	case HIT_SIDE::RIGHT: //�E��
		Location.x = vec.x + BLOCK_SIZE;
		flg = false;
		break;
	case HIT_SIDE::TOP:   //�㑤
		Location.y = vec.y - YSize;
		Move = MOVE_VECTOR::STOP;
		jState = JUMP_STATE::GROUND;
		Jumping = false;
		flg = false;

		break;
	case HIT_SIDE::UNDER: //����
		Location.y = vec.y + BLOCK_SIZE;
		//�~������
		Move = MOVE_VECTOR::DOWN;
		kasokudo = -0.437;
		YSpeed = InitialSpeed[index];
		break;
	}
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
			Move = MOVE_VECTOR::STOP;
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
			Move = MOVE_VECTOR::STOP;
		}
	}
}

//�W�����v����O�̏���
void Mario::PreparingJump()
{
	Jumping = false;
	jState = JUMP_STATE::SKY;
	Move = MOVE_VECTOR::JUMP;
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
	if (Move == MOVE_VECTOR::JUMP)
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

	float Ground = 0.0f;
	//�n�ʂɒ��n���������f
	if (State == STATE::SMALL)
	{
		Ground = 12 * BLOCK_SIZE;
	}
	else
	{
		Ground = 11 * BLOCK_SIZE;
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

}
