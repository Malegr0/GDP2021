#pragma once

#define CheckError(x) if (x != 0) return x;
#define CheckFailed(hr, code) if (FAILED(hr)) return code;

template<typename T>
void safeRelease(T * &obj)
{
	if (obj != nullptr) 
	{
		obj->Release();
		obj = nullptr;
	}
}