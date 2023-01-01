#include "image.h"


Image::Image(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, wchar_t* name, float& size, DWORD colorkey):size(size)
{
	D3DXIMAGE_INFO info;

	sprite=NULL;
	texture=NULL;

//	this->size=size;

	D3DXCreateSprite(d3d_dev, &sprite);
	D3DXGetImageInfoFromFile(name, &info);
	D3DXCreateTextureFromFileEx(d3d_dev, name, info.Width, info.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, colorkey, NULL, NULL, &texture);

	width=0.0f-(float)info.Width/2.0f;
	height=0.0f-(float)info.Height/2.0f;
}


Image::~Image(void)
{
	if(sprite!=NULL)
		sprite->Release();
	if(texture!=NULL)
		texture->Release();
}

void Image::draw(float x, float y, int color, bool center){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX sizematr;
	D3DXMATRIX matr;
	D3DXMatrixTranslation(&matr, x, y, 0.0f);
	
	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matr, &centermatr, &matr);
	}

	if(size!=1.0f){
		D3DXMatrixScaling(&sizematr, size, size, 1.0f);
		D3DXMatrixMultiply(&matr, &matr, &sizematr);
	}

	sprite->SetTransform(&matr);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}

void Image::draw(float x, float y, float rot, int color, bool center){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX sizematr;
	D3DXMATRIX matrt;
	D3DXMATRIX matrr;
	D3DXMatrixTranslation(&matrt, x, y, 0.0f);
	D3DXMatrixRotationZ(&matrr, rot);

	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matrr, &centermatr, &matrr);
	}

	D3DXMatrixMultiply(&matrt, &matrr, &matrt);
	
	if(size!=1.0f){
		D3DXMatrixScaling(&sizematr, size, size, 1.0f);
		D3DXMatrixMultiply(&matrt, &matrt, &sizematr);
	}

	sprite->SetTransform(&matrt);
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}

void Image::draw(float x, float y, float rot, float scax, float scay, int color, bool center){
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);
	D3DXMATRIX centermatr;
	D3DXMATRIX sizematr;
	D3DXMATRIX matrt;
	D3DXMATRIX matrr;
	D3DXMATRIX matrs;
	D3DXMatrixTranslation(&matrt, x, y, 0.0f);
	D3DXMatrixRotationZ(&matrr, rot);
	D3DXMatrixScaling(&matrs, scax, scay, 1.0f);

	if(center){
		D3DXMatrixTranslation(&centermatr, width, height, 0.0f);
		D3DXMatrixMultiply(&matrs, &centermatr, &matrs);
	}

	D3DXMatrixMultiply(&matrr, &matrs, &matrr);
	D3DXMatrixMultiply(&matrt, &matrr, &matrt);

	if(size!=1.0f){
		D3DXMatrixScaling(&sizematr, size, size, 1.0f);
		D3DXMatrixMultiply(&matrt, &matrt, &sizematr);
	}

	sprite->SetTransform(&matrt);
	
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, &vec, color);
	sprite->End();
}