#pragma once
#include "DxLib.h"

class CharaBase
{
public:
	CharaBase();
	virtual ~CharaBase() {};

	virtual void Hit(int stagex,int stagey) = 0; //�����蔻��(�X�e�[�W)

protected:
	float Speed;      //���s�X�s�[�h
};