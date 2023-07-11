#pragma once
#include "DxLib.h"
class BoxCollider
{
public:
	//bool ChackHitStage(float StageX, float StageY, int XSize, int YSize, int move_vector);  //当たり判定をとる(false：当たっていない true：当たっている)
	bool ChackHitStage(int stage[][20]);

	//自身の何処にステージブロックが当たっているか(1：左側 2：右側 3：上側 4：下側)
	VECTOR GetLocation() { return Location; }

protected:
	VECTOR Location;  //画像左上の座標
	int XSize, YSize;      //画像サイズ
};
