#include "Item.h"
#include "DxLib.h"
#include "Define.h"

Item::Item()
{
	UpEnd = false;
	XSize = BLOCK_SIZE;
	YSize = BLOCK_SIZE;
	UpSpeed = 0.0f;
	Speed = 1.0f;
	Move = MOVE_VECTOR::STOP;

	//�摜�̓ǂݍ���
	if (LoadImages() == -1)
	{
		perror("LoadImage Error");
		throw;
	}
}

Item::Item(int block_y, int block_x
	,int stage_num, int player_state,int scroll)
{
	Move = MOVE_VECTOR::STOP;
	UpEnd = false;
	Speed = 1.0f;
	FallSpeed = 4.0f;
	XSize = BLOCK_SIZE;
	YSize = BLOCK_SIZE;
	Location.y = (float)block_y * BLOCK_SIZE;
	Location.x = (float)block_x * BLOCK_SIZE;
	StartLocate = Location;

	switch (stage_num)
	{
	case 3:   //�R�C��
	case 31:
		ItemType = ITEM_TYPE::COIN;
		break;
	case 5:   //1UP�L�m�R
		ItemType = ITEM_TYPE::UP_MUSHROOM;
		break;
	case 30:  //�L�m�R�E�t�����[
		//�}���I���������T�C�Y�ȊO�Ȃ�t�����[���o��
		if (0 < player_state)
		{
			ItemType = ITEM_TYPE::FLOWER;
		}
		else  //�}���I���������Ȃ�L�m�R���o��
		{
			ItemType = ITEM_TYPE::MUSHROOM;
		}
		break;
	case 32:  //�X�^�[
		ItemType = ITEM_TYPE::STAR;
		break;
	}

	if (ItemType == ITEM_TYPE::COIN)
	{
		UpSpeed = 5.0f;
	}
	else
	{
		UpSpeed = 0.8f;
	}

	//�摜�̓ǂݍ���
	if (LoadImages() == -1)
	{
		perror("LoadImage Error");
		throw;
	}
}

void Item::Update()
{
	//��ɂ�����
	if (!UpEnd)
	{
		Location.y -= UpSpeed;
		if (ItemType == ITEM_TYPE::COIN)
		{
			if (Location.y < StartLocate.y - BLOCK_SIZE * 3)
			{
				UpSpeed = -UpSpeed;
			}
			if (StartLocate.y < Location.y)
			{
				Location.y = StartLocate.y;
				Move = MOVE_VECTOR::STOP;
				UpEnd = true;
			}
		}
		else
		{
			if (Location.y < StartLocate.y - BLOCK_SIZE)
			{
				Move = MOVE_VECTOR::RIGHT;
				UpEnd = true;
				//kasokudo = IncrementalAcceleration;
			}
		}
	}

	//��ɏオ��؂�����
	//�R�C���ƃt�����[�ȊO�͈ړ�������
	if (ItemType != ITEM_TYPE::COIN && ItemType != ITEM_TYPE::FLOWER)
	{

		if (UpEnd)
		{
			if (Move != MOVE_VECTOR::STOP)
			{
				Location.x += Speed;
			}

			/*if (ItemType == ITEM_TYPE::STAR)
			{
				IsAir = true;
				StarJump();
			}*/

			if (Move == MOVE_VECTOR::DOWN)
			{
				Location.y += FallSpeed;
			}
		}
	}

	//�L�m�R�E1UP�L�m�R�ȊO�̓A�j���[�V�������X�V����
	if (ItemType != ITEM_TYPE::MUSHROOM && ItemType != ITEM_TYPE::UP_MUSHROOM)
	{
		Animation();
	}
}

