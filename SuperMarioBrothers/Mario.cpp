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
	JumpStartPosition = 0.0f;
	Jumping = false;
	//�����܂�
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
	if (Jumping)
	{
		Jump();
	}

	/*�ړ�����*/
	if (Move == MOVE_VECTOR::STOP)  //�����Ă��Ȃ��A��ʂ�
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
	DrawFormatString(10, 10, 0xffffff, "����̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>(Location.x / BLOCK_SIZE), static_cast<int>(Location.y / BLOCK_SIZE));
	DrawFormatString(10, 50, 0xffffff, "�E���̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((Location.x + XSize) / BLOCK_SIZE), static_cast<int>((Location.y + YSize) / BLOCK_SIZE));
	DrawFormatString(400, 10, 0xffffff, "X %f Y %f", Location.x, Location.y);
	DrawFormatString(10, 100, 0xffffff, "1�F�� 2�F�E 3�F�� 4�F��\n�������� %d", static_cast<int>(Move));
	DrawFormatString(10, 140, 0xffffff, "1�F�� 2�F�E 3�F�� 4�F��\n������������ %d", static_cast<int>(side));

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
		break;
	case HIT_SIDE::RIGHT: //�E��
		Location.x = vec.x + BLOCK_SIZE;
		break;
	case HIT_SIDE::TOP:   //�㑤
		Location.y = vec.y - YSize;
		break;
	case HIT_SIDE::UNDER: //����
		Location.y = vec.y + BLOCK_SIZE;
		//�~������
		Move = MOVE_VECTOR::DOWN;
		kasokudo = -0.437;
		InitialSpeed = 4;
		break;
	}

	Move = MOVE_VECTOR::STOP;
	flg = false;
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

//�W�����v����O�̏���
void Mario::PreparingJump()
{
	kasokudo = 0.125f;
	InitialSpeed = -4.0f;
	index = 0;
	time = 0.016f;
	Move = MOVE_VECTOR::JUMP;
}

//�W�����v����
void Mario::Jump()
{
	//������������
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

	//�~�����x�𒲐�����
	if ((Move == MOVE_VECTOR::DOWN) && kasokudo == MaxFallSpeed)
	{
		kasokudo = MaxFallSpeed;
	}

	//���������߂�    1�t���[�� = 0.016�b
	//Y���W
	Location.y += InitialSpeed * time + 0.5 * kasokudo * pow(time, 2);
	//X���W
	//Location.x += 0.5 * Inertia * pow(time, 2) + Speed * time;

	//���~����^�C�~���O�𔻒f
	if (Location.y < 150)//MAX_SMALL_JUMP
	{
		Location.y = 150;//MAX_SMALL_JUMP
		kasokudo = -0.437;
		InitialSpeed = 4;
	}

	//�n�ʂɒ��n���������f
	float Ground = 12 * BLOCK_SIZE;
	if (Ground < Location.y)
	{
		Location.y = Ground;
		Jumping = false;
	}

	time += 0.01;
}

////������������
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
////�~�����x�𒲐�����
//if ((Move == MOVE_VECTOR::DOWN) && kasokudo == MaxFallSpeed)
//{
//	kasokudo = MaxFallSpeed;
//}
//
////���������߂�    1�t���[�� = 0.016�b
////Y���W
//Location.y += InitialSpeed * 1.5 + 0.5 * kasokudo * pow(0.016, 2);
////X���W
//Location.x += 0.5 * Inertia * pow(0.016, 2) + Speed * 0.016;
//
////���~����^�C�~���O�𔻒f
//if (Location.y < 150)//MAX_SMALL_JUMP
//{
//	Location.y = 150;//MAX_SMALL_JUMP
//	kasokudo = -0.437;
//	InitialSpeed = 4;
//}
//
////�n�ʂɒ��n���������f
//float Ground = 12 * BLOCK_SIZE;
//if (Ground < Location.y)
//{
//	Location.y = Ground;
//	Jumping = false;
//}
