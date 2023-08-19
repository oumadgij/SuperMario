#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "Stage.h"
#include "Define.h"

Stage::Stage()
{
    Push = 0.0f;

    //�f�[�^�̓ǂݍ���
    if (LoadStages() == -1)
    {
        perror("LoadStage Error");
        throw;
    }
    if (LoadBack() == -1)
    {
        perror("LoadBack Error");
        throw;
    }
    //�摜�̓ǂݍ���
    if (LoadImages() == -1)
    {
        perror("LoadImage Error");
        throw;
    }

    for (int i = 0; i < STAGE_HEIGHT_BLOCK; i++)
    {
        for (int j = 0; j < STAGE_WIDTH_BLOCK; j++)
        {
            ChackStage[i][j] = StageData[i][j];
        }
    }
}

void Stage::Draw() const
{
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			//�w�i��`��
			DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, BackImages[BackData[i][j]], TRUE);

            //�}���I���Ԃ������u���b�N�Ȃ�
            //p��ω�������
            int p = 0;
            if ((i == PushBlock[0])&&(j == PushBlock[1]))
            {
                p = Push;
            }

			//�X�e�[�W��`��
			switch (StageData[i][j])
			{
			case 1:  //�t���A�u���b�N
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Floor, TRUE);
				break;
			case 2:  //���ʂ̃u���b�N
            case 32:
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE + p, Block, TRUE);
				break;
			case 3:  //�n�e�i�u���b�N
            case 30:
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, QuestionBlock[0], TRUE);
				break;
			case 4:  //��u���b�N
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE + p, EmptyBlock, TRUE);
				break;
			case 6:  //�K�i�u���b�N
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, StairsBlock, TRUE);
				break;
			case 7:  //�y��
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[0], TRUE);
				break;
			case 8:	//�y��
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[1], TRUE);
				break;
			case 9:	//�y��
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[2], TRUE);
				break;
			case 10://�y��
				DrawGraph(j * BLOCK_SIZE - ScrollX, i * BLOCK_SIZE, Pipe[3], TRUE);
				break;
			}
		}
	}

#define DEBUG
#ifdef DEBUG
    for (int i = 0; i < 15; i++)
    {
        DrawFormatString(285, 15 + i * 10, 0x00ff00, "%d", i);
    }
    for (int j = 0; j < 20; j++)
    {
        DrawFormatString(300+j*15, 0, 0x00ff00, "%d", j);
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            DrawFormatString(300 + j * 15, 15 + i * 10,0x000000, "%d", ChackStage[i][j]);
        }
    }

    DrawFormatString(400, 250, 0x000000, "scroll %d  / %d", ScrollX, ScrollX / BLOCK_SIZE);
    DrawFormatString(0, 260, 0x000000, "down %d", down);
    DrawFormatString(0, 100, 0x000000, "Push %f", Push);
    DrawFormatString(0, 140, 0x000000, "1�F�� 2�F�E 3�F�� 4�F��\nSide�F%d", (int)Side);
    DrawFormatString(0, 180, 0x000000, "HitBlock h %d ���W %d", HitBlock[0], HitBlock[0] * BLOCK_SIZE);
    DrawFormatString(0, 220, 0x000000, "HitBlock w %d ���W %d", HitBlock[1], HitBlock[1] * BLOCK_SIZE);
   /* DrawFormatString(0, 180, 0x000000, "PushBlock h %d", PushBlock[0]);
    DrawFormatString(0, 220, 0x000000, "PushBlock w %d", PushBlock[1]);*/
    DrawFormatString(10, 10, 0xffffff, "�����̃X�e�[�W�ʒu\nX %d Y %d", vertex[0][1],vertex[0][0]);
    DrawFormatString(10, 50, 0xffffff, "�E���̃X�e�[�W�ʒu\nX %d Y %d", vertex[1][1], vertex[1][0]);
#endif // DEBUG

}

int Stage::LoadStages()
{
	FILE* fp;
	char buf[1000];
	char* p;
	int i = 0, ret;
	int j = 0;

	//�X�e�[�W�f�[�^��ǂݍ���
	fopen_s(&fp, "StageData/Stage.csv", "r");
	if (fp == NULL)
	{
		perror("LoadFile Error");
		return -1;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		p = strtok(buf, ",");
		ret = sscanf(p, "%d", &StageData[i][j++]);

		while (p != NULL)
		{
			p = strtok(NULL, ",");
			if (p != NULL)
			{
				ret = sscanf(p, "%d", &StageData[i][j++]);
			}
		}

		++i;
		j = 0;
	}
	fclose(fp);

	return 0;
}

