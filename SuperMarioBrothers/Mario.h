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
	~Mario()
	{
		//delete marioImg;
	}

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
	void PreparingJump();    //ジャンプの準備
	void Jump();

private:
	int marioImg[10];
	//int Acceleration[3];
	float Inertia;       //慣性
	float JumpStartPosition;  //ジャンプ開始時の位置
	bool Jumping;        //ジャンプしているか(true：ジャンプしている false：地面にいる)
	STATE State;         //マリオの状態
	MOVE_VECTOR Move;    //動く方向
	MOVE_STATE mState;   //動くときの状態(歩くか走るか)

	//TO DO いづれ消す
	int m;
	float MAX_SMALL_JUMP = 0.0f;
	float kasokudo = 0.125f;
	float InitialSpeed = 4.0f;//初速
	const float IncrementalAcceleration[5] = { 0.125,0.125,0.117,0.156,0.156 }; //増加加速度
	const float FallAcceleration[5] = { 0.437,0.473,0.375,0.562,0.562 };  //降下時の加速度
	//const int InitialSpeed[2] = { -4,-4,-5,-5 };  //初速
	const int MaxFallSpeed = 4;  //最大降下速度
	int index = 0;
	int sec = 0;  //秒数を数える
	float time = 0.0f;
	//ここまで
};

