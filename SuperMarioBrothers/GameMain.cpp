#include "DxLib.h"
#include "GameMain.h"
#include "Define.h"

GameMain::GameMain()
{
	mario = new Mario;

	//�f�[�^�̓ǂݍ���
	if (stage.LoadStages(StageData) == -1)
	{
		perror("LoadStage Error");
		throw;
	}
	if (stage.LoadBack(BackData) == -1)
	{
		perror("LoadBack Error");
		throw;
	}
	//�摜�̓ǂݍ���
	if(stage.LoadImages()==-1)
	{
		perror("LoadImage Error");
		throw;
	}
}

AbstractScene* GameMain::Update()
{
	if (mario->GetJState() != 2 && 
		(mario->GetMoveVector() < 3 || mario->GetMoveVector() == 4))
	{
		if (stage.ChackUnder(StageData, ScrollX
			, mario->GetLocation(), mario->GetSizeX()
			, mario->GetSizeY()))
		{
			mario->Fall();
		}
	}

	mario->Update();
	

	//�}���I�ƃX�e�[�W�u���b�N�̓����蔻��
	if (stage.ChackHitStage(StageData, mario->GetJState()
		, mario->GetLocation(), mario->GetSizeX()
		, mario->GetSizeY(), mario->GetMoveVector(), ScrollX))
	{
		mario->HitStage(stage.GetHitBlock(0),stage.GetHitBlock(1)
			, stage.GetHitSide());
		mario->flg = true;
	}
	else
	{
		mario->flg = false;
	}

	//�}���I����ʂ̔����ɍs�����Ƃ��ɃX�N���[������
	if ((320 <= mario->GetLocation().x)&& (0 < mario->GetSpeed()))
	{
		ScrollX += mario->GetSpeed();
	}

	return this;
}

void GameMain::Draw() const
{
	stage.Draw(StageData, BackData, ScrollX);
	mario->Draw();

#define DEBUG
#ifdef DEBUG
	//DrawFormatString(10, 10, 0xffffff, "����̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((mario->GetLocation().x - mario->GetSizeX() / 2) / BLOCK_SIZE + ScrollX / BLOCK_SIZE), static_cast<int>((mario->GetLocation().y - mario->GetSizeY() / 2) / BLOCK_SIZE));
	DrawFormatString(400, 300, 0x000000, "move_vector %d", mario->GetMoveVector());
	DrawFormatString(10, 10, 0xffffff, "�����̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((mario->GetLocation().x - mario->GetSizeX() / 2) / BLOCK_SIZE + ScrollX / BLOCK_SIZE), static_cast<int>((mario->GetLocation().y + mario->GetSizeY() / 2) / BLOCK_SIZE));
	DrawFormatString(10, 50, 0xffffff, "�E���̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((mario->GetLocation().x + mario->GetSizeX() / 2 - 1) / BLOCK_SIZE + ScrollX / BLOCK_SIZE), static_cast<int>((mario->GetLocation().y + (mario->GetSizeY() / 2)) / BLOCK_SIZE));
#endif // DEBUG

}