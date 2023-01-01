#pragma once
#include "stage.h"
#include <algorithm>
#include <list>

#define WRAITH_VEC 3.5f
#define WRAITH_RAN 225.0f
#define START_FRAME 200

using namespace std;

class Resolver :
	public Stage
{
public:
	Resolver(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, wchar_t* name, int num, int numofimg, int numofsnd, float& size, float volume, bool bgm, Player* player, DWORD colorkey):
	  Stage(d3d, d3d_dev, aud_dev, name, num, numofimg, numofsnd, size, volume, bgm, player, colorkey){;}
	~Resolver(void){;}
	int run();
};

