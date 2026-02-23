#pragma once
#include <d3d12.h>
#include <string>
#include "Mymath.h"
#include <wrl.h>


class SpriteCommon;

class Sprite
{
public:
	Sprite() {};

	~Sprite();

	void Initialize(SpriteCommon* spriteCommon, std::string textureFilePath);

	void UpData();

	void Draw();

	struct VertexData
	{
		Mymath::Vector4 position;
		Mymath::Vector2 texcode;
		Mymath::Vector3 normal;
	};

	struct Material
	{
		Mymath::Vector4 color;
		int32_t enableLighting;
	};

	struct TransformMatrix
	{
		Mymath::Matrix4x4 WVP;
		Mymath::Matrix4x4 World;
	};

	struct Transform {
		Mymath::Vector3 scale;
		Mymath::Vector3 rotate;
		Mymath::Vector3 translate;
	};

	const Mymath::Vector2& GetPosition() const { return position; }
	void SetPosition(const Mymath::Vector2& position) { this->position = position; }

	float GetRotation() const { return rotation; }
	void SetRotation(float rotation) { this->rotation = rotation; }

	const Mymath::Vector4& GetColor() const { return materialData->color; }
	void SetColor(const Mymath::Vector4& color) { materialData->color = color; }

	const Mymath::Vector2& GetSize() const { return scale; }
	void SetSize(const Mymath::Vector2& scale) { this->scale = scale; }

	const Mymath::Vector2& GetAnchorPoint() const { return anchorPoint; }
	void SetAnchorPoint(const Mymath::Vector2& anchorPoint) { this->anchorPoint = anchorPoint; }

	const bool GetFlipX() const { return isFlipX_; }
	void SetFlipX(bool isFlipX) { isFlipX_ = isFlipX; }

	const bool GetFlipY() const { return isFlipY_; }
	void SetFlipY(bool isFlipY) { isFlipX_ = isFlipY; }

	const  Mymath::Vector2& GetTextureLeftTop() const { return textureLeftTop; }
	void SetTextureLeftTop(Mymath::Vector2& textureLeftTop) { this->textureLeftTop = textureLeftTop; }

	const  Mymath::Vector2& GetTextureSize() const { return textureSize; }
	void SetTextureSize(const Mymath::Vector2& textureSize) { this->textureSize = textureSize; }
private:
	void AdjustTextureSize();


	SpriteCommon* spriteCommon;

	Microsoft::WRL::ComPtr < ID3D12Resource> vertexResource;
	Microsoft::WRL::ComPtr <ID3D12Resource> indexResource;

	VertexData* vertexDate = nullptr;
	uint32_t* indexData = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW indexBufferView;

	Microsoft::WRL::ComPtr < ID3D12Resource> transformationMatirxResource;

	TransformMatrix* transformationMatirxData;

	Microsoft::WRL::ComPtr < ID3D12Resource> materialResource;

	Material* materialData;

	Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	Microsoft::WRL::ComPtr < ID3D12Resource> transformationMatirxResourceSprite;
	TransformMatrix* transformationMatirxDataSprite;

	Transform transform;
	Transform cameratransform{ {1.0f,1.0f,1.0f,},{0.0f,0.0f,0.0f},{0.0f,0.0f,-15.0f} };


	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHeapHandleCPU;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHeapHandleGPU;

	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr < ID3D12Resource> directionalLightResource;

	ID3D12GraphicsCommandList* commandList;

	Mymath::Vector2 position = { 0.0f,0.0f };
	float rotation = 0.0f;
	Mymath::Vector2 scale = { 640.0f,360.0f };
	uint32_t textureIndex = 0;


	Mymath::Vector2 anchorPoint = { 0.5f,0.5f };

	bool isFlipX_ = false;
	bool isFlipY_ = false;


	Mymath::Vector2 textureLeftTop = { 0.0f,0.0f };
	Mymath::Vector2 textureSize = { 100.0f,100.0f };

	Mymath::Vector2 size = {};
};

