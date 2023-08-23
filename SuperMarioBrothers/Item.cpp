#include "Item.h"
#include "DxLib.h"
#include "Define.h"

Item::Item()
{
	UpEnd = false;
	XSize = BLOCK_SIZE;
	YSize = BLOCK_SIZE;
	UpSpeed = 0.0f;
	Speed = 1.0f;
	Move = MOVE_VECTOR::STOP;
	for (int i = 0; i < 2; i++)
	{
		Locate[i] = -1;
	}

	//画像の読み込み
	if (LoadImages() == -1)
	{
		perror("LoadImage Error");
		throw;
	}
}

Item::Item(int block_y, int block_x
	,int stage_num, int player_state,int scroll)
{
	Move = MOVE_VECTOR::STOP;
	UpEnd = false;
	Speed = 1.0f;
	FallSpeed = 4.0f;
	XSize = BLOCK_SIZE;
	YSize = BLOCK_SIZE;
	Locate[0] = block_y;
	Locate[1] = block_x;
	Location.y = (float)Locate[0] * BLOCK_SIZE;
	Location.x = (float)Locate[1] * BLOCK_SIZE;
	StartLocate = Location;

	switch (stage_num)
	{
	case 3:   //コイン
	case 31:
		ItemType = ITEM_TYPE::COIN;
		break;
	case 5:   //1UPキノコ
		ItemType = ITEM_TYPE::UP_MUSHROOM;
		break;
	case 30:  //キノコ・フラワー
		//マリオが小さいサイズ以外ならフラワーを出す
		if (0 < player_state)
		{
			ItemType = ITEM_TYPE::FLOWER;
		}
		else  //マリオが小さいならキノコを出す
		{
			ItemType = ITEM_TYPE::MUSHROOM;
		}
		break;
	case 32:  //スター
		ItemType = ITEM_TYPE::STAR;
		break;
	}

	if (ItemType == ITEM_TYPE::COIN)
	{
		UpSpeed = 5.0f;
	}
	else
	{
		UpSpeed = 0.8f;
	}

	//画像の読み込み
	if (LoadImages() == -1)
	{
		perror("LoadImage Error");
		throw;
	}
}

void Item::Update()
{
	//上にあげる
	if (!UpEnd)
	{
		Location.y -= UpSpeed;
		if (ItemType == ITEM_TYPE::COIN)
		{
			if (Location.y < StartLocate.y - BLOCK_SIZE * 3)
			{
				UpSpeed = -UpSpeed;
			}
			if (StartLocate.y < Location.y)
			{
				Location.y = StartLocate.y;
				Move = MOVE_VECTOR::STOP;
				UpEnd = true;
			}
		}
		else
		{
			if (Location.y < StartLocate.y - BLOCK_SIZE)
			{
				//スターの時MoveをUPにする
				if (ItemType == ITEM_TYPE::STAR)
				{
					Move = MOVE_VECTOR::UP;
				}
				else
				{
					Move = MOVE_VECTOR::RIGHT;
				}
				UpEnd = true;
			}
		}
	}

	//上に上がり切ったら
	//コインとフラワー以外は移動させる
	if (ItemType != ITEM_TYPE::COIN && ItemType != ITEM_TYPE::FLOWER)
	{
		if (UpEnd && Move != MOVE_VECTOR::STOP)
		{
			Location.x += Speed;
		}

		if (ItemType == ITEM_TYPE::STAR && Move == MOVE_VECTOR::UP)
		{
			Location.y -= UpSpeed;
		}

		if (Move == MOVE_VECTOR::DOWN)
		{
			Location.y += FallSpeed;
		}
	}

	//キノコ・1UPキノコ以外はアニメーションを更新する
	if (ItemType != ITEM_TYPE::MUSHROOM && ItemType != ITEM_TYPE::UP_MUSHROOM)
	{
		Animation();
	}
}

