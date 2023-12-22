#include "DirectX.h"
#include "WinApi.h"
#include <Windows.h>
#include <cassert>
#include <dxcapi.h>
#pragma comment(lib, "dxcompiler.lib")

const wchar_t kWindowTitle[] = {L"CG2_WinMain"};

// dxcCompilerを初期化
IDxcUtils* dxcUtils = nullptr;
IDxcCompiler3* dxcCompiler = nullptr;
hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));
assert(SUCCEEDED(hr));
hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
assert(SUCCEEDED(hr));

// 現時点でincludeはしないが、includeに対応するための設定を行っておく
IDxcIncludeHandler* includeHandler = nullptr;
hr = dxcUtils->CreateDefaultIncludeHandler(&includeHandler);
assert(SUCCEEDED(hr));

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

#pragma region ウィンドウ

	// WinApi::CreateWindowView(kWindowTitle);
	DirectXCommon::DirectXInitialization();

#pragma endregion

#pragma region

	MSG msg{};

	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		} else {
		}
	}
#pragma endregion

	OutputDebugStringA("Hello,DirectX!\n");

	IDxcBlob* CompileShader(
	    // CompilerするShaderファイルへのパス
	    const std::wstring& filePath,
	    // Compilerに使用するProfile
	    const wchar_t* profile,
	    // 初期化で生成したものを３つ
	    IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler)

	{
		///hlslファイルを読む

		// ここからシェーダーをコンパイルする旨をログに出す
		Log(ConvertString( std::format(L"Begin CompileShader, path:{},profile:{}\n", filePath, profile)));
		//hlslファイルを読む
		IDxcBlobEncoding* shaderSource = nullptr;
		HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
		//読めなかった止める
		assert(SUCCEEDED(hr));
		//読み込んだファイルの内容を設定する
		DxcBuffer shaderSourceBuffer;
		shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
		shaderSourceBuffer.Size = shaderSource->GetBufferSize();
		shaderSourceBuffer.Encoding = DXC_CP_UTF8; //UTF8の文字コードであることを通知
	
	
	///Compileする
		LPCWSTR argument[] = {
		    filePath.c_str(),//コンパイル対象のhlslファイル名
		    L"-E",L"main,"//エントリーポイントの指定。基本的にmain以外はしない
		    L"-T",profile,//ShaderProfileの設定
		    L"-Zi",L"-Qemded_debug",//デバッグ用の情報を埋め込む
		    L"-Od",//最適化を外しておく
		    L"-Zpr",//メモリレイアウトは優先的
		};

		//実際にShaderをコンパイルする
		IDxcResult* shaderResult = nullptr;
		hr = dxcCompiler->Compile(
		    &shaderSourceBuffer, //読み込んだファイル
			arguments,            //コンパイルオプション
			_countof(arguments), //コンパイルオプションの数
			includeHandler,      //includeが含まれた諸々
		    IID_PPV_ARGS(&shaderResult)//コンパイル結果
		);
	
		//コンパイルエラーではなくdxcが起動できないほど致命的な状況
		assert(SUCCEEDED(hr));
	
	
	//警告・エラーが出てたらログに出して止める
		IDxcBlobUtf8* shaderError = nullptr;
		shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
		if (shaderError != nullptr && shaderError->GerStringLength() != 0) {
			log(shaderError->GetStringPointer());
		//警告・エラーダメゼッタイ
			assert(false);
		}
	
	//コンパイル結果から実行用のバイナリ部分を取得

	
	
	
	
	
	
	
	
	
	
	}

	return 0;
}