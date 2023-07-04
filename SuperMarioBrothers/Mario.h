#pragma once
class Mario
{
public:
	Mario();
	~Mario() {};

	void Update();
	void Draw()const;

private:
	int marioImg[9];
	int x, y;
	int i;
};

