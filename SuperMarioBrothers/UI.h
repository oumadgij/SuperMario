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
	//�摜�p�ϐ�
	int PlayerName;
	int Time;
	int Number[15];
	int World;
	int CointImg[4];

	int Coin;            //�R�C���̐�
	const int WaitTime = 60;
	int Sec;
	int TimeLimit;
	int Score;
	int Numbers[3];
	int ScoreNum[6];
	int CoinNum[2];
};

