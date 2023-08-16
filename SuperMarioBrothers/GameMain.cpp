#include "DxLib.h"
#include "GameMain.h"
#include "Define.h"

GameMain::GameMain()
{
	mario = new Mario;

	
}

AbstractScene* GameMain::Update()
{
	mario->Update();

	//�}���I����ʂ̔����ɍs�����Ƃ��ɃX�N���[������
	if ((320 <= mario->GetLocation().x) && (0 < mario->GetSpeed()))
	{
		stage.AddScrollX((int)mario->GetSpeed());
	}

	//���O����
	stage.ChackStagePreparation(mario->GetLocation()
		, mario->GetSizeX(), mario->GetSizeY());

	if (mario->GetJState() != 2 &&
		(mario->GetMoveVector() < 3 || mario->GetMoveVector() == 4))
	{
		//�����ɒn�ʂ����邩�ǂ������ׂ�
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
	}
	else
	{
		mario->flg = false;
	}

	//�u���b�N������
	stage.MoveBlock();

	return this;
}

void GameMain::Draw() const
{
	stage.Draw();
	mario->Draw();

#define DEBUG
#ifndef DEBUG
	DrawFormatString(400, 300, 0x000000, "move_vector %d", mario->GetMoveVector());
#endif // DEBUG

}