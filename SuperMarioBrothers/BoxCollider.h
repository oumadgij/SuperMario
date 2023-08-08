#pragma once
#include "DxLib.h"

class BoxCollider
{
public:
	//void HitStage();  //判定後の処理
protected:
	enum class HIT_SIDE
	{
		DEFAULT = 0,
		LEFT,
		RIGHT,
		TOP,
		UNDER
	};

	VECTOR Location;  //画像左上の座標
	int XSize, YSize;      //画像サイズ
	HIT_SIDE side = HIT_SIDE::DEFAULT;  //当たった場所
};
