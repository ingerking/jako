#pragma once
#include "stage.h"
#include <algorithm>
#include <list>

#define NEWSDESK_WIDTH 30.0f
#define NEWSDESK_HEIGHT 30.0f
#define NEWSDESK_BULLET_RAN 30.0f
#define NEWSDESK_ANGLE 20
#define NEWSDESK_BULLET_VEL 4.0f
#define NEWSDESK_FIRSTSHOT 180
#define NEWSDESK_SECONDSHOT 300
#define NEWSDESK_THIRDSHOT 420
#define NEWSDESK_FOURTHSHOT 540
#define NEWSDESK_BLIND_START 60
#define NEWSDESK_BLIND_SHOT_DELAY 90
#define NEWSDESK_BLIND_SHOT_DELAY_FAST 45
#define NEWSDESK_OVERRUN 360
#define NEWSDESK_NUMOFBULLET 4

using namespace std;

class Newsdesk :
	public Stage
{
private:
	int lastrandnum;
	int framesave;
public:
	Newsdesk(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, wchar_t* name, int num, int numofimg, int numofsnd, float& size, float volume, bool bgm, Player* player, DWORD colorkey);
	~Newsdesk(void){;}
	int run();
};

