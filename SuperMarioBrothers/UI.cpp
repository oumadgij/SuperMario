#include "UI.h"
#include "Define.h"

#define FONT_SIZE 16

UI::UI()
{
    Sec = 0;
    Coin = 0;
    StopTime = 0;
    ChangeSpeed = 0;
    CoinIndex = 0;
    TimeLimit = 400;
    Score = 0;
    ChangeStart = true;
    ItemType = 0;
    uScore = new UpScore * [5];
    for (int i = 0; i < 5; i++)
    {
        uScore[i] = nullptr;
    }

    for (int i = 0; i < 3; i++)
    {
        TimeNum[i] = 0;
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
    //残り時間を減らす
    CountDown();

    int Save = 0;    //保存用変数
    int Divisor = 100000; //割る数
    //スコアを配列に入れる
    //6桁目
    Save = Score % Divisor;
    ScoreNum[0] = Score / Divisor;
    Divisor /= 10;
    //5～2桁目
    for (int i = 1; i < 4; i++)
    {
        ScoreNum[i] = Save / Divisor;
        Save %= Divisor;
        Divisor /= 10;
    }
    //1桁目
    ScoreNum[5] = Save;

    //コインの枚数を配列に入れる
    Divisor = 10;
    //2桁目
    Save = Coin % Divisor;
    CoinNum[0] = Coin / Divisor;
    //1桁目
    CoinNum[1] = Save;

    Change();

    for (int i = 0; i < 5; i++)
    {
        if (uScore[i] != nullptr)
        {
            uScore[i]->Update();
            //スコアの出現演出がおわったら消す
            if (uScore[i]->GetUpEnd())
            {
                delete uScore[i];
                uScore[i] = nullptr;
            }
        }
    }
}

void UI::CountDown()
{
    if (WaitTime < ++Sec)
    {
        //制限時間がマイナスにならないように
        if (--TimeLimit < 0)
        {
            TimeLimit = 0;
        }
        Sec = 0;
    }

    int Divisor = 100;
    //3桁目
    int SaveTime = TimeLimit % Divisor;
    TimeNum[0] = TimeLimit / Divisor;
    Divisor /= 10;
    //2桁目
    TimeNum[1] = SaveTime / Divisor;
    SaveTime %= Divisor;
    //1桁目
    TimeNum[2] = SaveTime;
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
    DrawGraphF(WINDOW_WIDTH * 0.35f, FONT_SIZE * 2, CoinImg[CoinIndex], TRUE);
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
        DrawGraphF(WINDOW_WIDTH * 0.825f + i * FONT_SIZE, FONT_SIZE * 2, Number[TimeNum[i]], TRUE);
    }

    //動くスコア
    for (int i = 0; i < 5; i++)
    {
        if (uScore[i] == nullptr)
        {
            continue;
        }

        switch (ItemType)
        {
        case 0:
        case 4:
        case 5:
            for (int j = 0; j < 4; j++)
            {
                DrawGraphF(uScore[i]->GetVector().x + j * FONT_SIZE, uScore[i]->GetVector().y, Number[PointNum[ItemType][j]], TRUE);
            }
            break;
        case 1:
            DrawGraphF(uScore[i]->GetVector().x, uScore[i]->GetVector().y, Number[1], TRUE);
            DrawGraphF(uScore[i]->GetVector().x + FONT_SIZE, uScore[i]->GetVector().y, String[20], TRUE);
            DrawGraphF(uScore[i]->GetVector().x + 2 * FONT_SIZE, uScore[i]->GetVector().y, String[15], TRUE);
            break;
        case 2:
        case 3:
            for (int j = 0; j < 3; j++)
            {
                DrawGraphF(uScore[i]->GetVector().x + j * FONT_SIZE, uScore[i]->GetVector().y, Number[PointNum[ItemType][j]], TRUE);
            }
            break;
        }
    }
}

void UI::Instantiation(VECTOR location, int scroll, int xsize,int item_type)
{
    for (int i = 0; i < 5; i++)
    {
        if (uScore[i] == nullptr)
        {
            uScore[i] = new UpScore(location, scroll, xsize);
            break;
        }
    }

    ItemType = item_type;
}

int UI::LoadImages()
{
    if ((PlayerName = LoadGraph("1-1image/UI/name_mario.png")) == -1) return -1;
    if ((Time = LoadGraph("1-1image/UI/time.png")) == -1) return -1;
    if ((World = LoadGraph("1-1image/UI/world.png")) == -1) return -1;
    if (LoadDivGraph("1-1image/UI/num.png", 15, 15, 1, 16, 16, Number) == -1) return -1;
    if (LoadDivGraph("1-1image/UI/uicoin_1.png", 4, 4, 1, 16, 16, CoinImg) == -1) return -1;
    if (LoadDivGraph("1-1image/UI/string.png", 26, 26, 1, 16, 16, String) == -1) return -1;

    return 0;
}

void UI::Change()
{
    if (ChangeStart)
    {
        if (WaitTime / 3 < ++ChangeSpeed)
        {
            if (3 < ++CoinIndex)
            {
                CoinIndex = 0;
                ChangeStart = false;
            }
            ChangeSpeed = 0;
        }
    }
    else
    {
        if (WaitTime / 3 < ++StopTime)
        {
            StopTime = 0;
            ChangeStart = true;
        }
    }
}
