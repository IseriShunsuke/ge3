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





//
//struct Transform {
//	Vector3 scale;
//	Vector3 rotate;
//	Vector3 translate;
//};
//
//
//
//
//float dot(const Vector3& v1, const Vector3& v2)
//{
//	return v1.x * v2.x + v1.y * v2.y + v1.z + v2.z;
//}
//
//float Length(const Vector3& v)
//{
//	return std::sqrt(dot(v, v));
//}
//
//Vector3 Normalize(const Vector3& v)
//{
//	float length = Length(v);
//	if (length == 0)
//	{
//		return v;
//	}
//	return { v.x / length,v.y / length,v.z / length };
//}
//
//
//// 単位行列
//Matrix4x4 MakeIdentity4x4() {
//	Matrix4x4 identity;
//	identity.m[0][0] = 1.0f;	identity.m[0][1] = 0.0f;	identity.m[0][2] = 0.0f;	identity.m[0][3] = 0.0f;
//	identity.m[1][0] = 0.0f;	identity.m[1][1] = 1.0f;	identity.m[1][2] = 0.0f;	identity.m[1][3] = 0.0f;
//	identity.m[2][0] = 0.0f;	identity.m[2][1] = 0.0f;	identity.m[2][2] = 1.0f;	identity.m[2][3] = 0.0f;
//	identity.m[3][0] = 0.0f;	identity.m[3][1] = 0.0f;	identity.m[3][2] = 0.0f;	identity.m[3][3] = 1.0f;
//	return identity;
//}
//
//// 4x4の掛け算
//Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
//	Matrix4x4 result;
//	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
//	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
//	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
//	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
//
//	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
//	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
//	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
//	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
//
//	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
//	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
//	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
//	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
//
//	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
//	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
//	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
//	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
//
//	return result;
//}
//
//// X軸で回転
//Matrix4x4 MakeRotateXMatrix(float radian) {
//	float cosTheta = std::cos(radian);
//	float sinTheta = std::sin(radian);
//	return { 1.0f, 0.0f, 0.0f, 0.0f,
//			0.0f, cosTheta, sinTheta, 0.0f,
//			0.0f, -sinTheta, cosTheta, 0.0f,
//			0.0f, 0.0f, 0.0f, 1.0f };
//}
//
//// Y軸で回転
//Matrix4x4 MakeRotateYMatrix(float radian) {
//	float cosTheta = std::cos(radian);
//	float sinTheta = std::sin(radian);
//	return { cosTheta, 0.0f, -sinTheta, 0.0f,
//			0.0f, 1.0f, 0.0f, 0.0f,
//			sinTheta, 0.0f, cosTheta, 0.0f,
//			0.0f, 0.0f, 0.0f, 1.0f };
//}
//
//// Z軸で回転
//Matrix4x4 MakeRotateZMatrix(float radian) {
//	float cosTheta = std::cos(radian);
//	float sinTheta = std::sin(radian);
//	return { cosTheta, sinTheta, 0.0f, 0.0f,
//			-sinTheta, cosTheta, 0.0f , 0.0f,
//			0.0f, 0.0f, 1.0f, 0.0f,
//			0.0f, 0.0f, 0.0f, 1.0f };
//}
//
//// Affine変換
//Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
//	Matrix4x4 result = Multiply(Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)), MakeRotateZMatrix(rotate.z));
//	result.m[0][0] *= scale.x;
//	result.m[0][1] *= scale.x;
//	result.m[0][2] *= scale.x;
//
//	result.m[1][0] *= scale.y;
//	result.m[1][1] *= scale.y;
//	result.m[1][2] *= scale.y;
//
//	result.m[2][0] *= scale.z;
//	result.m[2][1] *= scale.z;
//	result.m[2][2] *= scale.z;
//
//	result.m[3][0] = translate.x;
//	result.m[3][1] = translate.y;
//	result.m[3][2] = translate.z;
//	return result;
//}
//
//
//Matrix4x4 Inverse(const Matrix4x4& m) {
//	float determinant = +m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
//		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
//		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
//
//		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
//		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
//		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
//
//		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
//		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
//		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
//
//		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
//		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
//		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
//
//		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
//		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
//		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
//
//		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
//		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
//		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
//
//		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
//		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
//		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
//
//		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
//		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
//		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
//
//	Matrix4x4 result;
//	float recpDeterminant = 1.0f / determinant;
//	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
//		m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
//		m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
//	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
//		m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
//		m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
//	result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
//		m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
//		m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) * recpDeterminant;
//	result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
//		m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
//		m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) * recpDeterminant;
//
//	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
//		m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
//		m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
//	result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
//		m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
//		m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) * recpDeterminant;
//	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
//		m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
//		m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) * recpDeterminant;
//	result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
//		m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
//		m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) * recpDeterminant;
//
//	result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
//		m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
//		m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) * recpDeterminant;
//	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
//		m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
//		m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) * recpDeterminant;
//	result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
//		m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
//		m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) * recpDeterminant;
//	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
//		m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
//		m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) * recpDeterminant;
//
//	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
//		m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
//		m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) * recpDeterminant;
//	result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
//		m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
//		m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) * recpDeterminant;
//	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
//		m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
//		m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) * recpDeterminant;
//	result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
//		m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
//		m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) * recpDeterminant;
//
//	return result;
//}
//
//
//
//
//
//
//
//ID3D12DescriptorHeap* CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible)
//{
//	ID3D12DescriptorHeap* descriptorHeap = nullptr;
//	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
//	descriptorHeapDesc.Type = heapType;
//	descriptorHeapDesc.NumDescriptors = numDescriptors;
//	descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
//	HRESULT hr = device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
//
//	assert(SUCCEEDED(hr));
//	return descriptorHeap;
//}
//
//
//
//
//
//
//Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRotation, float nearClip, float farClip)
//{
//	Matrix4x4 result;
//	result.m[0][0] = (1 / aspectRotation) * (1 / std::tan(fovY / 2));
//	result.m[0][1] = 0;
//	result.m[0][2] = 0;
//	result.m[0][3] = 0;
//	result.m[1][0] = 0;
//	result.m[1][1] = 1 / std::tan(fovY / 2);
//	result.m[1][2] = 0;
//	result.m[1][3] = 0;
//	result.m[2][0] = 0;
//	result.m[2][1] = 0;
//	result.m[2][2] = farClip / (farClip - nearClip);
//	result.m[2][3] = 1;
//	result.m[3][0] = 0;
//	result.m[3][1] = 0;
//	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
//	result.m[3][3] = 0;
//
//	return result;
//
//}
//
//Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
//{
//	Matrix4x4 result;
//	result.m[0][0] = 2 / (right - left);
//	result.m[0][1] = 0;
//	result.m[0][2] = 0;
//	result.m[0][3] = 0;
//	result.m[1][0] = 0;
//	result.m[1][1] = 2 / (top - bottom);
//	result.m[1][2] = 0;
//	result.m[1][3] = 0;
//	result.m[2][0] = 0;
//	result.m[2][1] = 0;
//	result.m[2][2] = 1 / (farClip - nearClip);
//	result.m[2][3] = 0;
//	result.m[3][0] = (left + right) / (left - right);
//	result.m[3][1] = (top + bottom) / (bottom - top);
//	result.m[3][2] = nearClip / (nearClip - farClip);
//	result.m[3][3] = 1;
//
//	return result;
//}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	DirectXCommon* dxcommond = nullptr;
	dxcommond = new DirectXCommon();
	dxcommond->Initialize();



	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxcommond);


	MSG msg{};

	/*ID3D12Resource* vertexResource = CreateBufferResource(device, sizeof(VertexData) * 6);

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();

	vertexBufferView.SizeInBytes = sizeof(VertexData) * 6;

	vertexBufferView.StrideInBytes = sizeof(VertexData);


	VertexData* vertexDate = nullptr;


	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexDate));

	vertexDate[0].position = { -0.5f,-0.5f,0.0f,1.0f };
	vertexDate[0].texcode = { 0.0f,1.0f };

	vertexDate[1].position = { 0.0f,0.5f,0.0f,1.0f };
	vertexDate[1].texcode = { 0.5f,0.0f };

	vertexDate[2].position = { 0.5f,-0.5f,0.0f,1.0f };
	vertexDate[2].texcode = { 1.0f,1.0f };

	vertexDate[3].position = { -0.5f,-0.5f,0.5f,1.0f };
	vertexDate[3].texcode = { 0.0f,1.0f };

	vertexDate[4].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexDate[4].texcode = { 0.5f,0.0f };

	vertexDate[5].position = { 0.5f,-0.5f,-0.5f,1.0f };
	vertexDate[5].texcode = { 1.0f,1.0f };*/

	ID3D12Device*  device = dxcommond->GetDevice();

	/*DirectX::ScratchImage mipImages = LoadTexture("resources/uvChecker.png");*/


	Input* input = nullptr;
	input = new Input();
	input->Initialize(dxcommond->GetWinApp());
	WinApp* winApp = dxcommond->GetWinApp();
	
	/*Sprite* sprite = nullptr;
	sprite = new Sprite();
	sprite->Initialize(spriteCommon);*/

	std::vector<Sprite*> sprites;
	for (uint32_t i = 0; i < 5; ++i)
	{
		Sprite* sprite = new Sprite();
		sprite->Initialize(spriteCommon);
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
				Vector2 position = sprites[i]->GetPosition();
				position.x = 0.1f + i * 100.0f; position.y += 0.1f;

				sprites[i]->SetPosition(position);

				float rotation = sprites[i]->GetRotation();

				rotation += 0.01f;
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

				sprites[i]->SetSize(scale);

				sprites[i]->UpData();

			}

			if (input->TriggerKey(DIK_D))
			{
				OutputDebugStringA("Hit 0\n");
			}
		}



		dxcommond->PreDraw();

		spriteCommon->CommonRenderingSettings();
		
		//commandList->IASetVertexBuffers(0, 1, &vertexBufferView);

		//commandList->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());

		//commandList->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());

		//commandList->SetGraphicsRootDescriptorTable(2, textureSrvHeapHandleGPU);

		///*commandList->DrawInstanced(6, 1, 0, 0);*/

		//commandList->DrawInstanced(UINT(modelData.vertices.size()), 1, 0, 0);

		/*sprite->Draw();*/

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


	/*CloseHandle(fenceEvent);
	fence->Release();
	rtvDescriptorHeap->Release();
	swapChainResource[0]->Release();
	swapChainResource[1]->Release();
	commandList->Release();*/
	/*materialResource->Release();*/
	device->Release();
	/*useAdapter->Release();
	dxgiFactory->Release();*/
	/*graphicsPipelineState->Release();
	signatureBlob->Release();*/
	/*depthStencilResource->Release();
	dsvDescriptorHeap->Release();*/
	/*indexResourceSprite->Release();
	directionalLightResource->Release();*/
	delete input;
	/*delete sprite;*/
	delete spriteCommon;
	delete dxcommond;

	


	/*if (errorBlob)
	{
		errorBlob->Release();
	}
	rootSignature->Release();
	pixelShaderBlob->Release();
	vertexShaderBlob->Release();*/
#ifdef _DEBUG
	//debugController->Release();
#endif 

	delete dxcommond;




	Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug))))
	{
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
	}

	winApp->Finalize();


	delete winApp;
	return 0;
}