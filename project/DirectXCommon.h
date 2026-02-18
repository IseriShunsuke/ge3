#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <array>
#include "WinApp.h"
#include <string>
#include <vector>
#include <dxcapi.h>
#include <chrono>
#include"externals/DirectXTex/DirectXTex.h"

struct Vector2
{
	float x;
	float y;
};

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

struct VertexData
{
	Vector4 position;
	Vector2 texcode;
	Vector3 normal;
};

struct Matrix4x4 {
	float m[4][4];
};

struct MaterialData
{
	std::string textureFilePath;
};

struct ModelData
{
	std::vector<VertexData> vertices;
	MaterialData material;
};

struct Material
{
	Vector4 color;
	int32_t enableLighting;
};

struct TransformMatrix
{
	Matrix4x4 WVP;
	Matrix4x4 World;
};

struct DirectionalLight
{
	Vector4 color;
	Vector3 direction;
	float intensity;
};


class DirectXCommon
{
public:


	void Initialize();

	void deviceInitialize();

	void CommandInitialize();

	void swapChainGenerate();

	void DepthBufferGenerate();

	void DescriptorGenerate();

	void RenderTargetViewInitialize();

	void DescriptorStencilView();

	void FenceInitialize();

	void ViewPortInitialize();

	void ScissorRect();

	void DXCompilerCreate();

	void ImGuiInitialize();

	void PreDraw();

	void PostDraw();


	ID3D12Resource* CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);


	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorsize, uint32_t index);
	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorsize, uint32_t index);

	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUDescriptorHandle(uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetRTVGPUDescriptorHandle(uint32_t index);

	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCPUDescriptorHandle(uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetDSVGPUDescriptorHandle(uint32_t index);

	ID3D12Resource* CreateBufferResource(size_t sizeInBytes);

	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

	ModelData LoadFile(const std::string& directorPath, const std::string& filename);

	IDxcBlob* CompileShader(const std::wstring& filePath, const wchar_t* profile);

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metaData);

	void UpLoadTextureData(Microsoft::WRL::ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages);

	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	D3D12_DEPTH_STENCIL_DESC GetDepthStencilDesc() { return depthStencilDesc; }
	ID3D12GraphicsCommandList* GetCommandList() { return commandList.Get(); }
	ID3D12Device* GetDevice() { return device.Get(); }
	WinApp* GetWinApp() { return winApp_; }
private:
	void InitializeFixFPS();
	void UpdataFixFPS();


	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeapDesc;
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;


	ID3D12Resource* depthStencilResource;

	uint32_t descriptorSizeSRV;
	uint32_t descriptorSizeRTV;
	uint32_t descriptorSizeDSV;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	D3D12_VIEWPORT viewPort{};
	D3D12_RECT scissorRect{};

	HANDLE fenceEvent;



	WinApp* winApp_ = nullptr;

	ID3D12Resource* swapChainResource[2];

	Microsoft::WRL::ComPtr < ID3D12GraphicsCommandList> commandList;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];


	D3D12_RESOURCE_BARRIER barrier{};

	ID3D12Fence* fence;

	uint64_t fenceValue = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;

	IDxcUtils* dxcUtils;
	IDxcCompiler3* dxcCompiler;
	IDxcIncludeHandler* includeHandler;

	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	ID3D12Resource* transformationMatirxResourceSprite;
	ID3D12Resource* directionalLightResource;

	std::chrono::steady_clock::time_point reference_;

};

