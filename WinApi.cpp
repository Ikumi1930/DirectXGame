#include "WinApi.h"

//ウィンドウプロシージャ
LRESULT CALLBACK WinApi::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//メッセージに応じてゲーム固有の処理を行う
	switch (msg)
	{
	case WM_DESTROY://ウィンドウが破壊された
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	//標準メッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApi::CreateWindowView(const wchar_t* title, int32_t clientWidth, int32_t clientheight) {
	//ウィンドウプロシージャ
	wc_.lpfnWndProc = WindowProc;
	//クラス名
	wc_.lpszClassName = L"CG2WindowClass";
	//インスタンスハンドルH
	wc_.hInstance = GetModuleHandle(nullptr);
	//カーソル
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);
	//ウィンドウクラス登録
	RegisterClass(&wc_);
	//ウィンドウサイズの構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };
	//クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウ生成
	hwnd_ = CreateWindow(
		wc_.lpszClassName,//クラス名
		title,//タイトルバーの名前
		WS_OVERLAPPEDWINDOW,//ウィンドウスタイル
		CW_USEDEFAULT,//表示X座標
		CW_USEDEFAULT,//表示Y座標
		wrc.right - wrc.left,//ウィンドウ横幅
		wrc.bottom - wrc.top,//ウィンドウ縦幅
		nullptr,//親ウィンドウハンドル
		nullptr,//メニューハンドル
		wc_.hInstance,//インスタンスハンドル
		nullptr//オプション
	);

#ifdef _DEBUG//デバッグレイヤー
	debugController_ = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController_)))) {
		//デバッグレイヤーを有効化
		debugController_->EnableDebugLayer();
		//GPU側でもチェックを行う
		debugController_->SetEnableGPUBasedValidation(TRUE);
	}
#endif // _DEBUG

	//ウィンドウ表示
	ShowWindow(hwnd_, SW_SHOW);
   }

bool WinApi::Procesmessage() {
	MSG msg{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT) // 終了メッセージが来たらループを抜ける
	{
		return true;
	}

	return false;
}

void WinApi::Finalize()
{
	debugController_->Release();
}


HWND WinApi::hwnd_;
UINT WinApi::windowStyle_;
ID3D12Debug1* WinApi::debugController_;
