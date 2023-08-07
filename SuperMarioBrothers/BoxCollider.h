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
	//ステージ
	bool ChackHitStage(int stage[][211],int jState, int move_vector, float scroll); //当たり判定
	bool ChackUnder(int stage[][211], float scroll);  //足元に地面があるかどうか
	//void HitStage();  //判定後の処理

	VECTOR GetLocation()const { return Location; }
protected:
	VECTOR Location;  //画像左上の座標
	int XSize, YSize;      //画像サイズ
	HIT_SIDE side = HIT_SIDE::DEFAULT;  //当たった場所
	int HitBlock[2] = { 0,0 };  //当たったステージブロックの座標
};
