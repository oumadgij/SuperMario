#pragma once
#include "DxLib.h"

class BoxCollider
{
public:
	//void HitStage();  //�����̏���
	bool ChackHitBox(VECTOR location, int x_size, int y_size,int scroll);

protected:

	VECTOR Location;  //�摜����̍��W
	int XSize, YSize;      //�摜�T�C�Y
};
