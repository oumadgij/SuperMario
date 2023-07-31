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

	//スクロールするんだけど、なんか硬い
	//マリオのスピードと同じくらいの速さとぬるぬる感でスクロールさせたい

	//マリオが画面の半分に行ったときにスクロールする
	if ((320 <= mario->GetLocation().x)&& (0 < mario->GetSpeed()))
	{
		s_ScrollX += mario->GetSpeed();
		b_ScrollX1 -= mario->GetSpeed();
		//背景の最後のブロックが見える位置まできたら
		//スクロール2を加算する
		b_ScrollX2 -= mario->GetSpeed();

		//背景が全て見えなくなるまできたら
		//スクロール1を0にする
		int h = BACK_WIDTH * BLOCK_SIZE * -1;
		if (b_ScrollX1 < h)
		{
			b_ScrollX1 = 0;
		}
		if (b_ScrollX2 < 0)
		{
			b_ScrollX2 = BACK_WIDTH * BLOCK_SIZE;
		}

		////スクロール量を制限
		//if (WINDOW_WIDTH < b_ScrollX2)
		//{
		//	b_ScrollX1 = 0;
		//}
		//if (WINDOW_WIDTH < b_ScrollX1)
		//{
		//	b_ScrollX2 = 0;
		//}
	}

	return this;
}

void GameMain::Draw() const
{
	Scroll(b_ScrollX1,WINDOW_WIDTH);
	Scroll(b_ScrollX2, 0);

	//ステージ描画
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{	
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			switch (Stage[i][j])
			{
			case 1:  //フロアブロック
				DrawGraph(j * BLOCK_SIZE - s_ScrollX, i * BLOCK_SIZE, Floor, TRUE);
				break;
			case 2:  //普通のブロック
				DrawGraph(j * BLOCK_SIZE - s_ScrollX, i * BLOCK_SIZE, Block, TRUE);
				break;
			case 3:  //ハテナブロック
				DrawGraph(j * BLOCK_SIZE - s_ScrollX, i * BLOCK_SIZE, QuestionBlock[0], TRUE);
				break;
			case 4:  //空ブロック
				DrawGraph(j * BLOCK_SIZE - s_ScrollX, i * BLOCK_SIZE, EmptyBlock, TRUE);
				break;
			case 6:  //階段ブロック
				DrawGraph(j * BLOCK_SIZE - s_ScrollX, i * BLOCK_SIZE, StairsBlock, TRUE);
				break;
			case 7:  //土管
				DrawGraph(j * BLOCK_SIZE - s_ScrollX, i * BLOCK_SIZE, Pipe[0], TRUE);
				break;
			case 8:
				DrawGraph(j * BLOCK_SIZE - s_ScrollX, i * BLOCK_SIZE, Pipe[1], TRUE);
				break;
			case 9:
				DrawGraph(j * BLOCK_SIZE - s_ScrollX, i * BLOCK_SIZE, Pipe[2], TRUE);
				break;
			case 10:
				DrawGraph(j * BLOCK_SIZE - s_ScrollX, i * BLOCK_SIZE, Pipe[3], TRUE);
				break;
			}
		}
	}

	mario->Draw();

#define DEBUG
#ifdef DEBUG
	DrawFormatString(0, 50, 0xff0000, "X1最初 %f　X1最後 %f", 0 * BLOCK_SIZE + b_ScrollX1, 48 * BLOCK_SIZE + b_ScrollX1);
	DrawFormatString(0, 100, 0xff0000, "X2最初 %f　X2最後 %f", 0 * BLOCK_SIZE + b_ScrollX2, 48 * BLOCK_SIZE + b_ScrollX2);
	DrawFormatString(0, 150, 0xff0000, "scroll1 %f\nscroll2 %f", b_ScrollX1, b_ScrollX2);
#endif // DEBUG

}

