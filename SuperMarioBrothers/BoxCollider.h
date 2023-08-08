#pragma once
#include "DxLib.h"

class BoxCollider
{
public:
	//void HitStage();  //�����̏���
protected:
	enum class HIT_SIDE
	{
		DEFAULT = 0,
		LEFT,
		RIGHT,
		TOP,
		UNDER
	};

	VECTOR Location;  //�摜����̍��W
	int XSize, YSize;      //�摜�T�C�Y
	HIT_SIDE side = HIT_SIDE::DEFAULT;  //���������ꏊ
};
