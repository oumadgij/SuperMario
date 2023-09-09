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
	VECTOR StartLocation;  //スタート時の座標
	VECTOR Location;//現在の座標
	bool UpStart;   //スコア出現させるか?
	bool UpEnd;     //スコア出現完了か?
	float UpSpeed;
};

