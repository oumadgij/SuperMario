#include "Mario.h"
#include "DxLib.h"

Mario::Mario()
{
	x = 6 * 32;
	y = 12 * 32;
	i = LoadDivGraph("1-1image/Mario/mario.png", 9, 9, 1, 32, 32, marioImg);
}

void Mario::Update()
{
	if (i != 0)
	{
		printf("ƒGƒ‰[\n");
	}
	else
	{
		printf("’Êí¬Œ÷");
	}
}

void Mario::Draw() const
{
	DrawGraph(x, y, marioImg[0], TRUE);
}
