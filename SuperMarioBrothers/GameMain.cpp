#include "DxLib.h"
#include "GameMain.h"
#include "Define.h"

GameMain::GameMain()
{
	mario = new Mario;
	item = new Item * [5];
	for (int i = 0; i < 5; i++)
	{
		item[i] = nullptr;
	}
}

AbstractScene* GameMain::Update()
{
	mario->Update();

	//�}���I����ʂ̔����ɍs�����Ƃ��ɃX�N���[������
	if ((320 <= mario->GetLocation().x) && (0 < mario->GetSpeed()))
	{
		stage.AddScrollX((int)mario->GetSpeed());
	}

	//�X�e�[�W�̃q�b�g�`�F�b�N���O����
	stage.ChackStagePreparation(mario->GetLocation()
		, mario->GetSizeX(), mario->GetSizeY());

	//�}���I�̑����ɒn�ʂ����邩�ǂ������ׂ�
	if (mario->GetJState() != 2 &&
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
		mario->HitStage(stage.GetHitBlock(0),stage.GetHitBlock(1)
			, stage.GetHitSide());
		mario->flg = true;

		//���������ӂ����̎��A�u���b�N�𓮂�������������
		if (stage.GetHitSide() == 4)
		{
			stage.MoveBlockPreparation();
		}

		//�A�C�e��������u���b�N�̎��A�A�C�e�������̉�
		if (stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) == 3
			|| stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) == 5
			|| (30 <= stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) && (stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) <= 32)))
		{
			for (int i = 0; i < 5; i++)
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
	for (int i = 0; i < 5; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Update();
		}
		else
		{
			continue;
		}
	}

	//�A�C�e������ʊO�ɍs������A�C�e��������
	for (int i = 0; i < 5; i++)
	{
		if (item[i] != nullptr)
		{
			if (item[i]->Getlocate().x - stage.GetScroll() < -100)
			{
				delete item[i];
				item[i] = nullptr;
			}
		}
	}

	return this;
}

void GameMain::Draw() const
{
	stage.Draw();
	mario->Draw();
	for (int i = 0; i < 5; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Draw(stage.GetScroll());
		}
	}

#define DEBUG
#ifdef DEBUG
	DrawFormatString(400, 300, 0xffffff, "CStage %d", stage.GetStage(stage.GetHitBlock(0)-1, stage.GetHitBlock(1)));
	//DrawFormatString(400, 300, 0x000000, "move_vector %d", mario->GetMoveVector());
#endif // DEBUG

}