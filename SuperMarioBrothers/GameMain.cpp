#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "GameMain.h"
#include "Define.h"

GameMain::GameMain()
{
	mario = new Mario;

	for (int i = 0; i < STAGE_HEIGHT_BLOCK; i++)
	{
		for (int j = 0; j < STAGE_WIDTH_BLOCK; j++)
		{
			Stage[i][j] = -1;
		}
	}

	FILE* fp;
	char buf[41];
	int i = 0, ret;

	fopen_s(&fp, "StageData/仮ステージ1.txt", "r");
	if (fp == NULL)
	{
		throw "LoadFile Error";
	}

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		ret = sscanf(buf, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"
			, &Stage[i][0], &Stage[i][1], &Stage[i][2], &Stage[i][3], &Stage[i][4], &Stage[i][5], &Stage[i][6], &Stage[i][7], &Stage[i][8], &Stage[i][9]
			, &Stage[i][10], &Stage[i][11], &Stage[i][12], &Stage[i][13], &Stage[i][14], &Stage[i][15], &Stage[i][16], &Stage[i][17], &Stage[i][18], &Stage[i][19]);
		i++;
	}
	fclose(fp);

	BlockImg[0] = LoadGraph("1-1image/Block/block.png");
	BlockImg[1] = LoadGraph("1-1image/Block/floor.png");
	BlockImg[2] = LoadGraph("1-1image/Block/kai_block.png");
}

AbstractScene* GameMain::Update()
{
	mario->Update();

	//マリオとステージブロックの当たり判定
	if (mario->ChackHitStage(Stage,mario->GetMoveVector()))
	{
		mario->HitStage();
		mario->flg = true;
	}
	else
	{
		mario->flg = false;
	}

	return this;
}

void GameMain::Draw() const
{
	for (int i = 0; i < STAGE_HEIGHT_BLOCK; i++)
	{
		for (int j = 0; j < STAGE_WIDTH_BLOCK; j++)
		{
			if (Stage[i][j] == 1)
			{
				DrawGraph(j * BLOCK_SIZE, i * BLOCK_SIZE, BlockImg[0], TRUE);
			}
			else if (Stage[i][j] == 2)
			{
				DrawGraph(j * BLOCK_SIZE, i * BLOCK_SIZE, BlockImg[1], TRUE);
			}
			else if (Stage[i][j] == 3)
			{
				DrawGraph(j * BLOCK_SIZE, i * BLOCK_SIZE, BlockImg[2], TRUE);
			}
		}
	}

	mario->Draw();
}
