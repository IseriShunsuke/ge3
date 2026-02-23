#pragma once
#include "DirectXCommon.h"

class SpriteCommon
{
public:
	void Initialize(DirectXCommon* dxcommond);

	void rootSignatureCreate();

	void GraphicsPipelineCreate();

	void CommonRenderingSettings();

	DirectXCommon* GetDxCommon() const { return dxcommond_; }

	~SpriteCommon();
private:
	Microsoft::WRL::ComPtr < ID3D12Device> device;

	HRESULT hr;

	Microsoft::WRL::ComPtr < ID3D12RootSignature> rootSignature;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	Microsoft::WRL::ComPtr < ID3D12PipelineState> graphicsPipelineState;

	DirectXCommon* dxcommond_;

	Microsoft::WRL::ComPtr <ID3DBlob> signatureBlob;
	Microsoft::WRL::ComPtr <ID3DBlob> errorBlob;
	Microsoft::WRL::ComPtr <IDxcBlob> vertexShaderBlob;
	Microsoft::WRL::ComPtr <IDxcBlob> pixelShaderBlob;
};

