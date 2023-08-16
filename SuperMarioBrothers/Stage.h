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
	void Draw()const;
	//ステージデータ読み込み
	int LoadStages();
	int LoadBack();
	//画像読み込み
	int LoadImages();

	//判定する前準備
	void ChackStagePreparation(VECTOR location,int x_size,int y_size);
	//ステージの当たり判定
	bool ChackHitStage(int move_vector);
	//足元に地面があるかどうか
	bool ChackUnder();

	//ブロックが動く
	void MoveBlockPreparation();
	void MoveBlock();

	//スクロール分増加させる
	void AddScrollX(int s) { ScrollX += s; }

	int GetHitSide()const { return (int)Side; }
	int GetHitBlock(int i)const { return HitBlock[i]; }

	//to do
	int GetScroll()const { return ScrollX; }
	//消す
private:
	int StageData[15][211];    //ステージデータを入れる変数
	int BackData[15][211]; //背景データを入れる変数

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
	HIT_SIDE SaveSide;
	int HitBlock[2] = { 0,0 };  //当たったステージブロックの座標
	float Push;
	float PushSpeed;
	int sec = 0;
	int down = 2;
	int PushBlock[2] = { -1,-1 }; //押し出すブロック
	int ScrollX = 0;  //横スクロール

	//判定する自身の範囲
	int vertex[2][2] = { {0,0},{0,0} };
	//to do
	int play[2];
	int ChackStage[15][20];
	//消す
};

