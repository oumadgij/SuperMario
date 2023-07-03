#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "GameMain.h"
#define STAGE_WIDTH_BLOCK 20
#define STAGE_HEIGHT_BLOCK 15

GameMain::GameMain()
{
	FILE* fp;
	char buf[100];
	int ret;
	int h = 0;

	fopen_s(&fp, "StageData/dat.txt", "r");

	if (fp == NULL)
	{
		printf("ファイル読み込みエラー\n");
	}
	else
	{
		while (fgets(buf, 100, fp) != NULL)
		{
			ret = sscanf(buf, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n"
				, &Stage[h][0], &Stage[h][1], &Stage[h][2], &Stage[h][3], &Stage[h][4], &Stage[h][5], &Stage[h][6], &Stage[h][7], &Stage[h][8], &Stage[h][9]
				, &Stage[h][0], &Stage[h][11], &Stage[h][12], &Stage[h][13], &Stage[h][14], &Stage[h][15], &Stage[h][16], &Stage[h][17], &Stage[h][18], &Stage[h][19]);
			++h;
		}
	}

	fclose(fp);
}

AbstractScene* GameMain::Update()
{
	return nullptr;
}

void GameMain::Draw() const
{
}
