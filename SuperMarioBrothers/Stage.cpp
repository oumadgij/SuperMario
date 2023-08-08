#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "Stage.h"
#include "Define.h"

Stage::Stage()
{
}

void Stage::Draw(const int stage[][211],const int back[][211], const float sx) const
{
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			//背景を描画
			DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, BackImages[back[i][j]], TRUE);

			//ステージを描画
			switch (stage[i][j])
			{
			case 1:  //フロアブロック
				DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, Floor, TRUE);
				break;
			case 2:  //普通のブロック
				DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, Block, TRUE);
				break;
			case 3:  //ハテナブロック
				DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, QuestionBlock[0], TRUE);
				break;
			case 4:  //空ブロック
				DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, EmptyBlock, TRUE);
				break;
			case 6:  //階段ブロック
				DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, StairsBlock, TRUE);
				break;
			case 7:  //土管
				DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, Pipe[0], TRUE);
				break;
			case 8:	//土管
				DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, Pipe[1], TRUE);
				break;
			case 9:	//土管
				DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, Pipe[2], TRUE);
				break;
			case 10://土管
				DrawGraph(j * BLOCK_SIZE - sx, i * BLOCK_SIZE, Pipe[3], TRUE);
				break;
			}
		}
	}

#define DEBUG
#ifdef DEBUG
    DrawFormatString(0, 180, 0x000000, "HitBlock[0] %d 座標 %d", HitBlock[0], HitBlock[0] * BLOCK_SIZE);
    DrawFormatString(0, 220, 0x000000, "HitBlock[1] %d 座標 %d", HitBlock[1], HitBlock[1] * BLOCK_SIZE);
#endif // DEBUG

}

int Stage::LoadStages(int stage[][211])
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
		ret = sscanf(p, "%d", &stage[i][j++]);

		while (p != NULL)
		{
			p = strtok(NULL, ",");
			if (p != NULL)
			{
				ret = sscanf(p, "%d", &stage[i][j++]);
			}
		}

		++i;
		j = 0;
	}
	fclose(fp);

	return 0;
}

int Stage::LoadBack(int back[][211])
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
		ret = sscanf(p, "%d", &back[i][j++]);

		while (p != NULL)
		{
			p = strtok(NULL, ",");
			if (p != NULL)
			{
				ret = sscanf(p, "%d", &back[i][j++]);
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

//当たり判定をとる(false：当たっていない true：当たっている)
bool Stage::ChackHitStage(const int stage[][211], int jState
    , VECTOR location, int x_size, int y_size
    , int move_vector, float scroll)
{
    /*
    * 自身の判定する範囲を求める
    *  ※範囲は矩形の開始座標を含むため
    *    終了位置を求めるときは、サイズを-1してから求める
    */
    float vertex[2][2];
    //開始位置(左上)
    //Y座標
    vertex[0][0] = (location.y - y_size / 2) / BLOCK_SIZE;
    //X座標
    vertex[0][1] = (location.x - x_size / 2) / BLOCK_SIZE + scroll / BLOCK_SIZE;

    //終了位置(右下)
    //Y座標
    vertex[1][0] = (location.y + (y_size / 2 - 1)) / BLOCK_SIZE;
    //X座標
    vertex[1][1] = (location.x + (x_size / 2 - 1)) / BLOCK_SIZE + scroll / BLOCK_SIZE;
    //VECTOR vertex[2];
    ////開始位置(左上)
    // //X座標
    //vertex[0].x = (Location.x - XSize / 2) / BLOCK_SIZE + scroll / BLOCK_SIZE;
    // //Y座標
    //vertex[0].y = (Location.y - YSize / 2) / BLOCK_SIZE;

    ////終了位置(右下)
    // //X座標
    //vertex[1].x = (Location.x + (XSize/2 - 1)) / BLOCK_SIZE + scroll / BLOCK_SIZE;
    // //Y座標
    //vertex[1].y = (Location.y + (YSize/2 - 1)) / BLOCK_SIZE;

    /*自身がステージの範囲を超えていないかチェック*/
    for (int i = 0; i < 2; i++)
    {
        //Y座標をチェック
        if (STAGE_HEIGHT_BLOCK < vertex[i][0]) //ステージより大きいか
        {
            vertex[i][0] = STAGE_HEIGHT_BLOCK - 1;
        }
        //X座標をチェック
        if (vertex[i][1] < 0) //0より小さいか
        {
            vertex[i][1] = 0;
        }
    }
    //for (int i = 0; i < 2; i++)
    //{
    //    //X座標をチェック
    //    if (vertex[i].x < 0) //0より小さいか
    //    {
    //        vertex[i].x = 0;
    //    }
    //    //Y座標をチェック
    //    if (STAGE_HEIGHT_BLOCK < vertex[i].y) //ステージより大きいか
    //    {
    //        vertex[i].y = STAGE_HEIGHT_BLOCK - 1;
    //    }
    //}

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
    }
    //下に移動している
    if (move_vector == 4)
    {
        check_y = 1;
    }

    int start = 0;
    int end = 1;
    /*判定する範囲にブロックがないかチェック*/
    for (int h = static_cast<int>(vertex[start + check_y][0]); h <= vertex[end][0]; h++)
    {
        for (int w = static_cast<int>(vertex[start + check_x][1]); w <= vertex[end][1]; w++)
        {
            if (stage[h][w] != 0 && stage[h][w] < 50)  //ブロックが当たった時
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
                HitBlock[1] = w - scroll / BLOCK_SIZE;

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

bool Stage::ChackUnder(const int stage[][211], float scroll
    , VECTOR location, int x_size, int y_size)
{
    /*自身の判定する範囲を求める*/
    VECTOR vertex[2];
    //左下
    //Y座標
    vertex[0].y = (location.y + y_size / 2) / BLOCK_SIZE;
    //X座標
    vertex[0].x = (location.x - x_size / 2) / BLOCK_SIZE + scroll / BLOCK_SIZE;

    //右下
    //Y座標
    vertex[1].y = (location.y + y_size / 2) / BLOCK_SIZE;
    //X座標
    vertex[1].x = (location.x + (x_size / 2 - 1)) / BLOCK_SIZE + scroll / BLOCK_SIZE;

    int start = 0;
    int end = 1;
    for (int h = (int)vertex[start].y; h <= (int)vertex[end].y; h++)
    {
        for (int w = (int)vertex[end].x; w <= (int)vertex[end].x; w++)
        {
            if (stage[h][w] == 0)
            {
                return true;
            }
        }
    }
    return false;
}