#pragma once

#include "enumstruct.h"
#include "stage.h"
#include "player.h"
#include "image.h"
#include "sound.h"
#include <Windows.h>
#include <vector>
#include "font.h"
#include "Option.h"

#include "Resolver.h"
#include "Backmasking.h"
#include "Newsdesk.h"

class Game
{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3d_dev;
	AudioDevicePtr aud_dev;
	Option* option;
	GAMEMODE gamemode;
	SELECTMODE select;
	unsigned char lastkey;
	unsigned char key;
	Player* player;
	Stage* nowstage;
	Stage* prevstage;
	Stage* nextstage;
	vector<Stage*> stagelist;
	vector<char*> replaylist;
	vector<Image*> imagelist;
	vector<Sound*> soundlist;
	FILE* replayfile;
	float size;
	float volume;
	float arr[5];
	int stagenum;
	bool gover;
	Font* stagefont;
	Font* gamefont;
	int sizecount, sizecountsav, volumecount, volumecountsav;

public:
	Game(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, Option* option);
	~Game(void);
	int gameloop(bool flag);
	void setkey(bool flag);
	int gamelooptop();
	int gameloopplay();
	int gameloopoption();
	int gameloopexit();
	int gamelooppractice();
	int gameloopreplay();
	void setrand();
	int gameover();
};

