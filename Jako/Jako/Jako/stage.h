#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include "sound.h"
#include "image.h"
#include "bullet.h"
#include "player.h"

#pragma once

using namespace std;

#define STAGE_HP 200
#define STAGE_HP_FLOAT 200.0f

class Stage
{
protected:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3d_dev;
	AudioDevicePtr aud_dev;
	wchar_t* stagename;
	int stagenum;
	Player* player;
	vector<Image*>* imglist;
	vector<Sound*>* soundlist;
	list<Bullet*>* bosslist;
	list<Bullet*>* spritelist;
	list<Bullet*>* bulletlist;
	list<Bullet*>* trashlist;
	int numofimg;
	int numofsnd;
	float& size;
	float volume;
	int frame;
	int hp;
	int counter;
	bool bgm;
	DWORD colorkey;

public:
	Stage(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, wchar_t* name, int num, int numofimg, int numofsnd, float& size, float volume, bool bgm, Player* player, DWORD colorkey);
	~Stage(void);
	virtual int run(){return 0;}
	void createstage();
	void deletestage();
	int gethp(){return hp;}
	wchar_t* getstagename(){return stagename;};
	void setvolume(float volume);
};

