#include "DxLib.h"
#include "GameMain.h"
#include "Define.h"

GameMain::GameMain()
{
	mario = new Mario;

	
}

AbstractScene* GameMain::Update()
{
	if (mario->GetJState() != 2 && 
		(mario->GetMoveVector() < 3 || mario->GetMoveVector() == 4))
	{
		if (stage.ChackUnder( ScrollX
			, mario->GetLocation(), mario->GetSizeX()
			, mario->GetSizeY()))
		{
			mario->Fall();
		}
	}

	mario->Update();
	

	//�}���I�ƃX�e�[�W�u���b�N�̓����蔻��
	if (stage.ChackHitStage(mario->GetJState()
		, mario->GetLocation(), mario->GetSizeX()
		, mario->GetSizeY(), mario->GetMoveVector(), ScrollX))
	{
		mario->HitStage(stage.GetHitBlock(0),stage.GetHitBlock(1)
			, stage.GetHitSide());
		mario->flg = true;
		if (stage.GetHitSide() == 4)
		{
			stage.MoveBlockPreparation(ScrollX);
		}
	}
	else
	{
		mario->flg = false;
	}
	//�u���b�N������
	stage.MoveBlock();

	//�}���I����ʂ̔����ɍs�����Ƃ��ɃX�N���[������
	if ((320 <= mario->GetLocation().x)&& (0 < mario->GetSpeed()))
	{
		ScrollX += mario->GetSpeed();
	}

	return this;
}

void GameMain::Draw() const
{
	stage.Draw(ScrollX);
	mario->Draw();

#define DEBUG
#ifdef DEBUG
	DrawFormatString(400, 250, 0x000000, "scroll %f", ScrollX);
	//DrawFormatString(400, 300, 0x000000, "move_vector %d", mario->GetMoveVector());
	DrawFormatString(10, 10, 0xffffff, "�����̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((mario->GetLocation().x - mario->GetSizeX() / 2) / BLOCK_SIZE + ScrollX / BLOCK_SIZE), static_cast<int>((mario->GetLocation().y + mario->GetSizeY() / 2) / BLOCK_SIZE));
	DrawFormatString(10, 50, 0xffffff, "�E���̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((mario->GetLocation().x + mario->GetSizeX() / 2 - 1) / BLOCK_SIZE + ScrollX / BLOCK_SIZE), static_cast<int>((mario->GetLocation().y + (mario->GetSizeY() / 2)) / BLOCK_SIZE));
#endif // DEBUG

}