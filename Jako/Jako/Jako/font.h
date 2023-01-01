#include <d3d9.h>
#include <d3dx9.h>

#pragma once
class Font
{
private:
	LPD3DXSPRITE fontsprite;
	LPD3DXFONT font;
	float& size;
public:
	Font(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, float& size, float fontsize);
	~Font(void);
	void draw(wchar_t* wcs, float left, float up, float right, float down, DWORD color, int center);
};

