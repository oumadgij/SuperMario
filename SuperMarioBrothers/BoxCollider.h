#pragma once
#include "DxLib.h"

enum class HIT_SIDE
{
	DEFAULT=0,
	LEFT,
	RIGHT,
	TOP,
	UNDER
};

class BoxCollider
{
public:
	//bool ChackHitStage(float StageX, float StageY, int XSize, int YSize, int move_vector);  //当たり判定をとる(false：当たっていない true：当たっている)
	//ステージ
	bool ChackHitStage(int stage[][212],int move_vector); //当たり判定
	//void HitStage();  //判定後の処理

	VECTOR GetLocation()const { return Location; }

protected:
	VECTOR Location;  //画像左上の座標
	int XSize, YSize;      //画像サイズ
	HIT_SIDE side = HIT_SIDE::DEFAULT;  //当たった場所
	int HitBlock[2] = { 0,0 };  //当たったステージブロックの座標
};
