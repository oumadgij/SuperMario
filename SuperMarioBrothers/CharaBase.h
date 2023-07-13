#pragma once
#include "DxLib.h"
#include "BoxCollider.h"

enum class MOVE_VECTOR
{
	STOP = 0,
	LEFT,
	RIGHT,
	JUMP,
	DOWN
};

class CharaBase :public BoxCollider
{
public:
	CharaBase();
	virtual ~CharaBase() {};

	virtual void Hit() = 0; //当たり判定
	//void HitStage(int stagex, int stagey);  //ステージの当たり判定

protected:
	float Speed;      //歩行スピード
	int images[2];
};