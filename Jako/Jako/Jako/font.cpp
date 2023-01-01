#include "font.h"


Font::Font(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, float& size, float fontsize):size(size)
{
	fontsprite=NULL;
	font=NULL;

	D3DXFONT_DESC fontDesc;	//폰트의 정보를 담을 구조체를 일단 정의한다.

	ZeroMemory(&fontDesc, sizeof(fontDesc)); //폰트의 구조체를 초기화시킴
	fontDesc.Height = (int)(2.0f*fontsize*size); //폰트의 높이(대체로 너비의 2배쯤이 적당함)
	fontDesc.Width = (int)(fontsize*size); //폰트의 너비
	fontDesc.Weight = 700; //폰트의 굵기 (0(얉음)~ 1000(굵음)의 값을 정함)
	fontDesc.Italic = false; //이탤릭?
	fontDesc.CharSet = DEFAULT_CHARSET; //디폴트로 선택하기
	wcscpy_s(fontDesc.FaceName, L"돋움"); // 글꼴 스타일


	D3DXCreateFontIndirect(d3d_dev, &fontDesc, &font); //폰트를 만든다.
	D3DXCreateSprite(d3d_dev, &fontsprite);
}


Font::~Font(void)
{
	if(fontsprite!=NULL)
		fontsprite->Release();
	if(font!=NULL)
		font->Release();
}

void Font::draw(wchar_t* wcs, float left, float up, float right, float down, DWORD color, int center){
	RECT rc={(LONG)(left*size), (LONG)(up*size), (LONG)(right*size), (LONG)(down*size)};
	fontsprite->Begin(D3DXSPRITE_ALPHABLEND);
	font->DrawTextW(fontsprite, wcs, wcslen(wcs), &rc, center | DT_SINGLELINE | DT_NOCLIP|DT_VCENTER, color);
	fontsprite->End();
}