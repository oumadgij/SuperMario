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

    /*���g��4���_�����߂�*/
    //VECTOR vertex[4];
    ////����
    //vertex[0] = { Location.x,Location.y };
    ////����
    //vertex[1] = { Location.x,Location.y + YSize };
    ////�E��
    //vertex[2] = { Location.x + XSize,Location.y };
    ////�E��
    //vertex[3] = { Location.x + XSize,Location.y + YSize };

    //for (int i = 0; i < 4; i++)
    //{
    //    int h = static_cast<int>(vertex[i].x / 32);
    //    int w = static_cast<int>(vertex[i].y / 32);
    //    if (stage[h][w] != 0)
    //    {
    //        /*HitVectors[0] = h;
    //        HitVectors[1] = w;*/

    //        return true;
    //    }
    //}

    return false;
}

void BoxCollider::HitStage()
{
    VECTOR vec;

    vec.y = static_cast<float>(HitBlock[0] * BLOCK_SIZE);
    vec.x = static_cast<float>(HitBlock[1] * BLOCK_SIZE);

    switch (side) //���������u���b�N�̕ӂ̈ʒu
    {
    case HIT_SIDE::LEFT:
        Location.x = vec.x - BLOCK_SIZE;
            break;
    case HIT_SIDE::RIGHT:
        Location.x = vec.x + BLOCK_SIZE;
        break;
    case HIT_SIDE::TOP:
        Location.y = vec.y - YSize;
        break;
    case HIT_SIDE::UNDER:
        Location.y = vec.y + BLOCK_SIZE;
        break;
    }

    //if (stagex != 0)
    //{
    //    switch (move)  //���������ɐi��ł�����
    //    {
    //    case MOVE_VECTOR::LEFT:  //��
    //        //X= (stagex+1) * 32;
    //        Location.x = static_cast<float>((stagex + 1) * 32);
    //        break;
    //    case MOVE_VECTOR::RIGHT:  //�E
    //        //X = (stagex-1) * 32 + 32;
    //        Location.x = static_cast<float>((stagex - 1) * 32 + 32);
    //        break;
    //    }

    //    /*Location.x = X;*/
    //}
    //float Y = 0.f;
    //if (stagey != 0)
    //{
    //    switch (move)
    //    {
    //    case MOVE_VECTOR::JUMP:
    //        //Y = (stagey+1) * 32 + 32;
    //        Location.y = static_cast<float>((stagey + 1) * 32 + 32);
    //        break;
    //    case MOVE_VECTOR::DOWN:
    //        //Y = (stagey - 1) * 32 + BIGMARIO_HEIGTH;
    //        Location.y = static_cast<float>((stagey - 1) * 32 + BIGMARIO_HEIGTH_SIZE);
    //        break;
    //    }

    //    //Location.y = Y;
    //}
}