int Stage::LoadBack()
{
	//�w�i�f�[�^��ǂݍ���
	FILE* fp;
	char buf[1000];
	char* p;
	int i = 0, ret;
	int j = 0;
	fopen_s(&fp, "StageData/BackGround.csv", "r");
	if (fp == NULL)
	{
		return -1;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		p = strtok(buf, ",");
		ret = sscanf(p, "%d", &BackData[i][j++]);

		while (p != NULL)
		{
			p = strtok(NULL, ",");
			if (p != NULL)
			{
				ret = sscanf(p, "%d", &BackData[i][j++]);
			}
		}

		++i;
		j = 0;
	}
	fclose(fp);

	return 0;
}

int Stage::LoadImages()
{
	//�u���b�N
	if ((Block = LoadGraph("1-1image/Block/block.png")) == -1) return -1;
	if ((Floor = LoadGraph("1-1image/Block/floor.png")) == -1) return -1;
	if ((StairsBlock = LoadGraph("1-1image/Block/kai_block.png")) == -1) return -1;
	if ((EmptyBlock = LoadGraph("1-1image/Block/kara_block.png")) == -1) return -1;
	if ((DebrisBlock = LoadGraph("1-1image/Block/bloak_1.png")) == -1) return -1;
	if ((b_Block = LoadGraph("1-1image/Block/blackblock.png")) == -1) return -1;
	if ((b_Floor = LoadGraph("1-1image/Block/tika_floor.png")) == -1) return -1;
	if ((Pipe[0] = LoadGraph("1-1image/dokan_left_up.png")) == -1) return -1;
	if ((Pipe[1] = LoadGraph("1-1image/dokan_right_up.png")) == -1) return -1;
	if ((Pipe[2] = LoadGraph("1-1image/dokan_left_down.png")) == -1) return -1;
	if ((Pipe[3] = LoadGraph("1-1image/dokan_right_down.png")) == -1) return -1;
	if (LoadDivGraph("1-1image/Block/hatena.png", 4, 4, 1, 32, 32, QuestionBlock) == -1) return -1;
	/*�w�i*/
	//��
	if ((BackImages[0] = LoadGraph("1-1image/sora.png")) == -1) return -1;
	//��
	if ((BackImages[1] = LoadGraph("1-1image/ha0.png")) == -1) return -1;
	if ((BackImages[2] = LoadGraph("1-1image/ha1.png")) == -1) return -1;
	if ((BackImages[3] = LoadGraph("1-1image/ha2.png")) == -1) return -1;
	//�R
	if ((BackImages[4] = LoadGraph("1-1image/mountain_left.png")) == -1) return -1;
	if ((BackImages[5] = LoadGraph("1-1image/mountain_right.png")) == -1) return -1;
	if ((BackImages[6] = LoadGraph("1-1image/mountain_up.png")) == -1) return -1;
	if ((BackImages[7] = LoadGraph("1-1image/mountain_surface.png")) == -1) return -1;
	if ((BackImages[8] = LoadGraph("1-1image/mountain_surface1.png")) == -1) return -1;
	if ((BackImages[9] = LoadGraph("1-1image/mountain_surface2.png")) == -1) return -1;
	//�_
	if ((BackImages[10] = LoadGraph("1-1image/cloud6.png")) == -1) return -1;
	if ((BackImages[11] = LoadGraph("1-1image/cloud5.png")) == -1) return -1;
	if ((BackImages[12] = LoadGraph("1-1image/cloud4.png")) == -1) return -1;
	if ((BackImages[13] = LoadGraph("1-1image/cloud1.png")) == -1) return -1;
	if ((BackImages[14] = LoadGraph("1-1image/cloud2.png")) == -1) return -1;
	if ((BackImages[15] = LoadGraph("1-1image/cloud3.png")) == -1) return -1;


	return 0;
}

void Stage::ChackStagePreparation(VECTOR location, int x_size, int y_size)
{
    //���肷��X�e�[�W�͈̔͂����߂�
    for (int h = 0; h < STAGE_HEIGHT_BLOCK; h++)
    {
        for (int w = 0; w < STAGE_WIDTH_BLOCK; w++)
        {
            ChackStage[h][w] = StageData[h][w + ScrollX / BLOCK_SIZE];
        }
    }

    /*
    * ���g�̔��肷��͈͂����߂�
    *  ���͈͂͋�`�̊J�n���W���܂ނ���
    *    �I���ʒu�����߂�Ƃ��́A�T�C�Y��-1���Ă��狁�߂�
    */
    //�J�n�ʒu(����)
    //Y���W
    vertex[0][0] = ((int)location.y - y_size / 2) / BLOCK_SIZE;
    //X���W
    vertex[0][1] = ((int)location.x - x_size / 2) / BLOCK_SIZE;

    //�I���ʒu(�E��)
    //Y���W
    vertex[1][0] = ((int)location.y + (y_size / 2 - 1)) / BLOCK_SIZE;
    //X���W
    vertex[1][1] = ((int)location.x + (x_size / 2 - 1)) / BLOCK_SIZE;

    /*���g���X�e�[�W�͈̔͂𒴂��Ă��Ȃ����`�F�b�N*/
    for (int i = 0; i < 2; i++)
    {
        //Y���W���`�F�b�N
        if (STAGE_HEIGHT_BLOCK < vertex[i][0]) //�X�e�[�W���傫����
        {
            vertex[i][0] = STAGE_HEIGHT_BLOCK;
        }
        //X���W���`�F�b�N
        if (vertex[i][1] < 0) //0��菬������
        {
            vertex[i][1] = 0;
        }
    }
}

