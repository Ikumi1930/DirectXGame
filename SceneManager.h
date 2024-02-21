#pragma once
#include "ClearScene.h"
#include "GameScene.h"
#include "OverScene.h"
#include "Scene.h"
#include "TitleScene.h"
#include <memory>

class SceneManager {
private:
	// シーンを保持するメンバ変数
	std::unique_ptr<Scene> sceneArr_[4];

	// 度のステージを呼び出すかを管理する変数
	int currentSceneNo_;
	int prevSceneNo_;

	MyEngine* engine_;
	DirectXCommon* dxCommon_;
	Scene* baseScene;

public:
	SceneManager(MyEngine* engine, DirectXCommon* dxCommon);
	~SceneManager();

	int Run();
};
