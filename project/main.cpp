#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")


#include "externals/DirectXTex/d3dx12.h"




#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"

#include"externals/DirectXTex/DirectXTex.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


#include <fstream>
#include <sstream>
#include <wrl.h>


#include "Input.h"
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include "WinApp.h"
#include "DirectXCommon.h"
#include "Logger.h"
#include "StringUtility.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "TextureManager.h"

using namespace Mymath;


struct D3DResourceLeakChecker
{
	~D3DResourceLeakChecker()
	{
		Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug))))
		{
			debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		}
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	D3DResourceLeakChecker leakCheck;
	WinApp* winApp = new WinApp();
	winApp->Initialize();
	assert(winApp);

	DirectXCommon* dxcommond = nullptr;
	dxcommond = new DirectXCommon();
	dxcommond->Initialize(winApp);




	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxcommond);

	TextureManager::GetInstance()->Initialize(dxcommond);
	std::string filePath = "resources/uvChecker.png";
	TextureManager::GetInstance()->LoadTexture(filePath);


	MSG msg{};

	ID3D12Device*  device = dxcommond->GetDevice();



	Input* input = nullptr;
	input = new Input();
	input->Initialize(dxcommond->GetWinApp());

	std::vector<Sprite*> sprites;
	for (uint32_t i = 0; i < 5; ++i)
	{
		Sprite* sprite = new Sprite();
		
		if (i > 1)
		{
			std::string filePath = "resources/monsterBall.png";
			TextureManager::GetInstance()->LoadTexture(filePath);
			sprite->Initialize(spriteCommon, "resources/monsterBall.png");
		}
		else
		{
			sprite->Initialize(spriteCommon, "resources/uvChecker.png");
		}
		sprites.push_back(sprite);
	}
	ID3D12GraphicsCommandList* commandList = dxcommond->GetCommandList();

	while (true)
	{
		if (winApp->ProcessMessage())
		{
			break;
		}

		else
		{
			input->UpDate();


			/*sprite->UpData();*/


			ImGui_ImplDX12_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			ImGui::End();

			

			ImGui::ShowDemoWindow();

			ImGui::Render();

			for (uint32_t i = 0; i < 5; ++i)
			{
				bool flipY = sprites[i]->GetFlipY();
				if (!flipY)
				{
					flipY = true;
				}
				sprites[i]->SetFlipY(flipY);
				Vector2 position = sprites[i]->GetPosition();
				position.x = 0.1f + i * 100.0f; position.y += 0.1f;

				sprites[i]->SetPosition(position);

				float rotation = sprites[i]->GetRotation();

				rotation = 0.51f;
				sprites[i]->SetRotation(rotation);

				Vector4 color = sprites[i]->GetColor();
				color.x += 0.01f;

				if (color.x > 1.0f)
				{
					color.x -= 1.0f;
				}
				sprites[i]->SetColor(color);

				Vector2 scale = sprites[i]->GetSize();
				scale.x += 0.1f; scale.y += 0.1f;

				sprites[i]->SetSize({64.0f, 64.0f});
				sprites[i]->SetTextureSize({64.0f, 64.0f});

				sprites[i]->UpData();

			}

			if (input->TriggerKey(DIK_D))
			{
				OutputDebugStringA("Hit 0\n");
			}
		}



		dxcommond->PreDraw();

		spriteCommon->CommonRenderingSettings();

		for (uint32_t i = 0; i < 5; ++i)
		{
			sprites[i]->Draw();
		}

		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);
		dxcommond->PostDraw();
	}


	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	
	device->Release();

	delete input;
	delete spriteCommon;
	for (uint32_t i = 0; i < 5; ++i)
	{
		delete sprites[i];
	}

	TextureManager::GetInstance()->Finalize();

	winApp->Finalize();


	delete winApp;
	return 0;
}