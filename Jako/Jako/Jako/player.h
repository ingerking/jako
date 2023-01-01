#include <vector>
#include <list>
#include <algorithm>
#include <math.h>
#include "sound.h"
#include "image.h"
#include "bullet.h"
#include "enumstruct.h"

#pragma once

#define PLAYER_VEL 3.0f
#define PLAYER_DEL 6
#define PLAYER_NUM 3
#define DASH_VEL 7.0f
#define BULLET_VEL 10.0f
#define RAD_PLUS 5
#define SHOT_DEL 45

using namespace std;

class Player
{
private:
	vector<Image*> imglist;
	vector<Sound*> soundlist;
	list<Bullet*>* bulletlist;
	Bullet* target;
	float x;
	float y;
	int radian;
	int bulletleft;
	int bulletdelay;
	int shotdelay;
	bool dash;
	bool movable;
	bool dashend;
	bool keynotinput;
	int deathcounter;

public:
	Player(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, float& size, float volume, DWORD colorkey);
	~Player(void);
	void initialize();
	void keyinput(unsigned char key);
	void move(bool drawable);
	void drawtarget();
	void setmap();
	void settarget(Bullet* bullet);
	Bullet* gettarget();
	list<Bullet*>* getbulletlist();
	void deletebullet();
	void hit();
	float getx();
	float gety();
	void setvolume(float volume);
};

