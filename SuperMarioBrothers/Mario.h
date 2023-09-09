#pragma once
#include "CharaBase.h"

enum class STATE
{
	SMALL = 0,  //ちびマリオ
	BIG,        //でかマリオ
	FIRE,       //ファイアマリオ
	STAR_SMALL, //無敵状態(小)
	STAR_BIG	//無敵状態(大)
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
	void Hit(int item_type);
	virtual void HitStage(int h_block, int w_block
		, int hit_side, int scroll)override;  //判定後の処理
	virtual void Fall()override;  //降下処理
	float GetSpeed()const { return Speed; }
	int GetStage()const { return (int)State; }


	//TO DOいづれ消す
	//bool flg;
	//ここまで

private:
	void SpeedUp();          //ダッシュ時、徐々にスピードを上げる
	void SpeedReduction();   //減速する
	void PreparingJump();    //ジャンプの準備
	void Jump();
	virtual void Animation()override;
	int LoadImages();

private:
	//画像用変数
	int sMario[10];  //小さいマリオ
	int bMario[10];  //大きいマリオ
	int fMario[10];  //ファイアマリオ
	int Star_bMario[36];//大きいマリオ(スター)
	int Star_sMario[32];//小さいマリオ(スター)

	int Life;            //ライフ数
	float Inertia;       //慣性
	bool Jumping;        //ジャンプしているか(true：ジャンプしている false：ジャンプしていない)
	STATE State;         //マリオの状態
	STATE SaveState;     //マリオの状態を保存する
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

	/*アニメーション変数*/
	int StarLimit = 720;
	int StarTime = 0;
	const int DownSpeedTime = 120;
	int H = 0;

	//TO DO いづれ消す
	//ここまで
};