int GameMain::LoadStages()
{
	FILE* fp;
	char buf[1000];
	char* p;
	int i = 0, ret;
	int j = 0;

	//ステージデータを読み込む
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

	//背景データを読み込む
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
	//ブロック
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
	//背景
	if ((Sky = LoadGraph("1-1image/sora.png")) == -1) return -1;
	if ((Cloud[0] = LoadGraph("1-1image/cloud6.png")) == -1) return -1;
	if ((Cloud[1] = LoadGraph("1-1image/cloud5.png")) == -1) return -1;
	if ((Cloud[2] = LoadGraph("1-1image/cloud4.png")) == -1) return -1;
	if ((Cloud[3] = LoadGraph("1-1image/cloud1.png")) == -1) return -1;
	if ((Cloud[4] = LoadGraph("1-1image/cloud2.png")) == -1) return -1;
	if ((Cloud[5] = LoadGraph("1-1image/cloud3.png")) == -1) return -1;
	if ((Leaf[0] = LoadGraph("1-1image/ha0.png")) == -1) return -1;
	if ((Leaf[1] = LoadGraph("1-1image/ha1.png")) == -1) return -1;
	if ((Leaf[2] = LoadGraph("1-1image/ha2.png")) == -1) return -1;
	if ((Mountain[0] = LoadGraph("1-1image/mountain_left.png")) == -1) return -1;
	if ((Mountain[1] = LoadGraph("1-1image/mountain_right.png")) == -1) return -1;
	if ((Mountain[2] = LoadGraph("1-1image/mountain_up.png")) == -1) return -1;
	if ((Mountain[3] = LoadGraph("1-1image/mountain_surface.png")) == -1) return -1;
	if ((Mountain[4] = LoadGraph("1-1image/mountain_surface1.png")) == -1) return -1;
	if ((Mountain[5] = LoadGraph("1-1image/mountain_surface2.png")) == -1) return -1;

	return 0;
}

void GameMain::Scroll(float scroll,int sabun)const
{
	int w = 0;
	for (int i = 0; i < STAGE_HEIGHT_BLOCK; i++)
	{
		//背景
		for (int j = 0; j < BACK_WIDTH; j++)
		{
			w = j * BLOCK_SIZE + scroll;
			switch (BackData[i][j])
			{
			case 0:
				DrawGraph(w, i * BLOCK_SIZE, Sky, TRUE);
				break;
			case 1:
				DrawGraph(w , i * BLOCK_SIZE, Leaf[0], TRUE);
				break;
			case 2:
				DrawGraph(w, i * BLOCK_SIZE, Leaf[1], TRUE);
				break;
			case 3:
				DrawGraph(w, i * BLOCK_SIZE, Leaf[2], TRUE);
				break;
			case 4:
				DrawGraph(w , i * BLOCK_SIZE, Mountain[0], TRUE);
				break;
			case 5:
				DrawGraph(w , i * BLOCK_SIZE, Mountain[1], TRUE);
				break;
			case 6:
				DrawGraph(w , i * BLOCK_SIZE, Mountain[2], TRUE);
				break;
			case 7:
				DrawGraph(w, i * BLOCK_SIZE, Mountain[3], TRUE);
				break;
			case 8:
				DrawGraph(w , i * BLOCK_SIZE, Mountain[4], TRUE);
				break;
			case 9:
				DrawGraph(w , i * BLOCK_SIZE, Mountain[5], TRUE);
				break;
			case 10:
				DrawGraph(w , i * BLOCK_SIZE, Cloud[0], TRUE);
				break;
			case 11:
				DrawGraph(w , i * BLOCK_SIZE, Cloud[1], TRUE);
				break;
			case 12:
				DrawGraph(w , i * BLOCK_SIZE, Cloud[2], TRUE);
				break;
			case 13:
				DrawGraph(w , i * BLOCK_SIZE, Cloud[3], TRUE);
				break;
			case 14:
				DrawGraph(w , i * BLOCK_SIZE, Cloud[4], TRUE);
				break;
			case 15:
				DrawGraph(w , i * BLOCK_SIZE, Cloud[5], TRUE);
				break;
			}
		}
	}
}
