#include <Windows.h>
#include <cstdint>
#include "WinAPI.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinAPI* winapi = new WinAPI;
	winapi->Initialize();

	//これがゲームループ↓
	MSG msg{};

	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			
		}

	}

	OutputDebugStringA("Hello,DirectX!\n");

	return 0;
}
