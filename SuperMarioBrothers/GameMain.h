#pragma once
#include "SceneManager.h"
class GameMain :
    public AbstractScene
{
public:
	//�R���X�g���N�^
	GameMain();

	//�f�X�g���N�^
	~GameMain() {};

	//�`��ȊO�̍X�V������
	virtual AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const override;

private:
	int Stage[15][20];
	int 
};

