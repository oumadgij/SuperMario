#pragma once
#include "SceneManager.h"
#include "Stage.h"
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

private:
	int StageData[15][211];    //�X�e�[�W�f�[�^������ϐ�
	int BackData[15][211]; //�w�i�f�[�^������ϐ�
	float ScrollX = 0.0f;  //���X�N���[��
	Stage stage;
	Mario* mario;
};

