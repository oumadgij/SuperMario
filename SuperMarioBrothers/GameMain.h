#pragma once
#include "SceneManager.h"
#include "Stage.h"
#include "Mario.h"
#include "Item.h"
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
	Stage stage;
	Mario* mario;
	Item** item;
};