void Item::Draw(int scroll) const
{
	switch (ItemType)
	{
	case ITEM_TYPE::MUSHROOM:
		DrawGraphF(Location.x - scroll, Location.y, Mushroom, TRUE);
		break;
	case ITEM_TYPE::UP_MUSHROOM:
		DrawGraphF(Location.x- scroll, Location.y, UP_Mushroom, TRUE);
		break;
	case ITEM_TYPE::COIN:
		DrawGraphF(Location.x - scroll, Location.y, Coin[aIndex], TRUE);
		break;
	case ITEM_TYPE::M_COIN:
		DrawGraphF(Location.x - scroll, Location.y, M_Coin[aIndex], TRUE);
		break;
	case ITEM_TYPE::FLOWER:
		DrawGraphF(Location.x - scroll, Location.y, Flower[aIndex], TRUE);
		break;
	case ITEM_TYPE::STAR:
		DrawGraphF(Location.x - scroll, Location.y, Star[aIndex], TRUE);
		break;
	}

#define DEBUG
#ifndef DEBUG
	DrawFormatString(0, 200, 0xffffff, "yspeed %d", YSpeed);

	DrawBox(Location.x - scroll, Location.y, Location.x + XSize-scroll, Location.y + YSize, 0xff0000, FALSE);
	DrawFormatString(0, 150, 0xffffff, "IMoveVector %d", (int)Move);
	DrawFormatString(0, 20, 0xffffff, "���� X %d Y %d", ((int)Location.x-XSize/2) / BLOCK_SIZE,((int)Location.y-YSize/2)/BLOCK_SIZE);
	DrawFormatString(0, 40, 0xffffff, "�E�� X %d Y %d", ((int)Location.x + (XSize / 2-1)) / BLOCK_SIZE, ((int)Location.y + (YSize / 2-1)) / BLOCK_SIZE);
	DrawFormatString(300, 20, 0xffffff, "���W X %f Y %f", Location.x, Location.y);
#endif // DEBUG

}

void Item::HitStage(int h_block, int w_block
	, int hit_side, int scroll)
{
	VECTOR vec;

	vec.y = static_cast<float>(h_block * BLOCK_SIZE);
	vec.x = static_cast<float>(w_block * BLOCK_SIZE);

	switch (hit_side) //���������u���b�N�̕ӂ̈ʒu
	{
	case 1:  //����
		Location.x = vec.x - BLOCK_SIZE+scroll;
		Inversion();
		break;
	case 2: //�E��
		Location.x = vec.x + BLOCK_SIZE + scroll;
		Inversion();
		break;
	case 3:   //�㑤
		//�o�����o���I����Ă��Ȃ���������W�C���͂��Ȃ�
		if (!UpEnd) break;

		Location.y = vec.y - YSize;
		IsAir = false;
		if (Speed < 0) //�i�s������Move��ύX
		{
			Move = MOVE_VECTOR::LEFT;
		}
		else
		{
			Move = MOVE_VECTOR::RIGHT;
		}

		if (ItemType == ITEM_TYPE::STAR)
		{
			kasokudo = -IncrementalAcceleration;
		}
		break;
	case 4: //����
		Location.y = vec.y + YSize;
		//�~������
		Move = MOVE_VECTOR::DOWN;
		break;
	}
}

void Item::Fall()
{
	Move = MOVE_VECTOR::DOWN;
	IsAir = true;
	//Location.y += FallSpeed;
}

void Item::Inversion()
{
	if (Move == MOVE_VECTOR::LEFT)
	{
		Move = MOVE_VECTOR::RIGHT;//�i�s�����𔽓]����
	}
	if (Move == MOVE_VECTOR::RIGHT)
	{
		Move = MOVE_VECTOR::LEFT; //�i�s�����𔽓]����
	}

	Speed *= -1;
}

void Item::Animation()
{
	if (AnimSpeed/4 < ++AnimWait)
	{
		if (3 < ++aIndex)
		{
			aIndex = 0;
		}
		AnimWait = 0;
	}
}

void Item::StarJump()
{
	//���������߂�    1�t���[�� = 0.016�b
	//Y���W
	YSpeed += kasokudo;

	Location.y += YSpeed;

	//X���W
	//Location.x += XSpeed * 0.016;

	//���~����^�C�~���O�𔻒f
	if (0 < YSpeed)
	{
		kasokudo = IncrementalAcceleration;
	}
}

int Item::LoadImages()
{
	if ((Mushroom = LoadGraph("1-1image/Item/mushroom.png")) == -1) return -1;
	if ((UP_Mushroom = LoadGraph("1-1image/Item/1up_mushroom.png")) == -1) return -1;
	if (LoadDivGraph("1-1image/Item/coin.png", 4, 4, 1, 32, 32, Coin) == -1) return -1;
	if (LoadDivGraph("1-1image/Item/mukidasitika_coin.png", 4, 4, 1, 32, 32, M_Coin) == -1) return -1;
	if (LoadDivGraph("1-1image/Item/flower.png", 4, 4, 1, 32, 32, Flower) == -1) return -1;
	if (LoadDivGraph("1-1image/Item/star.png", 4, 4, 1, 32, 32, Star) == -1) return -1;

	return 0;
}
