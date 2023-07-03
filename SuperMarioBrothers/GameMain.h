#pragma once
#include "SceneManager.h"
class GameMain :
    public AbstractScene
{
public:
	//コンストラクタ
	GameMain();

	//デストラクタ
	~GameMain() {};

	//描画以外の更新を実装
	virtual AbstractScene* Update() override;

	//描画に関することを実装
	virtual void Draw() const override;

private:
	int Stage[15][20];
	int 
};

