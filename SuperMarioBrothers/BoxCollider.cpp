#include "BoxCollider.h"
#include "Define.h"

//当たり判定をとる(false：当たっていない true：当たっている)
bool BoxCollider::ChackHitStage(int stage[][20])
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
            vertex[i].x = STAGE_WIDTH_BLOCK;
        }
        //Y座標をチェック
        if (vertex[i].y < 0) //0より小さいか
        {
            vertex[i].y = 0;
        }
        else if (STAGE_HEIGHT_BLOCK < vertex[i].y) //ステージより大きいか
        {
            vertex[i].y = STAGE_HEIGHT_BLOCK;
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

//bool BoxCollider::ChackHitStage(float StageX, float StageY, int XSize, int YSize, int move_vector)
//{
//    //自身の右側と下側の座標を求める
//    VECTOR Locetion2;
//    Locetion2.x = Location.x + this->XSize;
//    Locetion2.y = Location.y + this->YSize;
//
//    //ステージブロックの右側と下側の座標を求める
//    int StageX2 = StageX + XSize;
//    int StageY2 = StageY + YSize;
//
//    switch (move_vector)
//    {
//    case 1:
//        //自身の左側がステージブロックの右側よりも大きい
//        if (StageX2 < Location.x)
//        {
//            return false;
//        }
//        break;
//    case 2:
//        //自身の右側がステージブロックの左側よりも小さい
//        if (Locetion2.x < StageX)
//        {
//            return false;
//        }
//        break;
//    case 3:
//        //自身の上側がステージブロックの下側よりも大きい
//        if (StageY2 < Location.y)
//        {
//            return false;
//        }
//        break;
//    case 4:
//        //自身の下側がステージブロックの上側よりも小さい
//        if (Locetion2.y < StageY)
//        {
//            return false;
//        }
//        break;
//    }
//
//    ///*中心座標を求める*/
//    ////自身
//    //VECTOR Center;
//    //Center.x = this->Location.x + (this->XSize / 2);
//    //Center.y = this->Location.y + (this->YSize / 2);
//    ////対象
//    //VECTOR OCenter;
//    //OCenter.x = Location.x + XSize / 2;
//    //OCenter.y = Location.y + YSize / 2;
//
//    ///*X座標間とY座標間の距離を測る*/
//    //VECTOR Distance;
//    //Distance.x = fabsf(Center.x - OCenter.x);
//    //Distance.y = fabsf(Center.y - OCenter.y);
//
//    ///*X軸とY軸のサイズの和をとる*/
//    //int XSize_Sum = (this->XSize + XSize) / 2;
//    //int YSize_Sum = (this->YSize + YSize) / 2;
//
//    ///*比較*/
//    //if ((Distance.x <= XSize_Sum) && (Distance.y <= YSize_Sum))
//    //{
//    //    return true;
//    //}
//
//    return true;
//}