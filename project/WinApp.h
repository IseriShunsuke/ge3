#pragma once
#include <windows.h>
#include <cstdint>

class WinApp
{
public:

	void Initialize();
	void UpData();

	
	void Finalize();

	bool ProcessMessage();



	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparsm, LPARAM lparam);

	HWND GetHWND() const { return hwnd; }
	HINSTANCE GetHInstance() const { return wc.hInstance; }

	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;
private:
	HWND hwnd = nullptr;
	WNDCLASS wc{};
	
	
};

