#include "BoxCollider.h"
#include "Define.h"

//当たり判定をとる(false：当たっていない true：当たっている)
bool BoxCollider::ChackHitStage(int stage[][20], int move_vector)
{
    /*
    * 自身の判定する範囲を求める
    *  ※範囲は矩形の開始座標を含むため
    *    終了位置を求めるときは、サイズを-1してから求める
    */
    VECTOR vertex[2];
    //開始位置(左上)
     //X座標
    vertex[0].x = Location.x / BLOCK_SIZE;
     //Y座標
    vertex[0].y = Location.y / BLOCK_SIZE;

    //終了位置(右下)
     //X座標
    vertex[1].x = ((Location.x + (XSize - 1)) / BLOCK_SIZE);
     //Y座標
    vertex[1].y = (Location.y + (YSize - 1)) / BLOCK_SIZE;

    /*自身がステージの範囲を超えていないかチェック*/
    for (int i = 0; i < 2; i++)
    {
        //X座標をチェック
        if (vertex[i].x < 0) //0より小さいか
        {
            vertex[i].x = 0;
        }
        else if (STAGE_WIDTH_BLOCK < vertex[i].x) //ステージより大きいか
        {
            vertex[i].x = STAGE_WIDTH_BLOCK - 1;
        }
        //Y座標をチェック
        if (vertex[i].y < 0) //0より小さいか
        {
            vertex[i].y = 0;
        }
        else if (STAGE_HEIGHT_BLOCK < vertex[i].y) //ステージより大きいか
        {
            vertex[i].y = STAGE_HEIGHT_BLOCK - 1;
        }
    }

    int start = 0;
    int end = 1;
    /*判定する範囲にブロックがないかチェック*/
    for (int h = static_cast<int>(vertex[start].y); h <= vertex[end].y; h++)
    {
        for (int w = static_cast<int>(vertex[start].x); w <= vertex[end].x; w++)
        {
            if (stage[h][w] != 0)
            {
                switch (move_vector)
                {
                case 1:
                    side = HIT_SIDE::RIGHT;
                    break;
                case 2:
                    side = HIT_SIDE::LEFT;
                    break;
                case 3:
                    side = HIT_SIDE::UNDER;
                    break;
                case 4:
                    side = HIT_SIDE::TOP;
                    break;
                }

                HitBlock[0] = h;
                HitBlock[1] = w;

                return true;  //ブロックに当たっている
            }
        }
    }

    /*自身の4頂点を求める*/
    //VECTOR vertex[4];
    ////左上
    //vertex[0] = { Location.x,Location.y };
    ////左下
    //vertex[1] = { Location.x,Location.y + YSize };
    ////右上
    //vertex[2] = { Location.x + XSize,Location.y };
    ////右下
    //vertex[3] = { Location.x + XSize,Location.y + YSize };

    //for (int i = 0; i < 4; i++)
    //{
    //    int h = static_cast<int>(vertex[i].x / 32);
    //    int w = static_cast<int>(vertex[i].y / 32);
    //    if (stage[h][w] != 0)
    //    {
    //        /*HitVectors[0] = h;
    //        HitVectors[1] = w;*/

    //        return true;
    //    }
    //}

    return false;
}

void BoxCollider::HitStage()
{
    VECTOR vec;

    vec.y = static_cast<float>(HitBlock[0] * BLOCK_SIZE);
    vec.x = static_cast<float>(HitBlock[1] * BLOCK_SIZE);

    switch (side) //当たったブロックの辺の位置
    {
    case HIT_SIDE::LEFT:
        Location.x = vec.x - BLOCK_SIZE;
            break;
    case HIT_SIDE::RIGHT:
        Location.x = vec.x + BLOCK_SIZE;
        break;
    case HIT_SIDE::TOP:
        Location.y = vec.y - YSize;
        break;
    case HIT_SIDE::UNDER:
        Location.y = vec.y + BLOCK_SIZE;
        break;
    }

    //if (stagex != 0)
    //{
    //    switch (move)  //何処方向に進んでいたか
    //    {
    //    case MOVE_VECTOR::LEFT:  //左
    //        //X= (stagex+1) * 32;
    //        Location.x = static_cast<float>((stagex + 1) * 32);
    //        break;
    //    case MOVE_VECTOR::RIGHT:  //右
    //        //X = (stagex-1) * 32 + 32;
    //        Location.x = static_cast<float>((stagex - 1) * 32 + 32);
    //        break;
    //    }

    //    /*Location.x = X;*/
    //}
    //float Y = 0.f;
    //if (stagey != 0)
    //{
    //    switch (move)
    //    {
    //    case MOVE_VECTOR::JUMP:
    //        //Y = (stagey+1) * 32 + 32;
    //        Location.y = static_cast<float>((stagey + 1) * 32 + 32);
    //        break;
    //    case MOVE_VECTOR::DOWN:
    //        //Y = (stagey - 1) * 32 + BIGMARIO_HEIGTH;
    //        Location.y = static_cast<float>((stagey - 1) * 32 + BIGMARIO_HEIGTH_SIZE);
    //        break;
    //    }

    //    //Location.y = Y;
    //}
}