void Item::Draw(int scroll) const
{
	switch (ItemType)
	{
	case ITEM_TYPE::MUSHROOM:
		DrawGraphF(Location.x - scroll, Location.y, Mushroom, TRUE);
		//DrawGraph(Location.x - scroll, Location.y, Mushroom, TRUE);
		break;
	case ITEM_TYPE::UP_MUSHROOM:
		DrawGraph(Location.x- scroll, Location.y, UP_Mushroom, TRUE);
		break;
	case ITEM_TYPE::COIN:
		DrawGraph(Location.x - scroll, Location.y, Coin[aIndex], TRUE);
		break;
	case ITEM_TYPE::M_COIN:
		DrawGraph(Location.x - scroll, Location.y, M_Coin[aIndex], TRUE);
		break;
	case ITEM_TYPE::FLOWER:
		DrawGraph(Location.x - scroll, Location.y, Flower[aIndex], TRUE);
		break;
	case ITEM_TYPE::STAR:
		DrawGraph(Location.x - scroll, Location.y, Star[aIndex], TRUE);
		break;
	}

#define DEBUG
#ifdef DEBUG
	DrawBox(Location.x - scroll, Location.y, Location.x + XSize-scroll, Location.y + YSize, 0xff0000, FALSE);
	DrawFormatString(0, 150, 0xffffff, "IMoveVector %d", (int)Move);
	DrawFormatString(0, 20, 0xffffff, "左上 X %d Y %d", ((int)Location.x-XSize/2) / BLOCK_SIZE,((int)Location.y-YSize/2)/BLOCK_SIZE);
	DrawFormatString(0, 40, 0xffffff, "右下 X %d Y %d", ((int)Location.x + (XSize / 2-1)) / BLOCK_SIZE, ((int)Location.y + (YSize / 2-1)) / BLOCK_SIZE);
	DrawFormatString(300, 20, 0xffffff, "座標 X %f Y %f", Location.x, Location.y);
#endif // DEBUG

}

void Item::HitStage(int h_block, int w_block
	, int hit_side, int scroll)
{
	VECTOR vec;

	vec.y = static_cast<float>(h_block * BLOCK_SIZE);
	vec.x = static_cast<float>(w_block * BLOCK_SIZE) + scroll;

	switch (hit_side) //当たったブロックの辺の位置
	{
	case 1:  //左側
		Location.x = vec.x - BLOCK_SIZE;
		Inversion();
		break;
	case 2: //右側
		Location.x = vec.x + BLOCK_SIZE;
		Inversion();
		break;
	case 3:   //上側
		Location.y = vec.y - YSize;
		IsAir = false;
		if (Speed < 0) //進行方向にMoveを変更
		{
			Move = MOVE_VECTOR::LEFT;
		}
		else
		{
			Move = MOVE_VECTOR::RIGHT;
		}
		break;
	case 4: //下側
		Location.y = vec.y + YSize;
		//降下準備
		Move = MOVE_VECTOR::DOWN;
		break;
	}
}

void Item::Fall()
{
	Move = MOVE_VECTOR::DOWN;
	IsAir = true;
	//Location.y += FallSpeed;
}

void Item::Inversion()
{
	if (Move == MOVE_VECTOR::LEFT)
	{
		Move = MOVE_VECTOR::RIGHT;//進行方向を反転する
	}
	if (Move == MOVE_VECTOR::RIGHT)
	{
		Move = MOVE_VECTOR::LEFT; //進行方向を反転する
	}

	Speed *= -1;
}

void Item::Animation()
{
	if (AnimSpeed/4 < ++AnimWait)
	{
		if (3 < ++aIndex)
		{
			aIndex = 0;
		}
		AnimWait = 0;
	}
}

int Item::LoadImages()
{
	if ((Mushroom = LoadGraph("1-1image/Item/mushroom.png")) == -1) return -1;
	if ((UP_Mushroom = LoadGraph("1-1image/Item/1up_mushroom.png")) == -1) return -1;
	if (LoadDivGraph("1-1image/Item/coin.png", 4, 4, 1, 32, 32, Coin) == -1) return -1;
	if (LoadDivGraph("1-1image/Item/mukidasitika_coin.png", 4, 4, 1, 32, 32, M_Coin) == -1) return -1;
	if (LoadDivGraph("1-1image/Item/flower.png", 4, 4, 1, 32, 32, Flower) == -1) return -1;
	if (LoadDivGraph("1-1image/Item/star.png", 4, 4, 1, 32, 32, Star) == -1) return -1;

	return 0;
}
