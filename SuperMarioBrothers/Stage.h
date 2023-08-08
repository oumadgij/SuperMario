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
	//描画
	void Draw(const int stage[][211],const int back[][211],const float sx)const;
	//ステージデータ読み込み
	int LoadStages(int stage[][211]);
	int LoadBack(int back[][211]);
	//画像読み込み
	int LoadImages();
	//ステージの当たり判定
	bool ChackHitStage(const int stage[][211], int jState
		, VECTOR location, int x_size, int y_size
		, int move_vector, float scroll);
	//足元に地面があるかどうか
	bool ChackUnder(const int stage[][211], float scroll
		,VECTOR location, int x_size, int y_size);

	int GetHitSide()const { return (int)Side; }
	int GetHitBlock(int i)const { return HitBlock[i]; }
private:

	/*ブロックの画像を入れる変数*/
	int Floor;            //フロアブロック
	int Block;            //通常のブロック
	int EmptyBlock;       //空のブロック
	int StairsBlock;      //階段ブロック
	int DebrisBlock;      //ブロックの破片
	int QuestionBlock[4]; //ハテナブロック
	int b_Block;          //ブラックブロック
	int b_Floor;          //地下のフロアブロック
	int Pipe[4];          //土管

	/*背景の画像を入れる変数*/
	int BackImages[16];

	HIT_SIDE Side;
	int HitBlock[2] = { 0,0 };  //当たったステージブロックの座標
};

