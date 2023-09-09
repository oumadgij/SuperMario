#pragma once
#include "CharaBase.h"

enum class STATE
{
	SMALL = 0,  //���у}���I
	BIG,        //�ł��}���I
	FIRE,       //�t�@�C�A�}���I
	STAR_SMALL, //���G���(��)
	STAR_BIG	//���G���(��)
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
	void Hit(int item_type);
	virtual void HitStage(int h_block, int w_block
		, int hit_side, int scroll)override;  //�����̏���
	virtual void Fall()override;  //�~������
	float GetSpeed()const { return Speed; }
	int GetStage()const { return (int)State; }


	//TO DO���Â����
	//bool flg;
	//�����܂�

private:
	void SpeedUp();          //�_�b�V�����A���X�ɃX�s�[�h���グ��
	void SpeedReduction();   //��������
	void PreparingJump();    //�W�����v�̏���
	void Jump();
	virtual void Animation()override;
	int LoadImages();

private:
	//�摜�p�ϐ�
	int sMario[10];  //�������}���I
	int bMario[10];  //�傫���}���I
	int fMario[10];  //�t�@�C�A�}���I
	int Star_bMario[36];//�傫���}���I(�X�^�[)
	int Star_sMario[32];//�������}���I(�X�^�[)

	int Life;            //���C�t��
	float Inertia;       //����
	bool Jumping;        //�W�����v���Ă��邩(true�F�W�����v���Ă��� false�F�W�����v���Ă��Ȃ�)
	STATE State;         //�}���I�̏��
	STATE SaveState;     //�}���I�̏�Ԃ�ۑ�����
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

	/*�A�j���[�V�����ϐ�*/
	int StarLimit = 720;
	int StarTime = 0;
	const int DownSpeedTime = 120;
	int H = 0;

	//TO DO ���Â����
	//�����܂�
};

