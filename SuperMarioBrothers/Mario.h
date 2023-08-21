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
	void HitStage(int h_block, int w_block, int hit_side);  //�����̏���
	virtual void Fall()override;  //�~������
	float GetSpeed()const { return Speed; }
	int GetStage()const { return (int)State; }


	//TO DO���Â����
	bool flg;
	//�����܂�

private:
	void SpeedUp();          //�_�b�V�����A���X�ɃX�s�[�h���グ��
	void SpeedReduction();   //��������
	void PreparingJump();    //�W�����v�̏���
	void Jump();
	void Animation();

private:
	int s_marioImg[10];
	int b_marioImg[10];
	float Inertia;       //����
	bool Jumping;        //�W�����v���Ă��邩(true�F�W�����v���Ă��� false�F�W�����v���Ă��Ȃ�)
	STATE State;         //�}���I�̏��
	MOVE_STATE mState;   //�����Ƃ��̏��(���������邩)

	/*�W�����v�̕ϐ�*/
	float MaxJump = 0.0f;
	float kasokudo = 0.125f;    //�����x
	float Fallkasokudo = 0.0f;  //���������x
	const float IncrementalAccelerationData[5] = { 0.125f,0.125f,0.117f,0.156f,0.156f }; //���������x
	const float FallAcceleration[5] = { 0.437f,0.473f,0.375f,0.562f,0.562f };  //�~�����̉����x
	const int InitialSpeed[5] = { -6,-6,-6,-7,-7 };  //���� ��-4,-4,-4,-5,-5
	const int MaxFallSpeed = 4;  //�ő�~�����x
	int index = 0;
	float YSpeed = 0.0f;  //y���̑��x
	float XSpeed = 0.0f;  //x���̑��x
	float IncrementalAcceleration = 0.0f;  //�����x�̑����l
	int sec = 0;
	/*�A�j���[�V�����̕ϐ�*/
	int AnimSpeed = 10;  //�摜�؂�ւ��X�s�[�h
	int AnimWait;
	int aIndex = 0;      //�摜�̓Y����
	bool Turn = false;   //���]���邩�ǂ��� (true�F���� false�F���Ȃ�)

	//TO DO ���Â����
	int mari = 0;
	//�����܂�
};

