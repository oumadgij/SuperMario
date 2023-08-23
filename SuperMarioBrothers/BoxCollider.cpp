#include "BoxCollider.h"
#include "Define.h"

bool BoxCollider::ChackHitBox(VECTOR location, int x_size
    , int y_size, int scroll)
{
    //èÄîı
    //îªíËëäéË
    float Other[4];
    //ç∂ 
    Other[0] = location.x - scroll;
    //âE
    Other[1] = location.x + x_size - scroll;
    //è„
    Other[2] = location.y;
    //â∫
    Other[3] = location.y + y_size;

    //é©ï™
    float Self[4];
    //ç∂ 
    Self[0] = Location.x - XSize / 2;
    //âE
    Self[1] = Location.x + XSize / 2;
    //è„
    Self[2] = Location.y - YSize / 2;
    //â∫
    Self[3] = Location.y + YSize / 2;

    if (Other[1] < Self[0] || Self[1] < Other[0]) return false;
    if (Other[3] < Self[2] || Self[3] < Other[2]) return false;



    return true;
}
