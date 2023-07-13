#include "Mario.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Define.h"

#define SMALL_MARIO_SIZE 32
#define BIG_MARIO_WIDTH_SIZE 32
#define BIG_MARIO_HEIGTH_SIZE 64

Mario::Mario()
{
	//TO DO ��������
	m = 0;
	flg = false;
	//�����܂�
	Location.x = 6 * BLOCK_SIZE;
	Location.y = 12 * BLOCK_SIZE;
	Speed = 0.f;
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
	Move = MOVE_VECTOR::STOP;
	
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
	}
	//�E�ړ�
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)
		|| MARGIN < PadInput::GetThumbLX())
	{
		Move = MOVE_VECTOR::RIGHT;
	}
	//�W�����v
	if (PadInput::OnPressed(XINPUT_BUTTON_B))
	{

		Move = MOVE_VECTOR::JUMP;
	}
	//���Ⴊ��
	if ((State == STATE::BIG || State == STATE::FIRE)
		&& (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN) || PadInput::GetThumbLY() < -MARGIN))
	{
		m = 1;
	}

	/*�X�s�[�h��ω�������*/
	SpeedUp();

	/*���͂��~�߂�����*/
	if (Move == MOVE_VECTOR::STOP)
	{
		SpeedReduction();
	}

	/*�ړ�����*/
	if (0 < Location.x + Speed) //��ʂ���o�Ȃ��悤�ɂ���
	{
		Location.x += Speed;
	}

	//switch (Move)
	//{
	//case MOVE_VECTOR::STOP:
	//	break;
	//case MOVE_VECTOR::LEFT:
	//	if (0 < Location.x - Speed) //��ʂ���o�Ȃ��悤�ɂ���
	//	{
	//		Location.x -= Speed;
	//	}
	//	break;
	//case MOVE_VECTOR::RIGHT:
	//	Location.x += Speed;
	//	break;
	//case MOVE_VECTOR::JUMP:
	//	break;
	//case MOVE_VECTOR::DOWN:
	//	break;
	//}

#define DEBUG
#ifdef DEBUG
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

void Mario::SpeedUp()
{
	const float WALK_MAXSPEED = 3.2f;

	//�ړ������ɂ���ăX�s�[�h��ω�������
	if (Move == MOVE_VECTOR::LEFT)
	{
		Speed -= Inertia;
	}
	else if (Move == MOVE_VECTOR::RIGHT)
	{
		Speed += Inertia;
	}

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
}

void Mario::SpeedReduction()
{
	if (Speed < -0.3f)
	{
		Speed += 0.3f;
	}
	else if (0.09f < Speed)
	{
		Speed -= 0.3f;
	}
	else
	{
		Speed = 0.0f;
	}
}
