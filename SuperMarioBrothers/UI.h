#pragma once
#include "DxLib.h"
#include "UpScore.h"
class UI
{
public:
	UI();

	void Update();
	void Draw()const;
	//���̉�
	void Instantiation(VECTOR location, int scroll, int xsize,int item_type);
	void AddCoin() { ++Coin; }
	void AddScore(int type) { Score += Item_Points[type - 1]; }

private:
	void CountDown();
	int LoadImages();
	void Change();

	//�摜�p�ϐ�
	int PlayerName;
	int Time;
	int Number[15];
	int World;
	int CoinImg[4];
	int String[26];

	//������A�C�e���̔z�_ {�L�m�R,1UP�L�m�R,�R�C��,�����o���̃R�C��,�X�^�[,�t�@�C�A�t�����[}
	const int Item_Points[6] = { 1000,0,200,200,1000,1000 };
	const int WaitTime = 30; //�҂�����
	int StopTime;        //�R�C���̐F���P�T���Ă������ɕω����Ȃ��悤��
	int ChangeSpeed;     //�R�C���̐F���ς��X�s�[�h
	int CoinIndex;
	int Coin;            //�R�C���̐�
	int Sec;
	int TimeLimit;       //�c�莞��
	int Score;           //�X�R�A
	bool ChangeStart;    //�R�C���̐F��ς��邩
	//�����X�R�A�̕ϐ�
	UpScore** uScore;
	int ItemType;
	const int PointNum[6][5] = { {1,0,0,0},{0},{2,0,0},{2,0,0},{1,0,0,0},{1,0,0,0} };
	//�������̔z��`��p
	int TimeNum[3];
	int ScoreNum[6];
	int CoinNum[2];
};

