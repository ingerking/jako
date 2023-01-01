#pragma once
#include "stage.h"
#include <algorithm>
#include <list>

#define BACKMASKING_BULLET_VEC 2.5f
#define BACKMASKING_BULLET_FAST_VEC 7.0f
#define ARBITER_VEC 1.5f
#define ARBITER_RAN 300.0f
#define BULLET_RAN 64.0f
#define BACKMASKING_WAIT_FRAME 350
#define BACKMASKING_START_FRAME 150
#define BACKMASKING_FRAME 0

using namespace std;

class Backmasking :
	public Stage
{
public:
	Backmasking(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, wchar_t* name, int num, int numofimg, int numofsnd, float& size, float volume, bool bgm, Player* player, DWORD colorkey):
	  Stage(d3d, d3d_dev, aud_dev, name, num, numofimg, numofsnd, size, volume, bgm, player, colorkey){;}
	~Backmasking(void){;}
	int run();
};

