#include "DxLib.h"
#include "GameMain.h"
#include "Define.h"

#define MAX_ITEM 5

GameMain::GameMain()
{
	mario = new Mario;
	item = new Item * [MAX_ITEM];
	for (int i = 0; i < MAX_ITEM; i++)
	{
		item[i] = nullptr;
	}
}

AbstractScene* GameMain::Update()
{
	//�}���I�̃A�b�v�f�[�g
	mario->Update();

	//�}���I����ʂ̔����ɍs�����Ƃ��ɃX�N���[������
	if ((320 <= mario->GetLocation().x) && (0 < mario->GetSpeed()))
	{
		stage.AddScrollX((int)mario->GetSpeed());
	}

	//�}���I�̃X�e�[�W�̃q�b�g�`�F�b�N���O����
	stage.ChackStagePreparation(mario->GetLocation()
		, mario->GetSizeX(), mario->GetSizeY());

	//�}���I�̑����ɒn�ʂ����邩�ǂ������ׂ�
	if (!mario->GetIsAir() &&
		(mario->GetMoveVector() < 3 || mario->GetMoveVector() == 4))
	{
		if (stage.ChackUnder())
		{
			mario->Fall();
		}
	}

	//�}���I�ƃX�e�[�W�u���b�N�̓����蔻��
	if (stage.ChackHitStage(mario->GetMoveVector()))
	{
		//�}���I�̈ʒu��߂�
		mario->HitStage(stage.GetHitBlock(0), stage.GetHitBlock(1)
			, stage.GetHitSide(), 0);
		mario->flg = true;

		//���������ӂ����̎��A�u���b�N�𓮂�������������
		if (stage.GetHitSide() == 4)
		{
			stage.MoveBlockPreparation();

			//�@���ꂽ�u���b�N�̐^��ɃA�C�e����������i�s�����𔽓]
			for (int i = 0; i < MAX_ITEM; i++)
			{
				if (item[i] != nullptr)
				{
					if ((stage.GetPushBlock(0) == (int)item[i]->GetLocation().x / BLOCK_SIZE)
						&& (stage.GetPushBlock(1) == (int)item[i]->GetLocation().y / BLOCK_SIZE))
					{
						item[i]->Inversion();
					}
				}
			}
		}

		//�A�C�e��������u���b�N�̎��A�A�C�e�������̉�
		if (stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) == 3
			|| stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) == 5
			|| (30 <= stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1))
			&& stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) <= 32))
		{
			for (int i = 0; i < MAX_ITEM; i++)
				{
					if (item[i] == nullptr)
					{
						item[i] = new Item(stage.GetPushBlock(0), stage.GetPushBlock(1)
							, stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)), mario->GetStage()
							, stage.GetScroll());
						break;
					}
				}
		}
	}
	else
	{
		mario->flg = false;
	}

	//�u���b�N������
	stage.MoveBlock();

	//�A�C�e���̃A�b�v�f�[�g
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Update();

			//�R�C���̏o�����o���I�������R�C���̐��𑝂₵�ăR�C��������
			if (item[i]->GetItemType() == 3 && item[i]->GetCoinUpEnd())
			{
				mario->Hit(item[i]->GetItemType());
				DeleteItem(i);
				continue;
			}

			//�A�C�e���̃X�e�[�W�q�b�g�`�F�b�N���O����
			stage.ItemChackStagePreparation(item[i]->GetLocation()
				, item[i]->GetSizeX(), item[i]->GetSizeY());

			//����
			if (0 < item[i]->GetMoveVector() && item[i]->GetMoveVector() < 3)
			{
				if (stage.ChackUnder())
				{
					item[i]->Fall();
				}
			}

			//�A�C�e���ƃX�e�[�W�u���b�N�̓����蔻��
			if (stage.ChackHitStage(item[i]->GetMoveVector()))
			{
				//�A�C�e���̈ʒu��߂�
				item[i]->HitStage(stage.GetHitBlock(0), stage.GetHitBlock(1)
					, stage.GetHitSide(),stage.GetScroll());
			}

			//�A�C�e������ʊO�ɍs������A�C�e��������
			if (item[i]->GetLocation().x - stage.GetScroll() < -100)
			{
				DeleteItem(i);
			}
		}
	}

	HitChack();

	return this;
}

void GameMain::Draw() const
{
	stage.Draw();
	mario->Draw();
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Draw(stage.GetScroll());
		}
	}

#define DEBUG
#ifdef DEBUG
	DrawFormatString(400, 300, 0xffffff, "CStage %d", stage.GetStage(stage.GetHitBlock(0)-1, stage.GetHitBlock(1)));
	
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (item[i] != nullptr)
		{
			DrawFormatString(0, 100, 0xffffff, "MoveVector %d", item[i]->GetMoveVector());
		}
	}
	//DrawFormatString(400, 300, 0x000000, "move_vector %d", mario->GetMoveVector());
#endif // DEBUG

}

void GameMain::HitChack()
{
	//�}���I�ƃA�C�e���̓����蔻��
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (item[i] != nullptr)
		{
			//����������
			if (mario->ChackHitBox(item[i]->GetLocation(), item[i]->GetSizeX()
				, item[i]->GetSizeY(),stage.GetScroll()))
			{
				mario->Hit(item[i]->GetItemType());

				//�A�C�e��������
				DeleteItem(i);
			}
		}
	}

}
