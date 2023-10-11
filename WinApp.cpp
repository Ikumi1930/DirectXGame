#include "WinApp.h"
#include "DirectX.h"
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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



void WinApp::CreateWindowView(const wchar_t* title, int32_t clientWidth, int32_t clientheight) {
	//ウィンドウプロシージャ
	wc_.lpfnWndProc = WindowProc;
	//クラス名
	wc_.lpszClassName = L"CG2WindowClass";
	//インスタンスハンドル
	wc_.hInstance = GetModuleHandle(nullptr);
	//カーソル
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウィンドウクラス登録
	RegisterClass(&wc_);

	//ウィンドウサイズの構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	//クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	

#ifdef _DEBUG//デバッグレイヤー
	debugController_ = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController_)))) {
		//デバッグレイヤーを有効化
		debugController_->EnableDebugLayer();
		//GPU側でもチェックを行う
		debugController_->SetEnableGPUBasedValidation(TRUE);
	}
#endif // _DEBUG

	
}

bool WinApp::Procesmessage() {

	MSG msg{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_QUIT) // 終了メッセージが来たらループを抜ける
	{
		return true;
	}
	return false;
}

void WinApp::Finalize()
{
	debugController_->Release();
}


HWND WinApp::hwnd_;
UINT WinApp::windowStyle_;
ID3D12Debug1* WinApp::debugController_;