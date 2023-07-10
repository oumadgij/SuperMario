#pragma once
#include "CharaBase.h"
#include "BoxCollider.h"

enum class STATE
{
	SMALL = 0,  //ちびマリオ
	BIG,    //でかマリオ
	FIRE,   //ファイアマリオ
	STAR    //無敵状態
};

enum class MOVE_VECTOR
{
	STOP = 0,
	LEFT,
	RIGHT,
	JUMP,
	DOWN
};

class Mario : public CharaBase,public BoxCollider
{
public:
	Mario();
	~Mario() {};

	void Update();
	void Draw()const;
	virtual void Hit(int stagex, int stagey)override;
	int GetMoveVector() { return static_cast<int>(move); }
	
	//TO DOいづれ消す
	bool flg;
	//ここまで

private:
	int marioImg[10];
	STATE state;
	MOVE_VECTOR move;

	//TO DO いづれ消す
	int m;
	//ここまで
};

