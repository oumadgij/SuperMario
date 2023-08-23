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
	//�����̏���
	virtual void HitStage(int h_block, int w_block
		, int hit_side, int scroll)override;
	//�~������
	void Fall();
	//�i�s�����𔽓]
	void Inversion(); 
	//�A�j���[�V����
	virtual void Animation()override;

	int GetItemType()const { return static_cast<int>(ItemType); }
	bool GetCoinUpEnd()const { return UpEnd; }
	//to do
	
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
	float UpSpeed;  //�o������X�s�[�h
	float FallSpeed;  //�����X�s�[�h
	bool UpEnd;     //�A�C�e���o��������?
	//to do
	
	//����
};

