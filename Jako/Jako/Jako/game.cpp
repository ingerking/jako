#include "game.h"


Game::Game(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, Option* option)
{
	this->option=option;
	this->volume=option->setvolume();
	this->size=option->setsize();
	this->size=1.0f;
	this->sizecount=option->getsize();
	this->sizecountsav=this->sizecount;
	this->volumecount=option->getvolume();
	this->volumecountsav=this->volumecount;
	this->d3d=d3d;
	this->d3d_dev=d3d_dev;
	this->aud_dev=aud_dev;
	Image* opzimage=new Image(d3d, d3d_dev, L"res\\system\\99.png", size, 0); 
	d3d_dev->Clear( 0, NULL, D3DCLEAR_TARGET, 0xFFFFFFFF, 1.0f, 0 );
	d3d_dev->BeginScene();
	opzimage->draw(400.0f, 300.0f, 0xFFFFFFFF, true);
	d3d_dev->EndScene();
	d3d_dev->Present(NULL, NULL, NULL, NULL);
	delete opzimage;


	player=NULL;
	replayfile=NULL;
	nowstage=NULL;
	prevstage=NULL;
	nextstage=NULL;
	stagenum=0;
	gover=false;

	gamemode=GM_TOP;
	select=SE_ARCADE;

	setrand();

	stagefont=new Font(d3d, d3d_dev, size, 8.0f);
	gamefont=new Font(d3d, d3d_dev, size, 24.0f);
	
	player=new Player(d3d, d3d_dev, aud_dev, size, volume, 0);

	Image* image;
	image=new Image(d3d, d3d_dev, L"res\\system\\00.png", size, 0);//bg
	imagelist.push_back(image);
	image=new Image(d3d, d3d_dev, L"res\\system\\01.png", size, 0);//arcade
	imagelist.push_back(image);
	image=new Image(d3d, d3d_dev, L"res\\system\\02.png", size, 0);//practice
	imagelist.push_back(image);
	image=new Image(d3d, d3d_dev, L"res\\system\\03.png", size, 0);//replay
	imagelist.push_back(image);
	image=new Image(d3d, d3d_dev, L"res\\system\\04.png", size, 0);//option
	imagelist.push_back(image);
	image=new Image(d3d, d3d_dev, L"res\\system\\05.png", size, 0);//exit
	imagelist.push_back(image);
	image=new Image(d3d, d3d_dev, L"res\\system\\06.png", size, 0);//hpbar
	imagelist.push_back(image);
	image=new Image(d3d, d3d_dev, L"res\\system\\07.png", size, 0);//key
	imagelist.push_back(image);

	Sound* sound;
	sound=new Sound(aud_dev, "res\\system\\00.ogg", volume);
	soundlist.push_back(sound);
	sound=new Sound(aud_dev, "res\\system\\01.wav", volume);
	soundlist.push_back(sound);
	sound=new Sound(aud_dev, "res\\system\\02.wav", volume);
	soundlist.push_back(sound);
	sound=new Sound(aud_dev, "res\\system\\03.wav", volume);
	soundlist.push_back(sound);
	
	
	stagelist.push_back(new Resolver(d3d, d3d_dev, aud_dev, L"Stage 001", 1, 27, 2, size, volume, true, player, 0xFF000000));
	stagelist.push_back(new Backmasking(d3d, d3d_dev, aud_dev, L"Stage 002", 2, 32, 3, size, volume, true, player, 0xFF000000));
	stagelist.push_back(new Newsdesk(d3d, d3d_dev, aud_dev, L"Stage 003", 3, 5, 6, size, volume, false, player, 0xFF000000));
	
}

Game::~Game(void)
{
	Image* image;
	Sound* sound;
	Stage* stage;
	char* name;
	if(player!=NULL)
		delete player;
	if(replayfile!=NULL)
		fclose(replayfile);
	for(vector<Image*>::iterator imgiter=imagelist.begin();imgiter!=imagelist.end();imgiter++){
		image=*imgiter;
		delete image;
	}
	imagelist.clear();
	for(vector<Sound*>::iterator snditer=soundlist.begin();snditer!=soundlist.end();snditer++){
		sound=*snditer;
		delete sound;
	}
	soundlist.clear();
	for(vector<Stage*>::iterator staiter=stagelist.begin();staiter!=stagelist.end();staiter++){
		stage=*staiter;
		delete stage;
	}
	stagelist.clear();
	for(vector<char*>::iterator repiter=replaylist.begin();repiter!=replaylist.end();repiter++){
		name=*repiter;
		free(name);
	}
	replaylist.clear();
	delete stagefont;
	delete gamefont;
}

