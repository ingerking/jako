#include "Option.h"


Option::Option(HWND& hWnd, WNDCLASSEX& wc):hWnd(hWnd), wc(wc)
{
	FILE* fp=fopen("settings.se", "rb");
	if(fp==NULL){
		size=1;
		volume=5;
	}
	else{
		fread(&size, sizeof(int), 1, fp);
		fread(&volume, sizeof(int), 1, fp);
		fclose(fp);
	}
}


Option::~Option(void)
{
	FILE* fp=fopen("settings.se", "wb");
	if(fp!=NULL){
		fwrite(&size, sizeof(int), 1, fp);
		fwrite(&volume, sizeof(int), 1, fp);
		fclose(fp);
	}
}

float Option::setsize(int _size){
	HDC hdc;
	size=_size;
	int x, y, cx, cy;
	hdc=GetDC(NULL);
	x=GetDeviceCaps(hdc, HORZRES);
	y=GetDeviceCaps(hdc, VERTRES);
	switch(size){
	case 0:
		cx=640;
		cy=480;
		break;
	case 2:
		cx=1024;
		cy=768;
		break;
	case 3:
		cx=1152;
		cy=864;
		break;
	case 4:
		cx=1200;
		cy=900;
		break;
	case 5:
		cx=1280;
		cy=960;
		break;
	case 6:
		cx=1440;
		cy=1080;
		break;
	default:
		cx=800;
		cy=600;
		break;
	}
	SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, cx, cy, SWP_NOZORDER|SWP_NOMOVE);
	RECT rect;
	GetClientRect(hWnd, &rect);
	cx=2*cx-rect.right;
	cy=2*cy-rect.bottom;
	x=(x-cx)/2;
	y=(y-cy)/2;	
	SetWindowPos(hWnd, HWND_NOTOPMOST, x, y, cx, cy, SWP_NOZORDER);
	ReleaseDC(hWnd, hdc);
	return 1.0f;
}

float Option::setsize(){
	HDC hdc;
	int x, y, cx, cy;
	hdc=GetDC(NULL);
	x=GetDeviceCaps(hdc, HORZRES);
	y=GetDeviceCaps(hdc, VERTRES);
	switch(size){
	case 0:
		cx=640;
		cy=480;
		break;
	case 2:
		cx=1024;
		cy=768;
		break;
	case 3:
		cx=1152;
		cy=864;
		break;
	case 4:
		cx=1200;
		cy=900;
		break;
	case 5:
		cx=1280;
		cy=960;
		break;
	case 6:
		cx=1440;
		cy=1080;
		break;
	default:
		cx=800;
		cy=600;
		break;
	}
	SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, cx, cy, SWP_NOZORDER|SWP_NOMOVE);
	RECT rect;
	GetClientRect(hWnd, &rect);
	cx=2*cx-rect.right;
	cy=2*cy-rect.bottom;
	x=(x-cx)/2;
	y=(y-cy)/2;	
	SetWindowPos(hWnd, HWND_NOTOPMOST, x, y, cx, cy, SWP_NOZORDER);
	ReleaseDC(hWnd, hdc);
	return 1.0f;
}

float Option::setvolume(int _volume){
	volume=_volume;
	switch(volume){
	case 0:
		return 0.0f;
	case 1:
		return 0.1f;
	case 2:
		return 0.2f;
	case 3:
		return 0.3f;
	case 4:
		return 0.4f;
	case 6:
		return 0.6f;
	case 7:
		return 0.7f;
	case 8:
		return 0.8f;
	case 9:
		return 0.9f;
	case 10:
		return 1.0f;
	default:
		return 0.5f;
	}
}

float Option::setvolume(){
	switch(volume){
	case 0:
		return 0.0f;
	case 1:
		return 0.1f;
	case 2:
		return 0.2f;
	case 3:
		return 0.3f;
	case 4:
		return 0.4f;
	case 6:
		return 0.6f;
	case 7:
		return 0.7f;
	case 8:
		return 0.8f;
	case 9:
		return 0.9f;
	case 10:
		return 1.0f;
	default:
		return 0.5f;
	}
}