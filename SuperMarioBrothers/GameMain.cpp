#include "DxLib.h"
#include "GameMain.h"
#include "Define.h"

GameMain::GameMain()
{
	mario = new Mario;

	
}

AbstractScene* GameMain::Update()
{
	mario->Update();

	//マリオが画面の半分に行ったときにスクロールする
	if ((320 <= mario->GetLocation().x) && (0 < mario->GetSpeed()))
	{
		stage.AddScrollX((int)mario->GetSpeed());
	}

	//事前準備
	stage.ChackStagePreparation(mario->GetLocation()
		, mario->GetSizeX(), mario->GetSizeY());

	if (mario->GetJState() != 2 &&
		(mario->GetMoveVector() < 3 || mario->GetMoveVector() == 4))
	{
		//足元に地面があるかどうか調べる
		if (stage.ChackUnder())
		{
			mario->Fall();
		}
	}

	//マリオとステージブロックの当たり判定
	if (stage.ChackHitStage(mario->GetMoveVector()))
	{
		//マリオの位置を戻す
		mario->HitStage(stage.GetHitBlock(0),stage.GetHitBlock(1)
			, stage.GetHitSide());
		mario->flg = true;
		//当たった辺が下の時、ブロックを動かす準備をする
		if (stage.GetHitSide() == 4)
		{
			stage.MoveBlockPreparation();
		}
	}
	else
	{
		mario->flg = false;
	}

	//ブロックが動く
	stage.MoveBlock();

	return this;
}

void GameMain::Draw() const
{
	stage.Draw();
	mario->Draw();

#define DEBUG
#ifndef DEBUG
	DrawFormatString(400, 300, 0x000000, "move_vector %d", mario->GetMoveVector());
#endif // DEBUG

}