#include "font.h"


Font::Font(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, float& size, float fontsize):size(size)
{
	fontsprite=NULL;
	font=NULL;

	D3DXFONT_DESC fontDesc;	//��Ʈ�� ������ ���� ����ü�� �ϴ� �����Ѵ�.

	ZeroMemory(&fontDesc, sizeof(fontDesc)); //��Ʈ�� ����ü�� �ʱ�ȭ��Ŵ
	fontDesc.Height = (int)(2.0f*fontsize*size); //��Ʈ�� ����(��ü�� �ʺ��� 2������ ������)
	fontDesc.Width = (int)(fontsize*size); //��Ʈ�� �ʺ�
	fontDesc.Weight = 700; //��Ʈ�� ���� (0(����)~ 1000(����)�� ���� ����)
	fontDesc.Italic = false; //���Ÿ�?
	fontDesc.CharSet = DEFAULT_CHARSET; //����Ʈ�� �����ϱ�
	wcscpy_s(fontDesc.FaceName, L"����"); // �۲� ��Ÿ��


	D3DXCreateFontIndirect(d3d_dev, &fontDesc, &font); //��Ʈ�� �����.
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