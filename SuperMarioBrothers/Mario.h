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

enum class JUMP_STATE
{
	DEFAULT,
	GROUND,
	SKY
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
	void HitStage();  //�����̏���
	int GetMoveVector() { return static_cast<int>(Move); }


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
	bool Jumping;        //�W�����v���Ă悢��(true�F�W�����v���Ă悢 false�F�W�����v���Ȃ�)
	STATE State;         //�}���I�̏��
	MOVE_VECTOR Move;    //��������
	MOVE_STATE mState;   //�����Ƃ��̏��(���������邩)

	/*�W�����v�̕ϐ�*/
	JUMP_STATE jState = JUMP_STATE::DEFAULT;
	float MaxJump = 0.0f;
	float kasokudo = 0.125f;    //�����x
	float Fallkasokudo = 0.0f;  //���������x
	const float IncrementalAccelerationData[5] = { 0.125,0.125,0.117,0.156,0.156 }; //���������x
	const float FallAcceleration[5] = { 0.437,0.473,0.375,0.562,0.562 };  //�~�����̉����x
	const int InitialSpeed[5] = { -4,-4,-4,-5,-5 };  //����
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
	bool Turn = false;   //���]���邩�ǂ���

	//TO DO ���Â����
	int mari = 0;
	//�����܂�
};

