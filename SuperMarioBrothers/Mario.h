#pragma once
#include "CharaBase.h"
#include "BoxCollider.h"

enum class STATE
{
	SMALL = 0,  //���у}���I
	BIG,    //�ł��}���I
	FIRE,   //�t�@�C�A�}���I
	STAR    //���G���
};

enum class MOVE_VECTOR
{
	STOP = 0,
	LEFT,
	RIGHT,
	JUMP,
	DOWN
};

class Mario : public CharaBase,public BoxCollider
{
public:
	Mario();
	~Mario() {};

	void Update();
	void Draw()const;
	virtual void Hit(int stagex, int stagey)override;
	int GetMoveVector() { return static_cast<int>(move); }
	
	//TO DO���Â����
	bool flg;
	//�����܂�

private:
	int marioImg[10];
	STATE state;
	MOVE_VECTOR move;

	//TO DO ���Â����
	int m;
	//�����܂�
};

