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
	~Mario()
	{
		//delete marioImg;
	}

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
	void PreparingJump();    //�W�����v�̏���
	void Jump();

private:
	int marioImg[10];
	//int Acceleration[3];
	float Inertia;       //����
	float JumpStartPosition;  //�W�����v�J�n���̈ʒu
	bool Jumping;        //�W�����v���Ă��邩(true�F�W�����v���Ă��� false�F�n�ʂɂ���)
	STATE State;         //�}���I�̏��
	MOVE_VECTOR Move;    //��������
	MOVE_STATE mState;   //�����Ƃ��̏��(���������邩)

	//TO DO ���Â����
	int m;
	float MAX_SMALL_JUMP = 0.0f;
	float kasokudo = 0.125f;
	float InitialSpeed = 4.0f;//����
	const float IncrementalAcceleration[5] = { 0.125,0.125,0.117,0.156,0.156 }; //���������x
	const float FallAcceleration[5] = { 0.437,0.473,0.375,0.562,0.562 };  //�~�����̉����x
	//const int InitialSpeed[2] = { -4,-4,-5,-5 };  //����
	const int MaxFallSpeed = 4;  //�ő�~�����x
	int index = 0;
	int sec = 0;  //�b���𐔂���
	float time = 0.0f;
	//�����܂�
};

