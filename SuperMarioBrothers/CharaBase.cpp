#include "CharaBase.h"

CharaBase::CharaBase()
{
	Speed = 0;
	for (int i = 0; i < 2; i++)
	{
		images[i] = 0;
	}
}