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
	//����

private:
	int LoadImages();

	//�摜�p�ϐ�
	int Mushroom;     //�L�m�R
	int UP_Mushroom;  //1UP�L�m�R
	int Coin[4];      //�R�C��
	int M_Coin[4];    //�����o���R�C��
	int Flower[4];      //�t�@�C�A�t�����[
	int Star[4];      //�X�^�[

	ITEM_TYPE ItemType = ITEM_TYPE::DEFAULT;
	VECTOR StartLocate;
	int Locate[2];  //�A�C�e�����o���ʒu 0�F�c 1�F��
	float UpSpeed;
	float XSpeed = 1.0f;
	bool UpEnd;     //�A�C�e���o��������?
	//to do
	
	//����
};

