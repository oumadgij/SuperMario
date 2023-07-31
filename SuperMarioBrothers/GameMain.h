#pragma once
#include "SceneManager.h"
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

	//ステージデータ読み込み
	int LoadStages();
	//画像読み込み
	int LoadImages();

	void Scroll(float scroll,int sabun)const;

private:
	int Stage[15][212];  //ステージデータを入れる変数
	int BackData[15][49];
	
	/* TO DO */
	float s_ScrollX = 0.0f;
	float b_ScrollX1 = 0.0f;
	float b_ScrollX2 = 1568.f;
	/*ここまで*/
	
	/*ブロックの画像を入れる変数*/
	int Floor;            //フロアブロック
	int Block;            //通常のブロック
	int EmptyBlock;       //空のブロック
	int StairsBlock;      //階段ブロック
	int DebrisBlock;      //ブロックの破片
	int QuestionBlock[4]; //ハテナブロック
	int b_Block;          //ブラックブロック
	int b_Floor;          //地下のフロアブロック
	int Pipe[4];          //土管
	
	/*背景の画像を入れる変数*/
	int Sky;         //空
	int Cloud[6];    //雲
	int Leaf[3];     //葉
	int Mountain[6]; //山

	Mario* mario;
};

