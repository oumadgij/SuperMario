#pragma once
#include "DxLib.h"
#include "UpScore.h"
class UI
{
public:
	UI();

	void Update();
	void Draw()const;
	//実体化
	void Instantiation(VECTOR location, int scroll, int xsize,int item_type);
	void AddCoin() { ++Coin; }
	void AddScore(int type) { Score += Item_Points[type - 1]; }

private:
	void CountDown();
	int LoadImages();
	void Change();

	//画像用変数
	int PlayerName;
	int Time;
	int Number[15];
	int World;
	int CoinImg[4];
	int String[26];

	//取ったアイテムの配点 {キノコ,1UPキノコ,コイン,剥き出しのコイン,スター,ファイアフラワー}
	const int Item_Points[6] = { 1000,0,200,200,1000,1000 };
	const int WaitTime = 30; //待ち時間
	int StopTime;        //コインの色が１週してもすぐに変化しないように
	int ChangeSpeed;     //コインの色が変わるスピード
	int CoinIndex;
	int Coin;            //コインの数
	int Sec;
	int TimeLimit;       //残り時間
	int Score;           //スコア
	bool ChangeStart;    //コインの色を変えるか
	//動くスコアの変数
	UpScore** uScore;
	int ItemType;
	const int PointNum[6][5] = { {1,0,0,0},{0},{2,0,0},{2,0,0},{1,0,0,0},{1,0,0,0} };
	//桁数分の配列描画用
	int TimeNum[3];
	int ScoreNum[6];
	int CoinNum[2];
};

