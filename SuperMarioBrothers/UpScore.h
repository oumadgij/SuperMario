#pragma once
#include "DxLib.h"

class UpScore
{
public:
	UpScore();
	UpScore(VECTOR location, int scroll, int xsize);

	void Update();
	VECTOR GetVector()const { return Location; }
	bool GetUpEnd()const { return UpEnd; }

private:
	VECTOR StartLocation;  //�X�^�[�g���̍��W
	VECTOR Location;//���݂̍��W
	bool UpStart;   //�X�R�A�o�������邩?
	bool UpEnd;     //�X�R�A�o��������?
	float UpSpeed;
};

