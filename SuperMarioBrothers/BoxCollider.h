#pragma once
#include "DxLib.h"
class BoxCollider
{
public:
	bool ChackHitStage(float StageX ,float StageY, int XSize, int YSize,int move_vector);  //�����蔻����Ƃ�(false�F�������Ă��Ȃ� true�F�������Ă���)
	bool HitStage(int stage[][20]);
	void Hit(float stagex, float stagey);

	//���g�̉����ɃX�e�[�W�u���b�N���������Ă��邩(1�F���� 2�F���� 3�F�㑤 4�F����)
	int GetHitVector()const { return HitVector; }
	void InitHitVector() { HitVector = 0; }

protected:
	VECTOR Location;  //�摜����̍��W
	int XSize,YSize;      //�摜�T�C�Y
	int HitVector;   //1�F���� 2�F�E�� 3�F�㑤 4�F����
};

