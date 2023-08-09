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
	void Draw(const float sx)const;
	//�X�e�[�W�f�[�^�ǂݍ���
	int LoadStages();
	int LoadBack();
	//�摜�ǂݍ���
	int LoadImages();

	//�X�e�[�W�̓����蔻��
	bool ChackHitStage(int jState
		, VECTOR location, int x_size, int y_size
		, int move_vector, float scroll);
	//�����ɒn�ʂ����邩�ǂ���
	bool ChackUnder(float scroll
		,VECTOR location, int x_size, int y_size);

	//�u���b�N������
	void MoveBlockPreparation(float scroll);
	void MoveBlock();

	int GetHitSide()const { return (int)Side; }
	int GetHitBlock(int i)const { return HitBlock[i]; }
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

	/*�w�i�̉摜������ϐ�*/
	int BackImages[16];

	HIT_SIDE Side;
	HIT_SIDE SaveSide;
	int HitBlock[2] = { 0,0 };  //���������X�e�[�W�u���b�N�̍��W
	float Push;
	float PushSpeed;
	int sec = 0;
	int down = 2;
	int PushBlock[2] = { 0,0 }; //�����o���u���b�N
};

