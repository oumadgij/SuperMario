#include "UI.h"
#include "DxLib.h"
#include "Define.h"

#define FONT_SIZE 16

UI::UI()
{
    Sec = 0;
    TimeLimit = 400;
    Score = 0;
    for (int i = 0; i < 3; i++)
    {
        Numbers[i] = 0;
    }
    for (int i = 0; i < 6; i++)
    {
        ScoreNum[i] = 0;
    }
    for (int i = 0; i < 2; i++)
    {
        CoinNum[i] = 0;
    }

    if (LoadImages() == -1)
    {
        throw;
    }
}

void UI::Update()
{

}

void UI::CountDown()
{
    if (WaitTime < ++Sec)
    {
        --TimeLimit;
        Sec = 0;
    }

    //100桁目
    int SaveTime = TimeLimit % 100;
    Numbers[0] = TimeLimit / 100;
    //10桁目
    Numbers[1] = SaveTime / 10;
    SaveTime %= 10;
    //1桁目
    Numbers[2] = SaveTime;
}

void UI::Draw() const
{
    //プレイヤーネームとスコア
    DrawGraphF(WINDOW_WIDTH * 0.1f, FONT_SIZE, PlayerName, TRUE);
    for (int i = 0; i < 6; i++)
    {
        DrawGraphF(WINDOW_WIDTH * 0.1f + i * FONT_SIZE, FONT_SIZE * 2, Number[ScoreNum[i]], TRUE);
    }

    //コイン
    DrawGraphF(WINDOW_WIDTH * 0.35f, FONT_SIZE * 2, CointImg[0], TRUE);
    DrawGraphF(WINDOW_WIDTH * 0.35f + FONT_SIZE, FONT_SIZE * 2, Number[11], TRUE);
    for (int i = 0; i < 2; i++)
    {
        DrawGraphF(WINDOW_WIDTH * 0.35f + static_cast<float>((i + 2) * FONT_SIZE), FONT_SIZE * 2, Number[CoinNum[i]], TRUE);
    }

    //ワールド
    DrawGraphF(WINDOW_WIDTH * 0.6f, FONT_SIZE, World, TRUE);
    DrawGraphF(WINDOW_WIDTH * 0.625f, FONT_SIZE * 2, Number[1], TRUE);
    DrawGraphF(WINDOW_WIDTH * 0.625f + FONT_SIZE, FONT_SIZE * 2, Number[10], TRUE);
    DrawGraphF(WINDOW_WIDTH * 0.625f + 2 * FONT_SIZE, FONT_SIZE * 2, Number[1], TRUE);

    //時間
    DrawGraphF(WINDOW_WIDTH * 0.8f, FONT_SIZE, Time, TRUE);
    for (int i = 0; i < 3; i++)
    {
        DrawGraphF(WINDOW_WIDTH * 0.825f + i * FONT_SIZE, FONT_SIZE * 2, Number[Numbers[i]], TRUE);
    }
}

int UI::LoadImages()
{
    if ((PlayerName = LoadGraph("1-1image/UI/name_mario.png")) == -1) return -1;
    if ((Time = LoadGraph("1-1image/UI/time.png")) == -1) return -1;
    if ((World = LoadGraph("1-1image/UI/world.png")) == -1) return -1;
    if ((Coin = LoadGraph("1-1image/UI/world.png")) == -1) return -1;
    if (LoadDivGraph("1-1image/UI/num.png", 15, 15, 1, 16, 16, Number) == -1) return -1;
    if (LoadDivGraph("1-1image/UI/uicoin_1.png", 4, 4, 1, 16, 16, CointImg) == -1) return -1;

    return 0;
}
