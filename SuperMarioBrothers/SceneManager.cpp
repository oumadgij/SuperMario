#include "SceneManager.h"

AbstractScene* SceneManager::Update()
{
	//現在シーンのアップデートを実行
	AbstractScene* nextScene = mScene->Update();

	//次のシーンが現在シーンと違う場合切り替える
	if (nextScene != mScene)
	{
		delete mScene;
		mScene = nextScene;
	}

	return mScene;
}

void SceneManager::Draw() const
{
	mScene->Draw();
}
