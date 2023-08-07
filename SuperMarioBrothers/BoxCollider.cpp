#include "BoxCollider.h"
#include "Define.h"

//当たり判定をとる(false：当たっていない true：当たっている)
bool BoxCollider::ChackHitStage(int stage[][211], int jState, int move_vector, float scroll)
{
    /*
    * 自身の判定する範囲を求める
    *  ※範囲は矩形の開始座標を含むため
    *    終了位置を求めるときは、サイズを-1してから求める
    */
    float vertex[2][2];
    //開始位置(左上)
    //Y座標
    vertex[0][0] = (Location.y - YSize / 2) / BLOCK_SIZE;
    //X座標
    vertex[0][1] = (Location.x - XSize / 2) / BLOCK_SIZE + scroll / BLOCK_SIZE;

    //終了位置(右下)
    //Y座標
    vertex[1][0] = (Location.y + (YSize / 2 - 1)) / BLOCK_SIZE;
    //X座標
    vertex[1][1] = (Location.x + (XSize / 2 - 1)) / BLOCK_SIZE + scroll / BLOCK_SIZE;
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
    //左に移動している
    if (move_vector == 1)
    {
        check_x = 1;
    }
    //上に移動している
    if (move_vector == 3)
    {
        check_y = 1;
    }

    int start = 0;
    int end = 1;
    /*判定する範囲にブロックがないかチェック*/
    for (int h = static_cast<int>(vertex[start+check_y][0]); h <= vertex[end][0]; h++)
    {
        for (int w = static_cast<int>(vertex[start+check_x][1]); w <= vertex[end][1]; w++)
        {
            if (stage[h][w] != 0 && stage[h][w] < 50)  //ブロックが当たった時
            {
                switch (move_vector)
                {
                case 1:
                    side = HIT_SIDE::RIGHT;
                    ++w;
                    break;
                case 2:
                    side = HIT_SIDE::LEFT;
                    break;
                case 3:
                    side = HIT_SIDE::UNDER;
                    ++h;
                    break;
                case 4:
                    side = HIT_SIDE::TOP;
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

bool BoxCollider::ChackUnder(int stage[][211], float scroll)
{
    /*自身の判定する範囲を求める*/
    VECTOR vertex[2];
    //左下
    //Y座標
    vertex[0].y = (Location.y + YSize / 2) / BLOCK_SIZE;
    //X座標
    vertex[0].x = (Location.x - XSize / 2) / BLOCK_SIZE + scroll / BLOCK_SIZE;

    //右下
    //Y座標
    vertex[1].y = (Location.y + YSize / 2) / BLOCK_SIZE;
    //X座標
    vertex[1].x = (Location.x + (XSize / 2 - 1)) / BLOCK_SIZE + scroll / BLOCK_SIZE;

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
