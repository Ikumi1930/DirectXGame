#include "TitleScene.h"

void TitleScene::Initialize(MyEngine* engine, DirectXCommon* dxCommon) {
	dxCommon_ = dxCommon;
	engine_ = engine;
	input_ = Input::GetInstance();
	input_->Initialize();

	rotation = MakeRotateAxisAngleQuaternion(Normalise(Vector3{1.0f, 0.4f, -0.2f}), 0.45f);
	Vector3 pointY = {2.1f, -0.9f, 1.3f};
	rotateMatrix = MakeRotateMatrix(rotation);
	rotateByQuaternion = RotateVector(pointY, rotation);
	rotateByMatrix = VectorTransform(pointY, rotateMatrix);
}

void TitleScene::Update() {
	input_->Update();

	ImGui::Text("PRESS SPACE");

	if (input_->TriggerKey(DIK_SPACE)) {
		sceneNo = PLAY;
	}
}

void TitleScene::Draw() {}

void TitleScene::Finalize() {}