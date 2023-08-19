#pragma once
#include "BoxCollider.h"

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

class Item :public BoxCollider
{
public:
	Item();
	Item(int block_y, int block_x
		,int stage_num,int player_state, int scroll);

	void Update();
	void Draw(int scroll)const;

	//to do
	VECTOR Getlocate() { return Location; }
	//消す

private:
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
	float UpSpeed;
	float XSpeed = 1.0f;
	bool UpEnd;     //アイテム出現完了か?
	//to do
	
	//消す
};

