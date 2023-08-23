#pragma once
#include "DxLib.h"
#include "BoxCollider.h"

enum class MOVE_VECTOR
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class CharaBase :public BoxCollider
{
public:
	CharaBase();
	virtual ~CharaBase() {};

	virtual void HitStage(int h_block, int w_block
		, int hit_side, int scroll) = 0; //当たり判定
	VECTOR GetLocation()const { return Location; }
	virtual void Fall() = 0;  //降下処理
	virtual void Animation() = 0; //アニメーション
	int GetSizeX()const { return XSize; }
	int GetSizeY()const { return YSize; }
	int GetMoveVector()const { return static_cast<int>(Move); }
	MOVE_VECTOR GetMove()const { return Move; }
	bool GetIsAir()const { return IsAir; }

protected:
	MOVE_VECTOR Move;    //動く方向
	float Speed;      //歩行スピード
	bool IsAir;       //空中にいるか? tru:空中にいる false:足がついている

	/*アニメーションの変数*/
	int AnimSpeed = 10;  //画像切り替えスピード
	int AnimWait;
	int aIndex = 0;      //画像の添え字
	bool Turn = false;   //反転するかどうか (true：する false：しない)
};