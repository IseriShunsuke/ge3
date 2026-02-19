#pragma once
#include "DirectXCommon.h"

class SpriteCommon;

class Sprite
{
public:
	Sprite() {}

	void Initialize(SpriteCommon* spriteCommon);

	void UpData();

	void Draw();

	struct VertexData
	{
		Vector4 position;
		Vector2 texcode;
		Vector3 normal;
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

	struct Transform {
		Vector3 scale;
		Vector3 rotate;
		Vector3 translate;
	};

	const Vector2& GetPosition() const { return position; }
	void SetPosition(const Vector2& position) { this->position = position; }

	float GetRotation() const { return rotation; }
	void SetRotation(float rotation) { this->rotation = rotation; }

	const Vector4& GetColor() const { return materialData->color; }
	void SetColor(const Vector4& color) { materialData->color = color; }

	const Vector2& GetSize() const { return scale; }
	void SetSize(const Vector2& scale) {this->scale = scale; }
private:
	SpriteCommon* spriteCommon = nullptr;

	ID3D12Resource* vertexResource;
	ID3D12Resource* indexResource;

	VertexData* vertexDate = nullptr;
	uint32_t* indexData = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW indexBufferView;

	ID3D12Resource* transformationMatirxResource;

	TransformMatrix* transformationMatirxData;

	ID3D12Resource* materialResource;

	Material* materialData;

	DirectXCommon* dxcommond_;

	Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	ID3D12Resource* transformationMatirxResourceSprite;
	TransformMatrix* transformationMatirxDataSprite;

	Transform transform;
	Transform cameratransform{ {1.0f,1.0f,1.0f,},{0.0f,0.0f,0.0f},{0.0f,0.0f,-15.0f} };


	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHeapHandleCPU;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHeapHandleGPU;

	ID3D12Device* device;
	ID3D12Resource* directionalLightResource;


	Vector2 position = { 0.0f,0.0f };
	float rotation = 0.0f;
	Vector2 scale = { 640.0f,360.0f };
};

