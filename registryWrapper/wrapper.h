#pragma once
#include "depends.h"

class Wrapper {
public:
	void RegWrite(LPCWSTR path, LPCWSTR name, LPCWSTR value, DWORD type);

	void RegWrite(LPCWSTR path, LPCWSTR name, DWORD value, DWORD type);

	void RegDel(LPCWSTR path, LPCWSTR name);

	void RegDel(LPCWSTR path);

};
