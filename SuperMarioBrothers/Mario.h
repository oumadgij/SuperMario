#pragma once
#include "CharaBase.h"

enum class STATE
{
	SMALL = 0,  //���у}���I
	BIG,    //�ł��}���I
	FIRE,   //�t�@�C�A�}���I
	STAR    //���G���
};

class Mario : public CharaBase
{
public:
	Mario();
	~Mario() {};

	void Update();
	void Draw()const;
	virtual void Hit()override;
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

