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
private:
	ID3D12Device* device;

	HRESULT hr;

	ID3D12RootSignature* rootSignature;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	ID3D12PipelineState* graphicsPipelineState;

	DirectXCommon* dxcommond_;

	ID3DBlob* signatureBlob;
	ID3DBlob* errorBlob;
};

