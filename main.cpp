#include "Engine.h"
#include "Triangle.h"

const wchar_t kWindowTitle[] = { L"CG2_サカモトイクミ" };

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//初期化
	WinApp* win_ = nullptr;
	CreateEngine* Engine = new CreateEngine;
	Engine->Initialization(win_, kWindowTitle, 1280, 720);

	Engine->VariableInialize();

#pragma region ゲームループ

	MSG msg{};

	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else {

			//ゲームの処理
			Engine->BeginFrame();

			ImGui_ImplDX12_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();
			Engine->Update();

			Engine->Draw();

			ImGui::Render();

			Engine->EndFrame();

		}
	}

#pragma endregion

	OutputDebugStringA("Hello,DirectX!\n");

	Engine->Finalize();
	return 0;
}