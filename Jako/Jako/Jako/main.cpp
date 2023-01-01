#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"
#include "enumstruct.h"
#include <audiere.h>
#include <MemoryLeak.h>
#include "Option.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#pragma comment (lib, "audiere.lib")

LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3d_dev;

float size=1.0f;
float volume=0.5f;

AudioDevicePtr aud_dev;

HRESULT initD3D(HWND hWnd){
	d3d=Direct3DCreate9(D3D_SDK_VERSION);	//인터페이스 생성
	D3DPRESENT_PARAMETERS d3dpp;			//각종 변수들을 담는 구조체
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//메모리 초기화
	d3dpp.Windowed=TRUE;					//창 모드
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;	//
	d3dpp.hDeviceWindow=hWnd;				//세팅
	d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//디바이스 생성
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3d_dev);
	
    d3d_dev->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3d_dev->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

	return S_OK;
}

void cleanD3D(){
	d3d->Release();
	d3d_dev->Release();
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		
		
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT){
	Game* game;
	Option* option;
	WNDCLASSEX wc={sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, hInst, NULL, LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW+1), 
		NULL, L"jako", NULL};
	RegisterClassEx(&wc);

	HWND hWnd=CreateWindow(L"jako", L"jako v.test", WS_OVERLAPPED|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU, 0, 0, 200, 100, NULL, NULL, wc.hInstance, NULL);
		
	RECT rect;
	GetClientRect(hWnd, &rect);
	int x=1000-rect.right;
	int y=700-rect.bottom;
	HDC hdc=GetDC(NULL);
	int dx=GetDeviceCaps(hdc, HORZRES);
	int dy=GetDeviceCaps(hdc, VERTRES);

	dx=(dx-x)/2;
	dy=(dy-y)/2;

	SetWindowPos(hWnd, HWND_NOTOPMOST, dx, dy, x, y, SWP_NOZORDER);
	ReleaseDC(hWnd, hdc);
	
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	option=new Option(hWnd, wc);

	initD3D(hWnd); //생성 & 초기화
	aud_dev=OpenDevice();



	////////////////

//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

//	_CrtSetBreakAlloc(191);

	//////////



	srand((unsigned)time(NULL));
	game=new Game(d3d, d3d_dev, aud_dev, option);
	bool flag;
	HWND focused;

	MSG msg;
	msg.message = 0;
	while(msg.message!=WM_QUIT){
		flag=false;
		focused=GetFocus();
		if(focused==hWnd){
			flag=true;
		}

		if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		d3d_dev->Clear( 0, NULL, D3DCLEAR_TARGET, 0xFF000000, 1.0f, 0 );
		d3d_dev->BeginScene();
		if(game->gameloop(flag)){
			d3d_dev->EndScene();
			d3d_dev->Present(NULL, NULL, NULL, NULL);
			break;
		}
		else{
			d3d_dev->EndScene();
			d3d_dev->Present(NULL, NULL, NULL, NULL);
		}
	}
	delete game;
	
	cleanD3D(); //릴리즈
	delete option;

	UnregisterClass(L"jako", wc.hInstance);

	_CrtDumpMemoryLeaks();
	return 0;
}
