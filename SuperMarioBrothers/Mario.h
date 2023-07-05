#pragma once

enum class STATE
{
	SMALL = 0,  //ちびマリオ
	BIG,    //でかマリオ
	FIRE,   //ファイアマリオ
	STAR    //無敵状態
};

class Mario
{
public:
	Mario();
	~Mario() {};

	void Update();
	void Draw()const;

private:
	int marioImg[10];
	int x, y;
	STATE state;
	int m, n;
};

