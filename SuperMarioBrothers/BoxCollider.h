#pragma once
#include "DxLib.h"
class BoxCollider
{
public:
	//bool ChackHitStage(float StageX, float StageY, int XSize, int YSize, int move_vector);  //�����蔻����Ƃ�(false�F�������Ă��Ȃ� true�F�������Ă���)
	bool ChackHitStage(int stage[][20]);

	//���g�̉����ɃX�e�[�W�u���b�N���������Ă��邩(1�F���� 2�F�E�� 3�F�㑤 4�F����)
	VECTOR GetLocation() { return Location; }

protected:
	VECTOR Location;  //�摜����̍��W
	int XSize, YSize;      //�摜�T�C�Y
};
