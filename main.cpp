#include "Engine.h"
#include "Triangle.h"

const wchar_t kWindowTitle[] = { L"CG2_サカモトイクミ" };

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ウィンドウプロシージャ
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

		if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
			return true;
		}

		// メッセージに応じてゲーム固有の処理を行う
		switch (msg) {
			// ウィンドウ.lpszClassName,    // クラス名
	    title,                // タイトルバーの名前
	    WS_OVERLAPPEDWINDOW,  // ウィンドウスタイル
	    CW_USEDEFAULT,        // 表示X座標
	    CW_USEDEFAULT,        // 表示Y座標
	    wrc.right - wrc.left, // ウィンドウ横幅
	    wrc.bottom - wrc.top, // ウィンドウ縦幅
	    nullptr,              // 親ウィンドウハンドル
	    nullptr,              // メニューハンドル
	    wc_.hInstance,        // インスタンスハンドル
	    nullptr               // オプション
	);


	// ウィンドウ表示
	ShowWindow(hwnd_, SW_SHOW);








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