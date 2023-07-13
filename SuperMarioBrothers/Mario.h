#pragma once
#include "CharaBase.h"

enum class STATE
{
	SMALL = 0,  //ちびマリオ
	BIG,    //でかマリオ
	FIRE,   //ファイアマリオ
	STAR    //無敵状態
};

enum class MOVE_STATE
{
	WALK,
	DASH
};

class Mario : public CharaBase
{
public:
	Mario();
	~Mario() {};

	void Update();
	void Draw()const;
	virtual void Hit()override;
	int GetMoveVector() { return static_cast<int>(Move); }

	//TO DOいづれ消す
	bool flg;
	//ここまで

private:
	void SpeedUp();          //ダッシュ時、徐々にスピードを上げる
	void SpeedReduction();   //減速する

private:
	int marioImg[10];
	int Acceleration[3];
	float Inertia;       //慣性
	STATE State;         //マリオの状態
	MOVE_VECTOR Move;    //動く方向
	MOVE_STATE mState;   //動くときの状態(歩くか走るか)

	//TO DO いづれ消す
	int m;
	//ここまで
};

