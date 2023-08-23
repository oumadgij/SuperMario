#pragma once
#include "DxLib.h"

class BoxCollider
{
public:
	//void HitStage();  //判定後の処理
	bool ChackHitBox(VECTOR location, int x_size, int y_size,int scroll);

protected:

	VECTOR Location;  //画像左上の座標
	int XSize, YSize;      //画像サイズ
};
