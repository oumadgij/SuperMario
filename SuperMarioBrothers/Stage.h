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
	void Draw(const int stage[][211],const int back[][211],const float sx)const;
	//�X�e�[�W�f�[�^�ǂݍ���
	int LoadStages(int stage[][211]);
	int LoadBack(int back[][211]);
	//�摜�ǂݍ���
	int LoadImages();
	//�X�e�[�W�̓����蔻��
	bool ChackHitStage(const int stage[][211], int jState
		, VECTOR location, int x_size, int y_size
		, int move_vector, float scroll);
	//�����ɒn�ʂ����邩�ǂ���
	bool ChackUnder(const int stage[][211], float scroll
		,VECTOR location, int x_size, int y_size);

	int GetHitSide()const { return (int)Side; }
	int GetHitBlock(int i)const { return HitBlock[i]; }
private:

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
	int HitBlock[2] = { 0,0 };  //���������X�e�[�W�u���b�N�̍��W
};

