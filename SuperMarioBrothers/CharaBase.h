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

	virtual void HitStage(int h_block, int w_block
		, int hit_side, int scroll) = 0; //�����蔻��
	VECTOR GetLocation()const { return Location; }
	virtual void Fall() = 0;  //�~������
	virtual void Animation() = 0; //�A�j���[�V����
	int GetSizeX()const { return XSize; }
	int GetSizeY()const { return YSize; }
	int GetMoveVector()const { return static_cast<int>(Move); }
	MOVE_VECTOR GetMove()const { return Move; }
	bool GetIsAir()const { return IsAir; }

protected:
	MOVE_VECTOR Move;    //��������
	float Speed;      //���s�X�s�[�h
	bool IsAir;       //�󒆂ɂ��邩? tru:�󒆂ɂ��� false:�������Ă���

	/*�A�j���[�V�����̕ϐ�*/
	int AnimSpeed = 10;  //�摜�؂�ւ��X�s�[�h
	int AnimWait;
	int aIndex = 0;      //�摜�̓Y����
	bool Turn = false;   //���]���邩�ǂ��� (true�F���� false�F���Ȃ�)
};