#include <Windows.h>
#include <stdio.h>

#pragma once
class Option
{
private:
	HWND& hWnd;
	WNDCLASSEX& wc;
	int size;
	int volume;
public:
	Option(HWND& hWnd, WNDCLASSEX& wc);
	~Option(void);
	float setsize(int _size);
	float setsize();
	float setvolume(int _volume);
	float setvolume();
	int getsize(){return size;}
	int getvolume(){return volume;}
};

