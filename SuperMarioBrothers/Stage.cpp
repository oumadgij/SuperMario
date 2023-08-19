#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "Stage.h"
#include "Define.h"

Stage::Stage()
{
    Push = 0.0f;

    //データの読み込み
    if (LoadStages() == -1)
    {
        perror("LoadStage Error");
        throw;
    }
    if (LoadBack() == -1)
    {
        perror("LoadBack Error");
        throw;
    }
    //画像の読み込み
    if (LoadImages() == -1)
    {
        perror("LoadImage Error");
        throw;
    }

    for (int i = 0; i < STAGE_HEIGHT_BLOCK; i++)
    {
        for (int j = 0; j < STAGE_WIDTH_BLOCK; j++)
        {
            ChackStage[i][j] = StageData[i][j];
        }
    }
}

void Stage::Draw() const
{
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			//背景を描画
			DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, BackImages[BackData[i][j]], TRUE);

            //マリオがぶつかったブロックなら
            //pを変化させる
            int p = 0;
            if ((i == PushBlock[0])&&(j == PushBlock[1]))
            {
                p = Push;
            }

			//ステージを描画
			switch (StageData[i][j])
			{
			case 1:  //フロアブロック
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Floor, TRUE);
				break;
			case 2:  //普通のブロック
            case 32:
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE + p, Block, TRUE);
				break;
			case 3:  //ハテナブロック
            case 30:
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, QuestionBlock[0], TRUE);
				break;
			case 4:  //空ブロック
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE + p, EmptyBlock, TRUE);
				break;
			case 6:  //階段ブロック
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, StairsBlock, TRUE);
				break;
			case 7:  //土管
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[0], TRUE);
				break;
			case 8:	//土管
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[1], TRUE);
				break;
			case 9:	//土管
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[2], TRUE);
				break;
			case 10://土管
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[3], TRUE);
				break;
			}
		}
	}

#define DEBUG
#ifdef DEBUG
    for (int i = 0; i < 15; i++)
    {
        DrawFormatString(285, 15 + i * 10, 0x00ff00, "%d", i);
    }
    for (int j = 0; j < 20; j++)
    {
        DrawFormatString(300+j*15, 0, 0x00ff00, "%d", j);
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            DrawFormatString(300 + j * 15, 15 + i * 10,0x000000, "%d", ChackStage[i][j]);
        }
    }

    DrawFormatString(400, 250, 0x000000, "scroll %d  / %d", ScrollX, ScrollX / BLOCK_SIZE);
    DrawFormatString(0, 260, 0x000000, "down %d", down);
    DrawFormatString(0, 100, 0x000000, "Push %f", Push);
    DrawFormatString(0, 140, 0x000000, "1：左 2：右 3：上 4：下\nSide：%d", (int)Side);
    DrawFormatString(0, 180, 0x000000, "HitBlock h %d 座標 %d", HitBlock[0], HitBlock[0] * BLOCK_SIZE);
    DrawFormatString(0, 220, 0x000000, "HitBlock w %d 座標 %d", HitBlock[1], HitBlock[1] * BLOCK_SIZE);
   /* DrawFormatString(0, 180, 0x000000, "PushBlock h %d", PushBlock[0]);
    DrawFormatString(0, 220, 0x000000, "PushBlock w %d", PushBlock[1]);*/
    DrawFormatString(10, 10, 0xffffff, "左下のステージ位置\nX %d Y %d", vertex[0][1],vertex[0][0]);
    DrawFormatString(10, 50, 0xffffff, "右下のステージ位置\nX %d Y %d", vertex[1][1], vertex[1][0]);
#endif // DEBUG

}

int Stage::LoadStages()
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
		ret = sscanf(p, "%d", &StageData[i][j++]);

		while (p != NULL)
		{
			p = strtok(NULL, ",");
			if (p != NULL)
			{
				ret = sscanf(p, "%d", &StageData[i][j++]);
			}
		}

		++i;
		j = 0;
	}
	fclose(fp);

	return 0;
}

