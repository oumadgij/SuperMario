#include "Item.h"
#include "DxLib.h"
#include "Define.h"

Item::Item()
{
	UpEnd = false;
	XSize = BLOCK_SIZE;
	YSize = BLOCK_SIZE;
	UpSpeed = 0.0f;
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
	UpEnd = false;

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
		UpSpeed = 3.0f;
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
			if (Location.y < StartLocate.y - (BLOCK_SIZE * 2))
			{
				UpSpeed = -UpSpeed;
			}
			if (StartLocate.y < Location.y)
			{
				Location.y = StartLocate.y;
				UpEnd = true;
			}
		}
		else
		{
			if (Location.y < StartLocate.y - BLOCK_SIZE)
			{
				UpEnd = true;
			}
		}
	}
}

void Item::Draw(int scroll) const
{
	DrawFormatString(400, 400, 0xffffff, "キノコ X：%f Y:%f",Location.x - scroll /*-stage.GetScroll()*/, Location.y);
	DrawFormatString(400, 440, 0xffffff, "itemtype %d", (int)ItemType);
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
		DrawGraph(Location.x - scroll, Location.y, Coin[0], TRUE);
		break;
	case ITEM_TYPE::M_COIN:
		DrawGraph(Location.x - scroll, Location.y, M_Coin[0], TRUE);
		break;
	case ITEM_TYPE::FLOWER:
		DrawGraph(Location.x - scroll, Location.y, Flower[0], TRUE);
		break;
	case ITEM_TYPE::STAR:
		DrawGraph(Location.x - scroll, Location.y, Star[0], TRUE);
		break;
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
