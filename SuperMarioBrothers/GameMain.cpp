#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "GameMain.h"
#define STAGE_WIDTH_BLOCK 20
#define STAGE_HEIGHT_BLOCK 15
#define BLOCK_SIZE 32

#include "PadInput.h"

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

	fopen_s(&fp, "StageData/dat.txt", "r");
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
	int h = mario->GetLocation().y;

	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT)
		|| PadInput::GetThumbLX() < -MARGIN)
	{
		//左に移動
		DrawString(0, 0, "PRESSED LEFT\n", 0xffffff);
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT)
		|| MARGIN < PadInput::GetThumbLX())
	{
		//右に移動
		DrawString(0, 0, "PRESSED RIGHT\n", 0xffffff);
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN) || PadInput::GetThumbLY() < -MARGIN)
	{
		//しゃがみ
		DrawString(0, 0, "PRESSED DOWN\n", 0xffffff);
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_A))
	{
		//ダッシュ
		DrawString(0, 0, "PRESSED A\n", 0xffffff);
	}
	if (PadInput::OnPressed(XINPUT_BUTTON_B))
	{
		//ジャンプ
		DrawString(0, 0, "PRESSED B\n", 0xffffff);
	}

	//for (int h = 0; h < STAGE_HEIGHT_BLOCK; h++)
	//{
	//	for (int w = 0; w < STAGE_WIDTH_BLOCK; w++)
	//	{
	//		if (Stage[h][w] != 0)
	//		{
	//			if (mario->ChackHitStage(static_cast<float>(w * BLOCK_SIZE), static_cast<float>(h * BLOCK_SIZE), BLOCK_SIZE, BLOCK_SIZE, mario->GetMoveVector()))
	//			{
	//				mario->flg = true;

	//				switch (mario->GetHitVector())
	//				{
	//				case 1:
	//				case 2:
	//					mario->Hit(w, 0);
	//					break;
	//				case 3:
	//				case 4:
	//					mario->Hit(0, h);
	//					break;
	//				}
	//				goto hitcheck_end;
	//			}
	//			else
	//			{
	//				mario->flg = false;
	//				mario->InitHitVector();
	//			}
	//		}
	//	}
	//}
	//hitcheck_end:

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
