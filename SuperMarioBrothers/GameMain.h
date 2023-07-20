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
		//delete Stage;
		//delete BlockImg;
	}

	//�`��ȊO�̍X�V������
	virtual AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const override;

private:
	int Stage[15][20];
	int BlockImg[3];

	Mario* mario;
};

