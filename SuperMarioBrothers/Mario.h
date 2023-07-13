#pragma once
#include "CharaBase.h"

enum class STATE
{
	SMALL = 0,  //ちびマリオ
	BIG,    //でかマリオ
	FIRE,   //ファイアマリオ
	STAR    //無敵状態
};

class Mario : public CharaBase
{
public:
	Mario();
	~Mario() {};

	void Update();
	void Draw()const;
	virtual void Hit()override;
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

