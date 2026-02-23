#include "TextureManager.h"
#include "DireCtXCommon.h"
#include "StringUtility.h"


uint32_t TextureManager::kSRVIndexTop = 1;

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureManager;
	}
	return instance;
}

void TextureManager::Finalize()
{
	delete instance;
	instance = nullptr;
}


void TextureManager::Initialize(DirectXCommon* dxcommon)
{
	TextureDatas.reserve(DirectXCommon::kMaxSRVCount);
	dxcommon_ = dxcommon;
	device_ = dxcommon_->GetDevice();
	
}

void TextureManager::LoadTexture(std::string& filePath)
{
	auto it = std::find_if(TextureDatas.begin(), TextureDatas.end(), [&](TextureData& textureData) { return textureData.filePath == filePath; });

	if (it != TextureDatas.end())
	{
		return;
	}

	assert(TextureDatas.size() + kSRVIndexTop < DirectXCommon::kMaxSRVCount);

	DirectX::ScratchImage image{};

	std::wstring filePathW = StringUtility::ConvertString(filePath);

	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));


	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	TextureDatas.resize(TextureDatas.size() + 1);

	TextureData& textureData = TextureDatas.back();

	textureData.filePath = filePath;
	textureData.metadata = mipImages.GetMetadata();
	textureData.resource = dxcommon_->CreateTextureResource(textureData.metadata);

	uint32_t srvIndex = static_cast<uint32_t>(TextureDatas.size() - 1) + kSRVIndexTop;

	textureData.srvHandleCPU = dxcommon_->GetSRVCPUDescriptorHandle(srvIndex);
	textureData.srvHandleGPU = dxcommon_->GetSRVGPUDescriptorHandle(srvIndex);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = textureData.metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(textureData.metadata.mipLevels);

	device_->CreateShaderResourceView(textureData.resource.Get(), &srvDesc, textureData.srvHandleCPU);

	dxcommon_->UpLoadTextureData(textureData.resource.Get(), mipImages);
}

uint32_t TextureManager::GetTextureIndexByFilePath(const std::string& filePath)
{
	auto it = std::find_if(TextureDatas.begin(), TextureDatas.end(), [&](TextureData& textureData) { return textureData.filePath == filePath; });
	if (it != TextureDatas.end())
	{
		uint32_t textureIndex = static_cast<uint32_t>(std::distance(TextureDatas.begin(), it));
		return textureIndex;
	}

	assert(0);
	return 0;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetSRVHandleGPU(uint32_t textureIndex)
{
	assert(textureIndex < DirectXCommon::kMaxSRVCount);
		TextureData& textureData = TextureDatas[textureIndex];
		return textureData.srvHandleGPU;
}

DirectX::TexMetadata& TextureManager::GetMetadata(uint32_t textureIndex)
{
	assert(textureIndex < DirectXCommon::kMaxSRVCount);
	TextureData&  textureData = TextureDatas[textureIndex];
	return textureData.metadata;
}