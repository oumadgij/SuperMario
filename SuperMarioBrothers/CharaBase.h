#pragma once
#include "DxLib.h"
#include "BoxCollider.h"

enum class MOVE_VECTOR
{
	STOP = 0,
	LEFT,
	RIGHT,
	JUMP,
	DOWN
};

class CharaBase :public BoxCollider
{
public:
	CharaBase();
	virtual ~CharaBase() {};

	virtual void Hit() = 0; //�����蔻��
	//void HitStage(int stagex, int stagey);  //�X�e�[�W�̓����蔻��

protected:
	float Speed;      //���s�X�s�[�h
	int images[2];
};