int Stage::LoadBack()
{
	//背景データを読み込む
	FILE* fp;
	char buf[1000];
	char* p;
	int i = 0, ret;
	int j = 0;
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

int Stage::LoadImages()
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
	/*背景*/
	//空
	if ((BackImages[0] = LoadGraph("1-1image/sora.png")) == -1) return -1;
	//草
	if ((BackImages[1] = LoadGraph("1-1image/ha0.png")) == -1) return -1;
	if ((BackImages[2] = LoadGraph("1-1image/ha1.png")) == -1) return -1;
	if ((BackImages[3] = LoadGraph("1-1image/ha2.png")) == -1) return -1;
	//山
	if ((BackImages[4] = LoadGraph("1-1image/mountain_left.png")) == -1) return -1;
	if ((BackImages[5] = LoadGraph("1-1image/mountain_right.png")) == -1) return -1;
	if ((BackImages[6] = LoadGraph("1-1image/mountain_up.png")) == -1) return -1;
	if ((BackImages[7] = LoadGraph("1-1image/mountain_surface.png")) == -1) return -1;
	if ((BackImages[8] = LoadGraph("1-1image/mountain_surface1.png")) == -1) return -1;
	if ((BackImages[9] = LoadGraph("1-1image/mountain_surface2.png")) == -1) return -1;
	//雲
	if ((BackImages[10] = LoadGraph("1-1image/cloud6.png")) == -1) return -1;
	if ((BackImages[11] = LoadGraph("1-1image/cloud5.png")) == -1) return -1;
	if ((BackImages[12] = LoadGraph("1-1image/cloud4.png")) == -1) return -1;
	if ((BackImages[13] = LoadGraph("1-1image/cloud1.png")) == -1) return -1;
	if ((BackImages[14] = LoadGraph("1-1image/cloud2.png")) == -1) return -1;
	if ((BackImages[15] = LoadGraph("1-1image/cloud3.png")) == -1) return -1;


	return 0;
}

void Stage::ChackStagePreparation(VECTOR location, int x_size, int y_size)
{
    //判定するステージの範囲を求める
    for (int h = 0; h < STAGE_HEIGHT_BLOCK; h++)
    {
        for (int w = 0; w < STAGE_WIDTH_BLOCK; w++)
        {
            ChackStage[h][w] = StageData[h][w + ScrollX / BLOCK_SIZE];
        }
    }

    /*
    * 自身の判定する範囲を求める
    *  ※範囲は矩形の開始座標を含むため
    *    終了位置を求めるときは、サイズを-1してから求める
    */
    //開始位置(左上)
    //Y座標
    vertex[0][0] = ((int)location.y - y_size / 2) / BLOCK_SIZE;
    //X座標
    vertex[0][1] = ((int)location.x - x_size / 2) / BLOCK_SIZE;

    //終了位置(右下)
    //Y座標
    vertex[1][0] = ((int)location.y + (y_size / 2 - 1)) / BLOCK_SIZE;
    //X座標
    vertex[1][1] = ((int)location.x + (x_size / 2 - 1)) / BLOCK_SIZE;

    /*自身がステージの範囲を超えていないかチェック*/
    for (int i = 0; i < 2; i++)
    {
        //Y座標をチェック
        if (STAGE_HEIGHT_BLOCK < vertex[i][0]) //ステージより大きいか
        {
            vertex[i][0] = STAGE_HEIGHT_BLOCK;
        }
        //X座標をチェック
        if (vertex[i][1] < 0) //0より小さいか
        {
            vertex[i][1] = 0;
        }
    }
}

