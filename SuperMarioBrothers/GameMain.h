#pragma once
#include "SceneManager.h"
#include "Stage.h"
#include "Mario.h"
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
	int StageData[15][211];    //ステージデータを入れる変数
	int BackData[15][211]; //背景データを入れる変数
	float ScrollX = 0.0f;  //横スクロール
	Stage stage;
	Mario* mario;
};

