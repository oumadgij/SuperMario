#pragma once
#include "CharaBase.h"

enum class STATE
{
	SMALL = 0,  //���у}���I
	BIG,    //�ł��}���I
	FIRE,   //�t�@�C�A�}���I
	STAR    //���G���
};

enum class MOVE_STATE
{
	WALK,
	DASH
};

class Mario : public CharaBase
{
public:
	Mario();
	~Mario() {};

	void Update();
	void Draw()const;
	virtual void Hit()override;
	int GetMoveVector() { return static_cast<int>(Move); }

	//TO DO���Â����
	bool flg;
	//�����܂�

private:
	void SpeedUp();          //�_�b�V�����A���X�ɃX�s�[�h���グ��
	void SpeedReduction();   //��������

private:
	int marioImg[10];
	int Acceleration[3];
	float Inertia;       //����
	STATE State;         //�}���I�̏��
	MOVE_VECTOR Move;    //��������
	MOVE_STATE mState;   //�����Ƃ��̏��(���������邩)

	//TO DO ���Â����
	int m;
	//�����܂�
};

