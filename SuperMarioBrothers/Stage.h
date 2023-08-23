#pragma once
enum class HIT_SIDE
{
	DEFAULT = 0,
	LEFT,
	RIGHT,
	TOP,
	UNDER
};

class Stage
{
public:
	Stage();
	~Stage() {};
	//�`��
	void Draw()const;
	//�X�e�[�W�f�[�^�ǂݍ���
	int LoadStages();
	int LoadBack();
	//�摜�ǂݍ���
	int LoadImages();

	//���肷��O����
	//�v���C���[�E�G�p
	void ChackStagePreparation(VECTOR location,int x_size,int y_size); //correction�F�␳�l
	//���肷��O����
	//�A�C�e���p
	void ItemChackStagePreparation(VECTOR location, int x_size, int y_size);
	//�X�e�[�W�̓����蔻��
	bool ChackHitStage(int move_vector);
	//�����ɒn�ʂ����邩�ǂ���
	bool ChackUnder();

	//�u���b�N������
	void MoveBlockPreparation();
	void MoveBlock();

	//�X�N���[��������������
	void AddScrollX(int s) { ScrollX += s; }

	int GetHitSide()const { return (int)Side; }
	int GetHitBlock(int i)const { return HitBlock[i]; }
	int GetPushBlock(int i)const {return PushBlock[i]; }
	int GetStage(int h, int w)const { return ChackStage[h][w]; }
	int GetScroll()const { return ScrollX; }

	//to do
	bool GetPushEnd()const { return PushEnd; }
	//����
private:
	int StageData[15][211];    //�X�e�[�W�f�[�^������ϐ�
	int BackData[15][211]; //�w�i�f�[�^������ϐ�

	/*�u���b�N�̉摜������ϐ�*/
	int Floor;            //�t���A�u���b�N
	int Block;            //�ʏ�̃u���b�N
	int EmptyBlock;       //��̃u���b�N
	int StairsBlock;      //�K�i�u���b�N
	int DebrisBlock;      //�u���b�N�̔j��
	int QuestionBlock[4]; //�n�e�i�u���b�N
	int b_Block;          //�u���b�N�u���b�N
	int b_Floor;          //�n���̃t���A�u���b�N
	int Pipe[4];          //�y��
	int Pole;			  //�|�[��
	int Pole_Top;		  //�|�[���̐�[
	int Pole_Flg;		  //�|�[���̊�
	int Castle;			  //��
	int Flag;			  //��

	/*�w�i�̉摜������ϐ�*/
	int BackImages[16];

	HIT_SIDE Side;
	HIT_SIDE SaveSide;
	int HitBlock[2] = { 0,0 };  //���������X�e�[�W�u���b�N�̍��W 0�F�c 1�F��
	float Push;
	float PushSpeed;
	int sec = 0;
	int down = 2;
	int PushBlock[2] = { -1,-1 }; //�����o���u���b�N 0�F�c 1�F��
	int ScrollX = 0;  //���X�N���[��

	//���肷�鎩�g�͈̔�
	int vertex[2][2] = { {0,0},{0,0} };
	//to do
	int play[2];
	int ChackStage[15][20];
	bool PushEnd = false;  //�����o�����I�������  false �F�I����Ă��Ȃ� true�F�I����Ă���
	//����
};

