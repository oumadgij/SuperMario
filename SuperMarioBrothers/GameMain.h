#pragma once
#include "SceneManager.h"
#include "Mario.h"
class GameMain :
    public AbstractScene
{
public:
	//�R���X�g���N�^
	GameMain();

	//�f�X�g���N�^
	~GameMain()
	{
		InitGraph();
	}

	//�`��ȊO�̍X�V������
	virtual AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const override;

	//�X�e�[�W�f�[�^�ǂݍ���
	int LoadStages();
	//�摜�ǂݍ���
	int LoadImages();

	void Scroll(float scroll,int sabun)const;

private:
	int Stage[15][212];  //�X�e�[�W�f�[�^������ϐ�
	int BackData[15][49];
	
	/* TO DO */
	float s_ScrollX = 0.0f;
	float b_ScrollX1 = 0.0f;
	float b_ScrollX2 = 1568.f;
	/*�����܂�*/
	
	/*�u���b�N�̉摜������ϐ�*/
	int Floor;            //�t���A�u���b�N
	int Block;            //�ʏ�̃u���b�N
	int EmptyBlock;       //��̃u���b�N
	int StairsBlock;      //�K�i�u���b�N
	int DebrisBlock;      //�u���b�N�̔j��
	int QuestionBlock[4]; //�n�e�i�u���b�N
	int b_Block;          //�u���b�N�u���b�N
	int b_Floor;          //�n���̃t���A�u���b�N
	int Pipe[4];          //�y��
	
	/*�w�i�̉摜������ϐ�*/
	int Sky;         //��
	int Cloud[6];    //�_
	int Leaf[3];     //�t
	int Mountain[6]; //�R

	Mario* mario;
};

