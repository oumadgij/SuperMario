#pragma once
#include "DxLib.h"

enum class HIT_SIDE
{
	DEFAULT=0,
	LEFT,
	RIGHT,
	TOP,
	UNDER
};

class BoxCollider
{
public:
	//�X�e�[�W
	bool ChackHitStage(int stage[][211],int jState, int move_vector, float scroll); //�����蔻��
	bool ChackUnder(int stage[][211], float scroll);  //�����ɒn�ʂ����邩�ǂ���
	//void HitStage();  //�����̏���

	VECTOR GetLocation()const { return Location; }
protected:
	VECTOR Location;  //�摜����̍��W
	int XSize, YSize;      //�摜�T�C�Y
	HIT_SIDE side = HIT_SIDE::DEFAULT;  //���������ꏊ
	int HitBlock[2] = { 0,0 };  //���������X�e�[�W�u���b�N�̍��W
};
