#pragma once
#include "CharaBase.h"

enum class ITEM_TYPE
{
	DEFAULT,
	MUSHROOM,
	UP_MUSHROOM,
	COIN,
	M_COIN,
	FLOWER,
	STAR
};

class Item :public CharaBase
{
public:
	Item();
	Item(int block_y, int block_x
		,int stage_num,int player_state, int scroll);

	void Update();
	void Draw(int scroll)const;
	//判定後の処理
	virtual void HitStage(int h_block, int w_block
		, int hit_side, int scroll)override;
	//降下処理
	void Fall();
	//進行方向を反転
	void Inversion(); 
	//アニメーション
	virtual void Animation()override;

	int GetItemType()const { return static_cast<int>(ItemType); }
	bool GetCoinUpEnd()const { return UpEnd; }
	//to do
	
	//消す

private:
	//スターがジャンプする
	void StarJump();
	int LoadImages();

	//画像用変数
	int Mushroom;     //キノコ
	int UP_Mushroom;  //1UPキノコ
	int Coin[4];      //コイン
	int M_Coin[4];    //剥き出しコイン
	int Flower[4];      //ファイアフラワー
	int Star[4];      //スター

	ITEM_TYPE ItemType = ITEM_TYPE::DEFAULT;
	VECTOR StartLocate;
	int Locate[2];  //アイテムを出す位置 0：縦 1：横
	float UpSpeed;  //出現するスピード
	bool UpEnd;     //アイテム出現完了か?

	//ジャンプ
	float FallSpeed;  //落下スピード
	float kasokudo = 0.156f;    //加速度
	float YSpeed = -6.0f;  //y軸の速度
	float XSpeed = 0.0f;  //x軸の速度
	float IncrementalAcceleration = 0.156f;  //加速度の増加値
	int sec = 0;

	 
	//to do
	
	//消す
};