int Game::gameloop(bool flag){
	setkey(flag);

	switch(gamemode){
	case GM_TOP:
		return gamelooptop();
	case GM_PLAY:
		return gameloopplay();
	case GM_OPTION:
		return gameloopoption();
	case GM_EXIT:
		return gameloopexit();
	case GM_PRACTICE:
		return gamelooppractice();
	case GM_REPLAY:
		return gameloopreplay();
	default:
		return 1;
	}
}

void Game::setkey(bool flag){
	lastkey=key;
	key=0x00;
	if(gamemode==GM_PLAY&&select==SE_REPLAY){
		;
		//
	}
	else{
		if(flag){
			if(GetAsyncKeyState(VK_LEFT)&0x8000){
				key=key|MYKEY_LEFT;
			}
			if(GetAsyncKeyState(VK_RIGHT)&0x8000){
				key=key|MYKEY_RIGHT;
			}
			if(GetAsyncKeyState(VK_UP)&0x8000){
				key=key|MYKEY_UP;
			}
			if(GetAsyncKeyState(VK_DOWN)&0x8000){
				key=key|MYKEY_DOWN;
			}
			if(GetAsyncKeyState(VK_ESCAPE)&0x8000){
				key=key|MYKEY_LSHIFT;
			}
			if(GetAsyncKeyState('Z')&0x8000){
				key=key|MYKEY_SHOT;
			}
			if(GetAsyncKeyState('X')&0x8000){
				key=key|MYKEY_BOMB;
			}
			if(GetAsyncKeyState('C')&0x8000){
				key=key|MYKEY_DASH;
			}
		}
	}
}

int Game::gamelooptop(){
	unsigned char keyselect=key&(~lastkey);

	soundlist.at(0)->play(true);

	switch(select){
	case SE_ARCADE:
		if(keyselect&MYKEY_DOWN){
			soundlist.at(1)->play(true, false);
			select=SE_PRACTICE;
		}
		else if(keyselect&MYKEY_UP){
			soundlist.at(1)->play(true, false);
			select=SE_EXIT;
		}
		else if(keyselect&MYKEY_SHOT){
			soundlist.at(0)->stop();
			soundlist.at(0)->reset();
			soundlist.at(2)->play(true, false);
			stagenum=1;
			gover=false;
			gamemode=GM_PLAY;
			player->initialize();
			nowstage=stagelist.at(0);
			nowstage->createstage();
			if(stagelist.size()!=1){
				nextstage=stagelist.at(1);
			}
		}
		else if(keyselect&MYKEY_BOMB){
			soundlist.at(3)->play(true, false);
			select=SE_EXIT;
		}
		break;
	case SE_PRACTICE:
		if(keyselect&MYKEY_DOWN){
			soundlist.at(1)->play(true, false);
			select=SE_OPTION;
		}
		else if(keyselect&MYKEY_UP){
			soundlist.at(1)->play(true, false);
			select=SE_ARCADE;
		}
		else if(keyselect&MYKEY_SHOT){
			soundlist.at(2)->play(true, false);
			stagenum=0;
			gamemode=GM_PRACTICE;
		}
		else if(keyselect&MYKEY_BOMB){
			soundlist.at(3)->play(true, false);
			select=SE_EXIT;
		}
		break;
	case SE_REPLAY:
		if(keyselect&MYKEY_DOWN){
			soundlist.at(1)->play(true, false);
			select=SE_OPTION;
		}
		else if(keyselect&MYKEY_UP){
			soundlist.at(1)->play(true, false);
			select=SE_PRACTICE;
		}
		else if(keyselect&MYKEY_SHOT){
			soundlist.at(2)->play(true, false);
			gamemode=GM_REPLAY;
		}
		else if(keyselect&MYKEY_BOMB){
			soundlist.at(3)->play(true, false);
			select=SE_EXIT;
		}
		break;
	case SE_OPTION:
		if(keyselect&MYKEY_DOWN){
			soundlist.at(1)->play(true, false);
			select=SE_EXIT;
		}
		else if(keyselect&MYKEY_UP){
			soundlist.at(1)->play(true, false);
			select=SE_PRACTICE;
		}
		else if(keyselect&MYKEY_SHOT){
			soundlist.at(2)->play(true, false);
			stagenum=0;
			gamemode=GM_OPTION;
		}
		else if(keyselect&MYKEY_BOMB){
			soundlist.at(3)->play(true, false);
			select=SE_EXIT;
		}
		break;
	case SE_EXIT:
		if(keyselect&MYKEY_DOWN){
			soundlist.at(1)->play(true, false);
			select=SE_ARCADE;
		}
		else if(keyselect&MYKEY_UP){
			soundlist.at(1)->play(true, false);
			select=SE_OPTION;
		}
		else if(keyselect&MYKEY_SHOT){
			soundlist.at(3)->play(true, false);
			gamemode=GM_EXIT;
		}
		else if(keyselect&MYKEY_BOMB){
			soundlist.at(3)->play(true, false);
			select=SE_EXIT;
		}
		break;
	default:
		return 1;
	}

	imagelist.at(0)->draw(0.0f, 0.0f, 0xFFFFFFFF, false);
	for(int i=0;i<5;i++){
		imagelist.at(i+1)->draw(600.0f+arr[i], 200.0f+(float)(75*i), ((SELECTMODE)i==select?0xFFFFFFFF:D3DCOLOR_RGBA(255, 255, 255, 127)), true);
	}
	imagelist.at(7)->draw(65.0f, 325.0f, 0x80FFFFFF, false);

	return 0;
}

