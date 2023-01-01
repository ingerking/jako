#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Image
{
private:
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 texture;
	float& size;
	float width;
	float height;

public:
	Image(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, wchar_t* name, float& size, DWORD colorkey);
	~Image(void);
	void draw(float x, float y, int color, bool center);
	void draw(float x, float y, float rot, int color, bool center);
	void draw(float x, float y, float rot, float scax, float scay, int color, bool center);
};

