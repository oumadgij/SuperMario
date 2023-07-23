#include "BoxCollider.h"
#include "Define.h"

//�����蔻����Ƃ�(false�F�������Ă��Ȃ� true�F�������Ă���)
bool BoxCollider::ChackHitStage(int stage[][20], int move_vector)
{
    /*
    * ���g�̔��肷��͈͂����߂�
    *  ���͈͂͋�`�̊J�n���W���܂ނ���
    *    �I���ʒu�����߂�Ƃ��́A�T�C�Y��-1���Ă��狁�߂�
    */
    VECTOR vertex[2];
    //�J�n�ʒu(����)
     //X���W
    vertex[0].x = Location.x / BLOCK_SIZE;
     //Y���W
    vertex[0].y = Location.y / BLOCK_SIZE;

    //�I���ʒu(�E��)
     //X���W
    vertex[1].x = ((Location.x + (XSize - 1)) / BLOCK_SIZE);
     //Y���W
    vertex[1].y = (Location.y + (YSize - 1)) / BLOCK_SIZE;

    /*���g���X�e�[�W�͈̔͂𒴂��Ă��Ȃ����`�F�b�N*/
    for (int i = 0; i < 2; i++)
    {
        //X���W���`�F�b�N
        if (vertex[i].x < 0) //0��菬������
        {
            vertex[i].x = 0;
        }
        else if (STAGE_WIDTH_BLOCK < vertex[i].x) //�X�e�[�W���傫����
        {
            vertex[i].x = STAGE_WIDTH_BLOCK - 1;
        }
        //Y���W���`�F�b�N
        if (vertex[i].y < 0) //0��菬������
        {
            vertex[i].y = 0;
        }
        else if (STAGE_HEIGHT_BLOCK < vertex[i].y) //�X�e�[�W���傫����
        {
            vertex[i].y = STAGE_HEIGHT_BLOCK - 1;
        }
    }

    /*���肷��ӂ�����o��*/

    int start = 0;
    int end = 1;
    /*���肷��͈͂Ƀu���b�N���Ȃ����`�F�b�N*/
    for (int h = static_cast<int>(vertex[start].y); h <= vertex[end].y; h++)
    {
        for (int w = static_cast<int>(vertex[start].x); w <= vertex[end].x; w++)
        {
            if (stage[h][w] != 0)
            {
                switch (move_vector)
                {
                case 1:
                    side = HIT_SIDE::RIGHT;
                    break;
                case 2:
                    side = HIT_SIDE::LEFT;
                    break;
                case 3:
                    side = HIT_SIDE::UNDER;
                    break;
                case 4:
                    side = HIT_SIDE::TOP;
                    break;
                }

                HitBlock[0] = h;
                HitBlock[1] = w;

                return true;  //�u���b�N�ɓ������Ă���
            }
        }
    }

    return false;
}