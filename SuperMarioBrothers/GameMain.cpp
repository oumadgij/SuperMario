#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "GameMain.h"
#include "Define.h"

GameMain::GameMain()
{
	mario = new Mario;

	if (LoadStages() == -1)
	{
		perror("LoadStage Error");
		throw;
	}

	if(LoadImages()==-1)
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
		if (mario->ChackUnder(Stage, ScrollX))
		{
			mario->Fall();
		}
	}

	mario->Update();
	

	//�}���I�ƃX�e�[�W�u���b�N�̓����蔻��
	if (mario->ChackHitStage(Stage,mario->GetJState(),mario->GetMoveVector(),ScrollX))
	{
		mario->HitStage();
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
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{	
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			//�w�i��`��
			DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, BackImages[BackData[i][j]], TRUE);

			//�X�e�[�W��`��
			switch (Stage[i][j])
			{
			case 1:  //�t���A�u���b�N
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Floor, TRUE);
				break;
			case 2:  //���ʂ̃u���b�N
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Block, TRUE);
				break;
			case 3:  //�n�e�i�u���b�N
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, QuestionBlock[0], TRUE);
				break;
			case 4:  //��u���b�N
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, EmptyBlock, TRUE);
				break;
			case 6:  //�K�i�u���b�N
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, StairsBlock, TRUE);
				break;
			case 7:  //�y��
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[0], TRUE);
				break;
			case 8:	//�y��
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[1], TRUE);
				break;
			case 9:	//�y��
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[2], TRUE);
				break;
			case 10://�y��
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[3], TRUE);
				break;
			}
		}
	}

	mario->Draw();

#define DEBUG
#ifdef DEBUG
	//DrawFormatString(10, 10, 0xffffff, "����̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((mario->GetLocation().x - mario->GetSizeX() / 2) / BLOCK_SIZE + ScrollX / BLOCK_SIZE), static_cast<int>((mario->GetLocation().y - mario->GetSizeY() / 2) / BLOCK_SIZE));
	DrawFormatString(400, 300, 0x000000, "move_vector %d", mario->GetMoveVector());
	DrawFormatString(10, 10, 0xffffff, "�����̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((mario->GetLocation().x - mario->GetSizeX() / 2) / BLOCK_SIZE + ScrollX / BLOCK_SIZE), static_cast<int>((mario->GetLocation().y + mario->GetSizeY() / 2) / BLOCK_SIZE));
	DrawFormatString(10, 50, 0xffffff, "�E���̃X�e�[�W�ʒu\nX %d Y %d", static_cast<int>((mario->GetLocation().x + mario->GetSizeX() / 2 - 1) / BLOCK_SIZE + ScrollX / BLOCK_SIZE), static_cast<int>((mario->GetLocation().y + (mario->GetSizeY() / 2)) / BLOCK_SIZE));
#endif // DEBUG

}

int GameMain::LoadStages()
{
	FILE* fp;
	char buf[1000];
	char* p;
	int i = 0, ret;
	int j = 0;

	//�X�e�[�W�f�[�^��ǂݍ���
	fopen_s(&fp, "StageData/Stage.csv", "r");
	if (fp == NULL)
	{
		perror("LoadFile Error");
		return -1;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		p = strtok(buf, ",");
		ret = sscanf(p, "%d", &Stage[i][j++]);

		while (p != NULL)
		{
			p = strtok(NULL, ",");
			if (p != NULL)
			{
				ret = sscanf(p, "%d", &Stage[i][j++]);
			}
		}

		++i;
		j = 0;
	}
	fclose(fp);

	//�w�i�f�[�^��ǂݍ���
	i = 0;
	j = 0;
	fopen_s(&fp, "StageData/BackGround.csv", "r");
	if (fp == NULL)
	{
		return -1;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		p = strtok(buf, ",");
		ret = sscanf(p, "%d", &BackData[i][j++]);

		while (p != NULL)
		{
			p = strtok(NULL, ",");
			if (p != NULL)
			{
				ret = sscanf(p, "%d", &BackData[i][j++]);
			}
		}

		++i;
		j = 0;
	}
	fclose(fp);

	return 0;
}

int GameMain::LoadImages()
{
	//�u���b�N
	if ((Block = LoadGraph("1-1image/Block/block.png")) == -1) return -1;
	if ((Floor = LoadGraph("1-1image/Block/floor.png")) == -1) return -1;
	if ((StairsBlock = LoadGraph("1-1image/Block/kai_block.png")) == -1) return -1;
	if ((EmptyBlock = LoadGraph("1-1image/Block/kara_block.png")) == -1) return -1;
	if ((DebrisBlock = LoadGraph("1-1image/Block/bloak_1.png")) == -1) return -1;
	if ((b_Block = LoadGraph("1-1image/Block/blackblock.png")) == -1) return -1;
	if ((b_Floor = LoadGraph("1-1image/Block/tika_floor.png")) == -1) return -1;
	if ((Pipe[0] = LoadGraph("1-1image/dokan_left_up.png")) == -1) return -1;
	if ((Pipe[1] = LoadGraph("1-1image/dokan_right_up.png")) == -1) return -1;
	if ((Pipe[2] = LoadGraph("1-1image/dokan_left_down.png")) == -1) return -1;
	if ((Pipe[3] = LoadGraph("1-1image/dokan_right_down.png")) == -1) return -1;
	if (LoadDivGraph("1-1image/Block/hatena.png", 4, 4, 1, 32, 32, QuestionBlock) == -1) return -1;
	/*�w�i*/
	//��
	if ((BackImages[0] = LoadGraph("1-1image/sora.png")) == -1) return -1;
	//��
	if ((BackImages[1] = LoadGraph("1-1image/ha0.png")) == -1) return -1;
	if ((BackImages[2] = LoadGraph("1-1image/ha1.png")) == -1) return -1;
	if ((BackImages[3] = LoadGraph("1-1image/ha2.png")) == -1) return -1;
	//�R
	if ((BackImages[4] = LoadGraph("1-1image/mountain_left.png")) == -1) return -1;
	if ((BackImages[5] = LoadGraph("1-1image/mountain_right.png")) == -1) return -1;
	if ((BackImages[6] = LoadGraph("1-1image/mountain_up.png")) == -1) return -1;
	if ((BackImages[7] = LoadGraph("1-1image/mountain_surface.png")) == -1) return -1;
	if ((BackImages[8] = LoadGraph("1-1image/mountain_surface1.png")) == -1) return -1;
	if ((BackImages[9] = LoadGraph("1-1image/mountain_surface2.png")) == -1) return -1;
	//�_
	if ((BackImages[10] = LoadGraph("1-1image/cloud6.png")) == -1) return -1;
	if ((BackImages[11] = LoadGraph("1-1image/cloud5.png")) == -1) return -1;
	if ((BackImages[12] = LoadGraph("1-1image/cloud4.png")) == -1) return -1;
	if ((BackImages[13] = LoadGraph("1-1image/cloud1.png")) == -1) return -1;
	if ((BackImages[14] = LoadGraph("1-1image/cloud2.png")) == -1) return -1;
	if ((BackImages[15] = LoadGraph("1-1image/cloud3.png")) == -1) return -1;
	

	return 0;
}
