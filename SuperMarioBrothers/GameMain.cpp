#include "DxLib.h"
#include "GameMain.h"
#include "Define.h"

GameMain::GameMain()
{
	mario = new Mario;
	item = new Item * [5];
	for (int i = 0; i < 5; i++)
	{
		item[i] = nullptr;
	}
}

AbstractScene* GameMain::Update()
{
	mario->Update();

	//マリオが画面の半分に行ったときにスクロールする
	if ((320 <= mario->GetLocation().x) && (0 < mario->GetSpeed()))
	{
		stage.AddScrollX((int)mario->GetSpeed());
	}

	//ステージのヒットチェック事前準備
	stage.ChackStagePreparation(mario->GetLocation()
		, mario->GetSizeX(), mario->GetSizeY());

	//マリオの足元に地面があるかどうか調べる
	if (mario->GetJState() != 2 &&
		(mario->GetMoveVector() < 3 || mario->GetMoveVector() == 4))
	{
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

		//アイテムがあるブロックの時、アイテムを実体化
		if (stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) == 3
			|| stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) == 5
			|| (30 <= stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) && (stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)) <= 32)))
		{
			for (int i = 0; i < 5; i++)
			{
				if (item[i] == nullptr)
				{
					item[i] = new Item(stage.GetPushBlock(0), stage.GetPushBlock(1)
						, stage.GetStage(stage.GetHitBlock(0) - 1, stage.GetHitBlock(1)), mario->GetStage()
						, stage.GetScroll());
					break;
				}
			}
		}
	}
	else
	{
		mario->flg = false;
	}

	//ブロックが動く
	stage.MoveBlock();

	//アイテムのアップデート
	for (int i = 0; i < 5; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Update();
		}
		else
		{
			continue;
		}
	}

	//アイテムが画面外に行ったらアイテムを消す
	for (int i = 0; i < 5; i++)
	{
		if (item[i] != nullptr)
		{
			if (item[i]->Getlocate().x - stage.GetScroll() < -100)
			{
				delete item[i];
				item[i] = nullptr;
			}
		}
	}

	return this;
}

void GameMain::Draw() const
{
	stage.Draw();
	mario->Draw();
	for (int i = 0; i < 5; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Draw(stage.GetScroll());
		}
	}

#define DEBUG
#ifdef DEBUG
	DrawFormatString(400, 300, 0xffffff, "CStage %d", stage.GetStage(stage.GetHitBlock(0)-1, stage.GetHitBlock(1)));
	//DrawFormatString(400, 300, 0x000000, "move_vector %d", mario->GetMoveVector());
#endif // DEBUG

}