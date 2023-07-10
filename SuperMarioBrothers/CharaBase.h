#pragma once
#include "DxLib.h"

class CharaBase
{
public:
	CharaBase();
	virtual ~CharaBase() {};

	virtual void Hit(int stagex,int stagey) = 0; //当たり判定(ステージ)

protected:
	float Speed;      //歩行スピード
};