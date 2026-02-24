#pragma once
#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"


#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

class Input
{
public:
	void Initialize(WinApp* winApp);
	void UpDate();


	template <class T> using Comptr = Microsoft::WRL::ComPtr<T>;


	bool PushKey(BYTE keyNumber);

	bool TriggerKey(BYTE keyNumber);
private:
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};

	WinApp* winApp_ =  nullptr;

	Microsoft::WRL::ComPtr<IDirectInput8> directInput = nullptr;
};

