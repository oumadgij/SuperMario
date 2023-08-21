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
	void HitStage(int h_block, int w_block, int hit_side);  //判定後の処理
	virtual void Fall()override;  //降下処理
	float GetSpeed()const { return Speed; }
	int GetStage()const { return (int)State; }


	//TO DOいづれ消す
	bool flg;
	//ここまで

private:
	void SpeedUp();          //ダッシュ時、徐々にスピードを上げる
	void SpeedReduction();   //減速する
	void PreparingJump();    //ジャンプの準備
	void Jump();
	void Animation();

private:
	int s_marioImg[10];
	int b_marioImg[10];
	float Inertia;       //慣性
	bool Jumping;        //ジャンプしているか(true：ジャンプしている false：ジャンプしていない)
	STATE State;         //マリオの状態
	MOVE_STATE mState;   //動くときの状態(歩くか走るか)

	/*ジャンプの変数*/
	float MaxJump = 0.0f;
	float kasokudo = 0.125f;    //加速度
	float Fallkasokudo = 0.0f;  //落下加速度
	const float IncrementalAccelerationData[5] = { 0.125f,0.125f,0.117f,0.156f,0.156f }; //増加加速度
	const float FallAcceleration[5] = { 0.437f,0.473f,0.375f,0.562f,0.562f };  //降下時の加速度
	const int InitialSpeed[5] = { -6,-6,-6,-7,-7 };  //初速 元-4,-4,-4,-5,-5
	const int MaxFallSpeed = 4;  //最大降下速度
	int index = 0;
	float YSpeed = 0.0f;  //y軸の速度
	float XSpeed = 0.0f;  //x軸の速度
	float IncrementalAcceleration = 0.0f;  //加速度の増加値
	int sec = 0;
	/*アニメーションの変数*/
	int AnimSpeed = 10;  //画像切り替えスピード
	int AnimWait;
	int aIndex = 0;      //画像の添え字
	bool Turn = false;   //反転するかどうか (true：する false：しない)

	//TO DO いづれ消す
	int mari = 0;
	//ここまで
};