//当たり判定をとる(false：当たっていない true：当たっている)
bool Stage::ChackHitStage(int move_vector)
{
    /*
    * 動く向きによって
    * 判定する辺を割り出す
    */
    int check_y = 0;
    int check_x = 0;
    //右に移動している
    if (move_vector == 2)
    {
        check_x = 1;
    }//下に移動している
    else if (move_vector == 4)
    {
        check_y = 1;
    }

    int start = 0;
    int end = 1;
    /*判定する範囲にブロックがないかチェック*/
    for (int h = vertex[start][0] + check_y; h <= vertex[end][0]; h++)
    {
        if (STAGE_HEIGHT_BLOCK == h)
        {
            break;
        }

        for (int w = vertex[start][1] + check_x; w <= vertex[end][1]; w++)
        {
            if (ChackStage[h][w] != 0 && ChackStage[h][w] < 50)  //ブロックが当たった時
            {
                switch (move_vector)
                {
                case 1:
                    Side = HIT_SIDE::RIGHT;
                    ++w;
                    break;
                case 2:
                    Side = HIT_SIDE::LEFT;
                    break;
                case 3:
                    Side = HIT_SIDE::UNDER;
                    ++h;
                    break;
                case 4:
                    Side = HIT_SIDE::TOP;
                    break;
                }

                HitBlock[0] = h;
                HitBlock[1] = w;
                play[0] = h;
                play[1] = w;

                return true;  //ブロックに当たっている
            }
        }
    }
    //for (int h = static_cast<int>(vertex[start].y); h <= vertex[end].y; h++)
    //{
    //    for (int w = static_cast<int>(vertex[start].x); w <= vertex[end].x; w++)
    //    {
    //        if (stage[h][w] != 0 && stage[h][w] < 50)  //ブロックが当たった時
    //        {
    //            if (jState == 2)
    //            {
    //                side = HIT_SIDE::UNDER;
    //                ++h;

    //                HitBlock[0] = h;
    //                HitBlock[1] = w - scroll / BLOCK_SIZE;
    //                return true;
    //            }

    //            switch (move_vector)
    //            {
    //            case 1:
    //                side = HIT_SIDE::RIGHT;
    //                ++w;
    //                break;
    //            case 2:
    //                side = HIT_SIDE::LEFT;
    //                break;
    //            case 3:
    //                side = HIT_SIDE::UNDER;
    //                ++h;
    //                break;
    //            case 4:
    //                side = HIT_SIDE::TOP;
    //                break;
    //            }

    //            HitBlock[0] = h;
    //            HitBlock[1] = w - scroll / BLOCK_SIZE;

    //            return true;  //ブロックに当たっている
    //        }
    //    }
    //}

    return false;
}

bool Stage::ChackUnder()
{
    int start = 0;
    int end = 1;
    for (int h = vertex[start][0]; h <= vertex[end][0]; h++)
    {
        for (int w = vertex[end][1]; w <= vertex[end][1]; w++)
        {
            if (ChackStage[h+1][w] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

void Stage::MoveBlockPreparation()
{
    down = 1;
    PushSpeed = 0.8f;
    SaveSide = Side;
    Side = HIT_SIDE::DEFAULT;
    PushBlock[0] = HitBlock[0] - 1;
    PushBlock[1] = HitBlock[1] + ScrollX / BLOCK_SIZE;
    PushEnd = false;

    //アイテムがある所は空ブロックにする
    if (StageData[PushBlock[0]][PushBlock[1]] == 30
        || StageData[PushBlock[0]][PushBlock[1]] == 3)
    {
        StageData[PushBlock[0]][PushBlock[1]] = 4;
    }
}

void Stage::MoveBlock()
{
    if (SaveSide == HIT_SIDE::UNDER)
    {
        if (down == 1)
        {
            sec = 0;
            Push -= PushSpeed;
        }
        else if (down == 2)
        {
            sec = 0;
            Push += PushSpeed;
        }

        if (Push < (BLOCK_SIZE / 2) * -1)
        {
            down = 2;
        }

        //元の位置に戻ったらリセット
        if (0 < Push)
        {
            for (int i = 0; i < 2; i++)
            {
                HitBlock[i] = -1;
            }
            Push = 0;
            SaveSide = HIT_SIDE::DEFAULT;
            PushEnd = true;
        }
       
    }
}