int Game::gameloopplay(){
	if(key&MYKEY_LSHIFT){
		if(nowstage)
			nowstage->deletestage();
		if(nextstage)
			nextstage->deletestage();
		gamemode=GM_TOP;
		gover=false;
		nextstage=NULL;
		return 0;
	}
	player->keyinput(key&~(MYKEY_SHOT&(lastkey|~MYKEY_SHOT)));
	if(gover){
		if(gameover()){
			gover=false;
			gamemode=GM_TOP;
		}
	}
	else{
		if(nowstage->run()){
			nowstage->deletestage();
			if(nextstage!=NULL){
				if(stagenum!=-1){//not practice
					nowstage=nextstage;
					nowstage->createstage();
					stagenum++;
					if(stagenum>=stagelist.size()){
						nextstage=NULL;
					}
					else{
						nextstage=stagelist.at(stagenum);
					}
				}
				else{
					gover=true;
				}
			}
			else{
				gover=true;
			}
		}
		else{
			imagelist.at(6)->draw(200.0f, 20.0f, 0.0f, (float)nowstage->gethp()/STAGE_HP_FLOAT, 1.0f, 0xC0FFFFFF, false);
//			gamefont->draw(nowstage->getstagename(), 0.0f, 15.0f, 800.0f, 55.0f, 0xFFFF8888, DT_CENTER);
		}
	}
	
	return 0;
}

