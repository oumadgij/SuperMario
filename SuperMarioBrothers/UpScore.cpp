#include "UpScore.h"
#include "Define.h"

UpScore::UpScore()
{
    UpSpeed = 0.8f;
    StartLocation.x = 0.0f;
    StartLocation.y = 0.0f;
    StartLocation.z = 0.0f;
    Location.x = 0.0f;
    Location.y = 0.0f;
    Location.z = 0.0f;
    UpStart = false;
    UpEnd = false;
}

UpScore::UpScore(VECTOR location, int scroll, int xsize)
{
    UpSpeed = 3.0f;
    StartLocation = location;
    //íÜêSÇ…ï‚ê≥
    StartLocation.x -= scroll + xsize / 2;
    Location = StartLocation;
    UpStart = true;
    UpEnd = false;
}

void UpScore::Update()
{
    if (UpStart)
    {
        Location.y -= UpSpeed;
        if (Location.y < StartLocation.y - BLOCK_SIZE * 3)
        {
            UpEnd = true;
        }
    }
}
