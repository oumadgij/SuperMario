#include "BoxCollider.h"
#include "Define.h"

//�����蔻����Ƃ�(false�F�������Ă��Ȃ� true�F�������Ă���)
bool BoxCollider::ChackHitStage(int stage[][20])
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
            vertex[i].x = STAGE_WIDTH_BLOCK;
        }
        //Y���W���`�F�b�N
        if (vertex[i].y < 0) //0��菬������
        {
            vertex[i].y = 0;
        }
        else if (STAGE_HEIGHT_BLOCK < vertex[i].y) //�X�e�[�W���傫����
        {
            vertex[i].y = STAGE_HEIGHT_BLOCK;
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

//bool BoxCollider::ChackHitStage(float StageX, float StageY, int XSize, int YSize, int move_vector)
//{
//    //���g�̉E���Ɖ����̍��W�����߂�
//    VECTOR Locetion2;
//    Locetion2.x = Location.x + this->XSize;
//    Locetion2.y = Location.y + this->YSize;
//
//    //�X�e�[�W�u���b�N�̉E���Ɖ����̍��W�����߂�
//    int StageX2 = StageX + XSize;
//    int StageY2 = StageY + YSize;
//
//    switch (move_vector)
//    {
//    case 1:
//        //���g�̍������X�e�[�W�u���b�N�̉E�������傫��
//        if (StageX2 < Location.x)
//        {
//            return false;
//        }
//        break;
//    case 2:
//        //���g�̉E�����X�e�[�W�u���b�N�̍�������������
//        if (Locetion2.x < StageX)
//        {
//            return false;
//        }
//        break;
//    case 3:
//        //���g�̏㑤���X�e�[�W�u���b�N�̉��������傫��
//        if (StageY2 < Location.y)
//        {
//            return false;
//        }
//        break;
//    case 4:
//        //���g�̉������X�e�[�W�u���b�N�̏㑤����������
//        if (Locetion2.y < StageY)
//        {
//            return false;
//        }
//        break;
//    }
//
//    ///*���S���W�����߂�*/
//    ////���g
//    //VECTOR Center;
//    //Center.x = this->Location.x + (this->XSize / 2);
//    //Center.y = this->Location.y + (this->YSize / 2);
//    ////�Ώ�
//    //VECTOR OCenter;
//    //OCenter.x = Location.x + XSize / 2;
//    //OCenter.y = Location.y + YSize / 2;
//
//    ///*X���W�Ԃ�Y���W�Ԃ̋����𑪂�*/
//    //VECTOR Distance;
//    //Distance.x = fabsf(Center.x - OCenter.x);
//    //Distance.y = fabsf(Center.y - OCenter.y);
//
//    ///*X����Y���̃T�C�Y�̘a���Ƃ�*/
//    //int XSize_Sum = (this->XSize + XSize) / 2;
//    //int YSize_Sum = (this->YSize + YSize) / 2;
//
//    ///*��r*/
//    //if ((Distance.x <= XSize_Sum) && (Distance.y <= YSize_Sum))
//    //{
//    //    return true;
//    //}
//
//    return true;
//}