int Game::gameloopoption(){
	unsigned char optionkey=key&~lastkey;
	if(optionkey&MYKEY_SHOT){
		volume=option->setvolume(volumecount);
		if(sizecountsav!=sizecount){
			size=option->setsize(sizecount);
			sizecountsav=sizecount;
		}
		if(volumecountsav!=volumecount){
			player->setvolume(volume);
			for(vector<Sound*>::iterator siter=soundlist.begin();siter!=soundlist.end();siter++){
				(*siter)->setvolume(volume);
			}
			for(vector<Stage*>::iterator iter=stagelist.begin();iter!=stagelist.end();iter++){
				(*iter)->setvolume(volume);
			}
			volumecountsav=volumecount;
		}
		soundlist.at(2)->play(true, false);
		gamemode=GM_TOP;
	}
	else if(optionkey&MYKEY_BOMB){
		soundlist.at(3)->play(true, false);
		soundlist.at(0)->setvolume(volume);
		soundlist.at(1)->setvolume(volume);
		option->setvolume(volumecountsav);
		sizecount=sizecountsav;
		volumecount=volumecountsav;
		gamemode=GM_TOP;
	}
	else if(optionkey&MYKEY_DOWN){
		if(stagenum==0){
			soundlist.at(1)->play(true, false);
			stagenum=1;
		}
	}
	else if(optionkey&MYKEY_UP){
		if(stagenum==1){
			soundlist.at(1)->play(true, false);
			stagenum=0;
		}
	}
	else if(optionkey&MYKEY_RIGHT){
		if(stagenum==0){
			if(sizecount!=6){
				soundlist.at(1)->play(true, false);
				sizecount++;
			}
		}
		else{
			if(volumecount!=10){
				volumecount++;
				soundlist.at(0)->setvolume(option->setvolume(volumecount));
				soundlist.at(1)->setvolume(option->setvolume(volumecount));
				soundlist.at(1)->play(true, false);
			}
		}
	}
	else if(optionkey&MYKEY_LEFT){
		if(stagenum==0){
			if(sizecount!=0){
				soundlist.at(1)->play(true, false);
				sizecount--;
			}
		}
		else{
			if(volumecount!=0){
				volumecount--;
				soundlist.at(0)->setvolume(option->setvolume(volumecount));
				soundlist.at(1)->setvolume(option->setvolume(volumecount));
				soundlist.at(1)->play(true, false);
			}
		}
	}
	switch(sizecount){
	case 0:
		gamefont->draw(L"Display : 640 x 480", 150.0f, 150.0f, 650.0f, 200.0f, D3DCOLOR_ARGB((1-stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 1:
		gamefont->draw(L"Display : 800 x 600", 150.0f, 150.0f, 650.0f, 200.0f, D3DCOLOR_ARGB((1-stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 2:
		gamefont->draw(L"Display : 1024 x 768", 150.0f, 150.0f, 650.0f, 200.0f, D3DCOLOR_ARGB((1-stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 3:
		gamefont->draw(L"Display : 1152 x 864", 150.0f, 150.0f, 650.0f, 200.0f, D3DCOLOR_ARGB((1-stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 4:
		gamefont->draw(L"Display : 1200 x 900", 150.0f, 150.0f, 650.0f, 200.0f, D3DCOLOR_ARGB((1-stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 5:
		gamefont->draw(L"Display : 1280 x 960", 150.0f, 150.0f, 650.0f, 200.0f, D3DCOLOR_ARGB((1-stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	default:
		gamefont->draw(L"Display : 1440 x 1080", 150.0f, 150.0f, 650.0f, 200.0f, D3DCOLOR_ARGB((1-stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	}
	switch(volumecount){
	case 0:
		gamefont->draw(L"Volume : 0", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 1:
		gamefont->draw(L"Volume : 1", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 2:
		gamefont->draw(L"Volume : 2", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 3:
		gamefont->draw(L"Volume : 3", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 4:
		gamefont->draw(L"Volume : 4", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 5:
		gamefont->draw(L"Volume : 5", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 6:
		gamefont->draw(L"Volume : 6", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 7:
		gamefont->draw(L"Volume : 7", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 8:
		gamefont->draw(L"Volume : 8", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	case 9:
		gamefont->draw(L"Volume : 9", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	default:
		gamefont->draw(L"Volume : 10", 155.0f, 210.0f, 645.0f, 320.0f, D3DCOLOR_ARGB((stagenum)*127+128, 255, 136, 136), DT_LEFT);
		break;
	}
	imagelist.at(4)->draw(500.0f, 450.0f, 0x80FFFFFF, false);

	return 0;
}

int Game::gameloopexit(){
	return 1;
}

int Game::gamelooppractice(){
	unsigned char practicekey=key&~lastkey;
	if(practicekey&MYKEY_SHOT){
		soundlist.at(0)->stop();
		soundlist.at(0)->reset();
		soundlist.at(2)->play(true, false);
		nowstage=stagelist.at(stagenum);
		stagenum=-1;
		gover=false;
		gamemode=GM_PLAY;
		player->initialize();
		nowstage->createstage();
		nextstage=NULL;
	}
	else if(practicekey&MYKEY_BOMB){
		soundlist.at(3)->play(true, false);
		gamemode=GM_TOP;
	}
	else if(practicekey&MYKEY_DOWN){
		soundlist.at(1)->play(true, false);
		stagenum++;
		if(stagenum==stagelist.size()){
			stagenum=0;
		}
	}
	else if(practicekey&MYKEY_UP){
		soundlist.at(1)->play(true, false);
		if(stagenum==0){
			stagenum=stagelist.size()-1;
		}
		else{
			stagenum--;
		}
	}

	for(int i=0;i<stagelist.size();i++){
		if(i==stagenum){
			stagefont->draw(stagelist.at(i)->getstagename(), 100.0f, 50.0f+(float)(i)*25.0f, 700.0f, 75.0f+(float)(i)*25.0f, 0xFFFF8888, DT_LEFT);
		}
		else{
			stagefont->draw(stagelist.at(i)->getstagename(), 100.0f, 50.0f+(float)(i)*25.0f, 700.0f, 75.0f+(float)(i)*25.0f, 0x80FF8888, DT_LEFT);
		}
	}
	imagelist.at(2)->draw(500.0f, 450.0f, 0x80FFFFFF, false);
	return 0;
}

int Game::gameloopreplay(){
	return 1;
}

void Game::setrand(){
	for(int i=0;i<5;i++){
		arr[i]=(float)(2*(rand()%25));
	}
}

int Game::gameover(){
	return 1;
}