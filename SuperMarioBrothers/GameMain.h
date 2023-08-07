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

private:
	int Stage[15][211];  //�X�e�[�W�f�[�^������ϐ�
	int BackData[15][211];
	float ScrollX = 0.0f;
	
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
	int BackImages[16];

	Mario* mario;
};

