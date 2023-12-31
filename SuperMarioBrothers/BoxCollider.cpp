#include "BoxCollider.h"
#include "Define.h"

bool BoxCollider::ChackHitBox(VECTOR location, int x_size
    , int y_size, int scroll)
{
    //準備
    //判定相手
    float Other[4];
    //左 
    Other[0] = location.x - scroll;
    //右
    Other[1] = location.x + x_size - scroll;
    //上
    Other[2] = location.y;
    //下
    Other[3] = location.y + y_size;

    //自分
    float Self[4];
    //左 
    Self[0] = Location.x - XSize / 2;
    //右
    Self[1] = Location.x + XSize / 2;
    //上
    Self[2] = Location.y - YSize / 2;
    //下
    Self[3] = Location.y + YSize / 2;

    if (Other[1] < Self[0] || Self[1] < Other[0]) return false;
    if (Other[3] < Self[2] || Self[3] < Other[2]) return false;



    return true;
}
