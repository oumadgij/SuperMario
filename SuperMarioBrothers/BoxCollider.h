#pragma once
#include "DxLib.h"
class BoxCollider
{
public:
	bool ChackHitStage(float StageX ,float StageY, int XSize, int YSize,int move_vector);  //当たり判定をとる(false：当たっていない true：当たっている)
	bool HitStage(int stage[][20]);
	void Hit(float stagex, float stagey);

	//自身の何処にステージブロックが当たっているか(1：左側 2：左側 3：上側 4：下側)
	int GetHitVector()const { return HitVector; }
	void InitHitVector() { HitVector = 0; }

protected:
	VECTOR Location;  //画像左上の座標
	int XSize,YSize;      //画像サイズ
	int HitVector;   //1：左側 2：右側 3：上側 4：下側
};