//�����蔻����Ƃ�(false�F�������Ă��Ȃ� true�F�������Ă���)
bool Stage::ChackHitStage(int move_vector)
{
    /*
    * ���������ɂ����
    * ���肷��ӂ�����o��
    */
    int check_y = 0;
    int check_x = 0;
    //�E�Ɉړ����Ă���
    if (move_vector == 2)
    {
        check_x = 1;
    }//���Ɉړ����Ă���
    else if (move_vector == 4)
    {
        check_y = 1;
    }

    int start = 0;
    int end = 1;
    /*���肷��͈͂Ƀu���b�N���Ȃ����`�F�b�N*/
    for (int h = vertex[start][0] + check_y; h <= vertex[end][0]; h++)
    {
        if (STAGE_HEIGHT_BLOCK == h)
        {
            break;
        }

        for (int w = vertex[start][1] + check_x; w <= vertex[end][1]; w++)
        {
            if (ChackStage[h][w] != 0 && ChackStage[h][w] < 50)  //�u���b�N������������
            {
                switch (move_vector)
                {
                case 1:
                    Side = HIT_SIDE::RIGHT;
                    ++w;
                    break;
                case 2:
                    Side = HIT_SIDE::LEFT;
                    break;
                case 3:
                    Side = HIT_SIDE::UNDER;
                    ++h;
                    break;
                case 4:
                    Side = HIT_SIDE::TOP;
                    break;
                }

                HitBlock[0] = h;
                HitBlock[1] = w;
                play[0] = h;
                play[1] = w;

                return true;  //�u���b�N�ɓ������Ă���
            }
        }
    }
    //for (int h = static_cast<int>(vertex[start].y); h <= vertex[end].y; h++)
    //{
    //    for (int w = static_cast<int>(vertex[start].x); w <= vertex[end].x; w++)
    //    {
    //        if (stage[h][w] != 0 && stage[h][w] < 50)  //�u���b�N������������
    //        {
    //            if (jState == 2)
    //            {
    //                side = HIT_SIDE::UNDER;
    //                ++h;

    //                HitBlock[0] = h;
    //                HitBlock[1] = w - scroll / BLOCK_SIZE;
    //                return true;
    //            }

    //            switch (move_vector)
    //            {
    //            case 1:
    //                side = HIT_SIDE::RIGHT;
    //                ++w;
    //                break;
    //            case 2:
    //                side = HIT_SIDE::LEFT;
    //                break;
    //            case 3:
    //                side = HIT_SIDE::UNDER;
    //                ++h;
    //                break;
    //            case 4:
    //                side = HIT_SIDE::TOP;
    //                break;
    //            }

    //            HitBlock[0] = h;
    //            HitBlock[1] = w - scroll / BLOCK_SIZE;

    //            return true;  //�u���b�N�ɓ������Ă���
    //        }
    //    }
    //}

    return false;
}

bool Stage::ChackUnder()
{
    int start = 0;
    int end = 1;
    for (int h = vertex[start][0]; h <= vertex[end][0]; h++)
    {
        for (int w = vertex[end][1]; w <= vertex[end][1]; w++)
        {
            if (ChackStage[h+1][w] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

void Stage::MoveBlockPreparation()
{
    down = 1;
    PushSpeed = 0.8f;
    SaveSide = Side;
    Side = HIT_SIDE::DEFAULT;
    PushBlock[0] = HitBlock[0] - 1;
    PushBlock[1] = HitBlock[1] + ScrollX / BLOCK_SIZE;
    PushEnd = false;

    //�A�C�e�������鏊�͋�u���b�N�ɂ���
    if (StageData[PushBlock[0]][PushBlock[1]] == 30
        || StageData[PushBlock[0]][PushBlock[1]] == 3)
    {
        StageData[PushBlock[0]][PushBlock[1]] = 4;
    }
}

void Stage::MoveBlock()
{
    if (SaveSide == HIT_SIDE::UNDER)
    {
        if (down == 1)
        {
            sec = 0;
            Push -= PushSpeed;
        }
        else if (down == 2)
        {
            sec = 0;
            Push += PushSpeed;
        }

        if (Push < (BLOCK_SIZE / 2) * -1)
        {
            down = 2;
        }

        //���̈ʒu�ɖ߂����烊�Z�b�g
        if (0 < Push)
        {
            for (int i = 0; i < 2; i++)
            {
                HitBlock[i] = -1;
            }
            Push = 0;
            SaveSide = HIT_SIDE::DEFAULT;
            PushEnd = true;
        }
       
    }
}
