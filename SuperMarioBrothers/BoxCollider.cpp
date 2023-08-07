#include "BoxCollider.h"
#include "Define.h"

//�����蔻����Ƃ�(false�F�������Ă��Ȃ� true�F�������Ă���)
bool BoxCollider::ChackHitStage(int stage[][211], int jState, int move_vector, float scroll)
{
    /*
    * ���g�̔��肷��͈͂����߂�
    *  ���͈͂͋�`�̊J�n���W���܂ނ���
    *    �I���ʒu�����߂�Ƃ��́A�T�C�Y��-1���Ă��狁�߂�
    */
    float vertex[2][2];
    //�J�n�ʒu(����)
    //Y���W
    vertex[0][0] = (Location.y - YSize / 2) / BLOCK_SIZE;
    //X���W
    vertex[0][1] = (Location.x - XSize / 2) / BLOCK_SIZE + scroll / BLOCK_SIZE;

    //�I���ʒu(�E��)
    //Y���W
    vertex[1][0] = (Location.y + (YSize / 2 - 1)) / BLOCK_SIZE;
    //X���W
    vertex[1][1] = (Location.x + (XSize / 2 - 1)) / BLOCK_SIZE + scroll / BLOCK_SIZE;
    //VECTOR vertex[2];
    ////�J�n�ʒu(����)
    // //X���W
    //vertex[0].x = (Location.x - XSize / 2) / BLOCK_SIZE + scroll / BLOCK_SIZE;
    // //Y���W
    //vertex[0].y = (Location.y - YSize / 2) / BLOCK_SIZE;

    ////�I���ʒu(�E��)
    // //X���W
    //vertex[1].x = (Location.x + (XSize/2 - 1)) / BLOCK_SIZE + scroll / BLOCK_SIZE;
    // //Y���W
    //vertex[1].y = (Location.y + (YSize/2 - 1)) / BLOCK_SIZE;

    /*���g���X�e�[�W�͈̔͂𒴂��Ă��Ȃ����`�F�b�N*/
    for (int i = 0; i < 2; i++)
    {
        //Y���W���`�F�b�N
        if (STAGE_HEIGHT_BLOCK < vertex[i][0]) //�X�e�[�W���傫����
        {
            vertex[i][0] = STAGE_HEIGHT_BLOCK - 1;
        }
        //X���W���`�F�b�N
        if (vertex[i][1] < 0) //0��菬������
        {
            vertex[i][1] = 0;
        }
    }
    //for (int i = 0; i < 2; i++)
    //{
    //    //X���W���`�F�b�N
    //    if (vertex[i].x < 0) //0��菬������
    //    {
    //        vertex[i].x = 0;
    //    }
    //    //Y���W���`�F�b�N
    //    if (STAGE_HEIGHT_BLOCK < vertex[i].y) //�X�e�[�W���傫����
    //    {
    //        vertex[i].y = STAGE_HEIGHT_BLOCK - 1;
    //    }
    //}

    /*
    * ���������ɂ����
    * ���肷��ӂ�����o��
    */
    int check_y = 0;
    int check_x = 0;
    //���Ɉړ����Ă���
    if (move_vector == 1)
    {
        check_x = 1;
    }
    //��Ɉړ����Ă���
    if (move_vector == 3)
    {
        check_y = 1;
    }

    int start = 0;
    int end = 1;
    /*���肷��͈͂Ƀu���b�N���Ȃ����`�F�b�N*/
    for (int h = static_cast<int>(vertex[start+check_y][0]); h <= vertex[end][0]; h++)
    {
        for (int w = static_cast<int>(vertex[start+check_x][1]); w <= vertex[end][1]; w++)
        {
            if (stage[h][w] != 0 && stage[h][w] < 50)  //�u���b�N������������
            {
                switch (move_vector)
                {
                case 1:
                    side = HIT_SIDE::RIGHT;
                    ++w;
                    break;
                case 2:
                    side = HIT_SIDE::LEFT;
                    break;
                case 3:
                    side = HIT_SIDE::UNDER;
                    ++h;
                    break;
                case 4:
                    side = HIT_SIDE::TOP;
                    break;
                }

                HitBlock[0] = h;
                HitBlock[1] = w - scroll / BLOCK_SIZE;

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

bool BoxCollider::ChackUnder(int stage[][211], float scroll)
{
    /*���g�̔��肷��͈͂����߂�*/
    VECTOR vertex[2];
    //����
    //Y���W
    vertex[0].y = (Location.y + YSize / 2) / BLOCK_SIZE;
    //X���W
    vertex[0].x = (Location.x - XSize / 2) / BLOCK_SIZE + scroll / BLOCK_SIZE;

    //�E��
    //Y���W
    vertex[1].y = (Location.y + YSize / 2) / BLOCK_SIZE;
    //X���W
    vertex[1].x = (Location.x + (XSize / 2 - 1)) / BLOCK_SIZE + scroll / BLOCK_SIZE;

    int start = 0;
    int end = 1;
    for (int h = (int)vertex[start].y; h <= (int)vertex[end].y; h++)
    {
        for (int w = (int)vertex[end].x; w <= (int)vertex[end].x; w++)
        {
            if (stage[h][w] == 0)
            {
                return true;
            }
        }
    }
    return false;
}
