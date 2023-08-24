#pragma once
class UI
{
public:
	UI();

	void Update();
	void CountDown();
	void Draw()const;

	int LoadImages();

	void AddCoin() { ++Coin; }

private:
	//画像用変数
	int PlayerName;
	int Time;
	int Number[15];
	int World;
	int CointImg[4];

	int Coin;            //コインの数
	const int WaitTime = 60;
	int Sec;
	int TimeLimit;
	int Score;
	int Numbers[3];
	int ScoreNum[6];
	int CoinNum[2];
};

