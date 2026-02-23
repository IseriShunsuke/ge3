#pragma once
#include "DireCtXCommon.h"
#include <string>
#include"externals/DirectXTex/DirectXTex.h"
#include <wrl.h>
#include <d3d12.h>


class TextureManager
{
public:
	void Initialize(DirectXCommon* dxcommon);

	static TextureManager* GetInstance();

	void Finalize();

	void LoadTexture(std::string& filePath);

	uint32_t GetTextureIndexByFilePath(const std::string& filePath);

	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVHandleGPU(uint32_t textureIndex);

	DirectX::TexMetadata& GetMetadata(uint32_t textureIndex);
private:
	static TextureManager* instance;
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(TextureManager&) = delete;

	TextureManager& operator=(TextureManager&) = delete;

	struct TextureData
	{
		std::string filePath;
		DirectX::TexMetadata metadata;
		Microsoft::WRL::ComPtr<ID3D12Resource> resource;
		D3D12_CPU_DESCRIPTOR_HANDLE srvHandleCPU;
		D3D12_GPU_DESCRIPTOR_HANDLE srvHandleGPU;
	};
		 
	std::vector<TextureData> TextureDatas;

	DirectXCommon* dxcommon_;
	Microsoft::WRL::ComPtr <ID3D12Device> device_;

	static uint32_t kSRVIndexTop;
};

