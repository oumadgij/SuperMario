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
	//bool ChackHitStage(float StageX, float StageY, int XSize, int YSize, int move_vector);  //�����蔻����Ƃ�(false�F�������Ă��Ȃ� true�F�������Ă���)
	//�X�e�[�W
	bool ChackHitStage(int stage[][212],int move_vector); //�����蔻��
	//void HitStage();  //�����̏���

	VECTOR GetLocation()const { return Location; }

protected:
	VECTOR Location;  //�摜����̍��W
	int XSize, YSize;      //�摜�T�C�Y
	HIT_SIDE side = HIT_SIDE::DEFAULT;  //���������ꏊ
	int HitBlock[2] = { 0,0 };  //���������X�e�[�W�u���b�N�̍��W
};
