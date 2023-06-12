#pragma once
#include <chrono>
#include <cstdlib>
#include <dxgi1_6.h>
#include "WinApi.h"
#include "String.h"

class DirectXCommon
{
public:
	
	 void Initialization(WinApi* win, const wchar_t* title, int32_t backBufferWidth = WinApi::kClientWidth, int32_t backBufferHeight = WinApi::kClientHeight);

	 void PreDraw();

	void PostDraw();

	static inline void CreateRenderTarget();

	static void Finalize();

	HRESULT GetHr() { return  hr_; }

	void SetHr(HRESULT a) { this->hr_ = a; }

	ID3D12Device* GetDevice() { return device_; }

	ID3D12GraphicsCommandList* GetCommandList() { return commandList_; }


private:
	static WinApi* winApi_;

	//DXGIファクトリー
	static IDXGIFactory7* dxgiFactory_;

	//使用するアダプタ用の変数
	static IDXGIAdapter4* useAdapter_;

	//D3D12Device生成
	static ID3D12Device* device_;

	//コマンドキューを生成する
	static ID3D12CommandQueue* commandQueue_;
	
	//コマンドアロケータを生成
	static ID3D12CommandAllocator* commandAllocator_;

	//コマンドリストの生成
	static ID3D12GraphicsCommandList* commandList_;

	//	スワップチェーンを生成
	static IDXGISwapChain4* swapChain_;
	
	//ディスクりぷたーぷの生成
	static ID3D12DescriptorHeap* rtvDescriptorHeap_;
	
	//SwapchainからResourceを引っ張る
	static	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2];
	static ID3D12Resource* swapChainResources_[2];

	//FenceのSignalを持つためにイベントを作成suru
	static ID3D12Fence* fence_;
	static UINT64 fenceValue_;
	static HANDLE fenceEvent_;

	//buffer
	static	int32_t backBufferWidth_;
	static	int32_t backBufferHeight_;

	//barrier
	static	inline D3D12_RESOURCE_BARRIER barrier_{};

	//hr
	static HRESULT hr_;

private:
	void InitializeDXGIDevice();

	void CreateSwapChain();

	void InitializeCommand();

	void CreateFinalRenderTargets();

	void CreateFence();
};

