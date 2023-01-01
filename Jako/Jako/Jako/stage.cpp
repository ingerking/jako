#include "stage.h"


Stage::Stage(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, wchar_t* name, int num, int numofimg, int numofsnd, float& size, float volume, bool bgm, Player* player, DWORD colorkey):size(size)
{
	char str[24];

	Sound* sound;

	soundlist=new vector<Sound*>;

	imglist=NULL;
	bulletlist=NULL;
	bosslist=NULL;
	trashlist=NULL;
	spritelist=NULL;

	this->d3d=d3d;
	this->d3d_dev=d3d_dev;
	this->aud_dev=aud_dev;
	stagename=(wchar_t*)malloc(sizeof(wchar_t)*wcslen(name)+2);
	wcscpy(stagename, name);
	stagenum=num;
	frame=0;
	this->numofimg=numofimg;
	this->numofsnd=numofsnd;
	this->player=player;
//	this->size=size;
	this->volume=volume;
	this->bgm=bgm;
	frame=0;
	counter=0;
	hp=STAGE_HP;
	this->colorkey=colorkey;
	
	if(bgm){
		sprintf_s(str, 24, "res\\stg%02d\\00.ogg", stagenum);
		sound=new Sound(aud_dev, str, volume);
		soundlist->push_back(sound);
	}
	else
		soundlist->push_back(NULL);
	for(int i=1;i<numofsnd;i++){
		sprintf_s(str, 24, "res\\stg%02d\\%02d.wav", stagenum, i);
		sound=new Sound(aud_dev, str, volume);
		soundlist->push_back(sound);
	}
}


Stage::~Stage(void)
{
	deletestage();
	Sound* sound;
	for(vector<Sound*>::iterator iter=soundlist->begin();iter!=soundlist->end();iter++){
		sound=*iter;
		if(sound!=NULL)
			delete sound;
	}
	soundlist->clear();
	delete soundlist;
	free(stagename);
}

void Stage::createstage(){
	Image* image;
	wchar_t wcs[24];
	frame=0;
	counter=0;
	
	if(imglist==NULL)
		imglist=new vector<Image*>;
	for(int i=0;i<numofimg;i++){
		swprintf_s(wcs, 24, L"res\\stg%02d\\%02d.png", stagenum, i);
		image=new Image(d3d, d3d_dev, wcs, size, colorkey);
		imglist->push_back(image);
	}
	if(bulletlist==NULL)
		bulletlist=new list<Bullet*>;
	if(trashlist==NULL)
		trashlist=new list<Bullet*>;
	if(bosslist==NULL)
		bosslist=new list<Bullet*>;
	if(spritelist==NULL)
		spritelist=new list<Bullet*>;
	
	hp=STAGE_HP;
}

void Stage::deletestage(){
	Image* image;
	Bullet* bullet;
	Sound* sound;
	list<Bullet*>::iterator buliter;
	if(imglist!=NULL){
		for(vector<Image*>::iterator imgiter=imglist->begin();imgiter!=imglist->end();imgiter++){
			image=*imgiter;
			delete image;
		}
		imglist->clear();
		delete imglist;
		imglist=NULL;
	}
	if(bulletlist!=NULL){
		for(buliter=bulletlist->begin();buliter!=bulletlist->end();buliter++){
			bullet=*buliter;
			delete bullet;
		}
		bulletlist->clear();
		delete bulletlist;
		bulletlist=NULL;
	}
	if(bosslist!=NULL){
		for(buliter=bosslist->begin();buliter!=bosslist->end();buliter++){
			bullet=*buliter;
			delete bullet;
		}
		bosslist->clear();
		delete bosslist;
		bosslist=NULL;
	}
	if(spritelist!=NULL){
		for(buliter=spritelist->begin();buliter!=spritelist->end();buliter++){
			bullet=*buliter;
			delete bullet;
		}
		spritelist->clear();
		delete spritelist;
		spritelist=NULL;
	}
	if(trashlist!=NULL){
		for(buliter=trashlist->begin();buliter!=trashlist->end();buliter++){
			bullet=*buliter;
			delete bullet;
		}
		trashlist->clear();
		delete trashlist;
		trashlist=NULL;
	}
	if(!soundlist->empty()){
		for(int i=0;i<soundlist->size();i++){
			sound=soundlist->at(i);
			if(sound!=NULL){
				sound->stop();
				sound->reset();
			}
		}
	}
}

void Stage::setvolume(float volume){
	vector<Sound*>::iterator iter;
	for(iter=soundlist->begin();iter!=soundlist->end();iter++){
		if(*iter!=NULL){
			(*iter)->setvolume(volume);
		}
	}
}