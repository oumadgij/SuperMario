#include "CharaBase.h"

CharaBase::CharaBase()
{
	Speed = 0.0f;
	AnimWait = 0;
	IsAir = false;
	Move = MOVE_VECTOR::STOP;
}