#pragma once

enum class STATE
{
	SMALL = 0,  //���у}���I
	BIG,    //�ł��}���I
	FIRE,   //�t�@�C�A�}���I
	STAR    //���G���
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

