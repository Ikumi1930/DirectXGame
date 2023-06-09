#pragma once
#include <Windows.h>
#include <string>
#include <format>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <dxgidebug.h>

#include "WinApi.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")

class DirectXCommon
{
public:
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;

	static void Log(const std::string& message);

	static void DirectXInitialization();

	static void InitializeDXGIDevice();

	static void InitializeCommand();

	static void CreateSwapChain();

	static void CreateFinalRenderTargets();

	static void CreateFence();

	static void Release();

	static void ResourceCheck();

private:
	static WinApi* winApi_;

	//DXGIファクトリー
	static IDXGIFactory7* dxgiFactory;
	static HRESULT hr;

	//使用するアダプタ用の変数
	static IDXGIAdapter4* useAdapter;

	//D3D12Device生成
	static ID3D12Device* device;

	//コマンドキューを生成する
	static ID3D12CommandQueue* commandQueue;
	static inline D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	//コマンドアロケータを生成
	static ID3D12CommandAllocator* commandAllocator;

	//コマンドリストの生成
	static ID3D12GraphicsCommandList* commandList;

	//	スワップチェーンを生成
	static IDXGISwapChain4* swapChain;
	static inline DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//ディスクりぷたーぷの生成
	static ID3D12DescriptorHeap* rtvDescriptorHeap;
	static inline D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc{};

	//SwapchainからResourceを引っ張る
	static ID3D12Resource* swapChainResources[2];

   //初期値０でFenceを作る
	static ID3D12Fence* fence;
	static uint64_t  fenceValue;

	//FenceのSignalを持つためにイベントを作成suru
	static HANDLE fenceEvent;

	//デバック
	static ID3D12Debug1* debugController;
	static IDXGIDebug1* debug;
};

