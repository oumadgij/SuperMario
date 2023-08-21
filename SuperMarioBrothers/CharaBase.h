#pragma once
#include "DxLib.h"
#include "BoxCollider.h"

enum class MOVE_VECTOR
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class CharaBase :public BoxCollider
{
public:
	CharaBase();
	virtual ~CharaBase() {};

	virtual void Hit() = 0; //�����蔻��
	VECTOR GetLocation()const { return Location; }
	virtual void Fall() = 0;  //�~������
	int GetSizeX()const { return XSize; }
	int GetSizeY()const { return YSize; }
	int GetMoveVector()const { return static_cast<int>(Move); }
	MOVE_VECTOR GetMove()const { return Move; }
	bool GetIsAir()const { return IsAir; }

protected:
	MOVE_VECTOR Move;    //��������
	float Speed;      //���s�X�s�[�h
	bool IsAir;       //�󒆂ɂ��邩? tru:�󒆂ɂ��� false:�������Ă���
};