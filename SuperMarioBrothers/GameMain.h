#pragma once
#include "SceneManager.h"
#include "Stage.h"
#include "Mario.h"
#include "Item.h"
class GameMain :
    public AbstractScene
{
public:
	//コンストラクタ
	GameMain();

	//デストラクタ
	~GameMain()
	{
		InitGraph();
	}

	//描画以外の更新を実装
	virtual AbstractScene* Update() override;

	//描画に関することを実装
	virtual void Draw() const override;

private:
	Stage stage;
	Mario* mario;
	Item** item;
};

