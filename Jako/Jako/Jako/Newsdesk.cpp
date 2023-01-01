#include "Newsdesk.h"

Newsdesk::Newsdesk(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, wchar_t* name, int num, int numofimg, int numofsnd, float& size, float volume, bool bgm, Player* player, DWORD colorkey):
Stage(d3d, d3d_dev, aud_dev, name, num, numofimg, numofsnd, size, volume, bgm, player, colorkey)
{
	lastrandnum=0;
	framesave=0;
}

int Newsdesk::run(){
	list<Bullet*>::iterator iter;
	Bullet* bullet;
	Bullet* bullet2;
	int i, j, k;
	float x, y;

	if(!bosslist->empty()){
		bullet=(*bosslist->begin());
		x=bullet->getx()-player->getx();
		y=bullet->gety()-player->gety();
		if(x<NEWSDESK_WIDTH&&x>-NEWSDESK_WIDTH&&y<NEWSDESK_HEIGHT&&y>-NEWSDESK_HEIGHT){
			player->hit();
		}
	}
	for(iter=bulletlist->begin();iter!=bulletlist->end();iter++){
		bullet=(*iter);
		bullet->move();
		if(bullet->getusable()){
			x=bullet->getx()-player->getx();
			y=bullet->gety()-player->gety();
			if(x*x+y*y<NEWSDESK_BULLET_RAN){
				player->hit();
				bullet->setusable(false);
				trashlist->push_back(bullet);
			}
			else{
				if(bullet->outofmap(30.0f, 30.0f)){
					bullet->setusable(false);
					trashlist->push_back(bullet);
				}
			}
		}
	}

	if(frame==0){
		lastrandnum=0;
		framesave=0;
		bullet=new Bullet(400.0f, 300.0f, 0.0f, 0.0f, 0);
		bullet->setinmap(true);
		bullet->setusable(true);
		bosslist->push_back(bullet);
		player->settarget(bullet);
	}
	else if(frame==NEWSDESK_FIRSTSHOT||frame==NEWSDESK_THIRDSHOT){
		lastrandnum=0;
		soundlist->at(4)->play(true, false);
		bullet=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, player->getx(), player->gety(), 0);
		bullet->setrad();
		bulletlist->push_back(bullet);
		for(i=0;i<NEWSDESK_NUMOFBULLET;i++){
			j=bullet->getradint()+(i+1)*NEWSDESK_ANGLE;
			k=bullet->getradint()-(i+1)*NEWSDESK_ANGLE;
			if(j>=360) j-=360;
			if(k<0) k+=360;
			bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, j, 0);
			bullet2->setrad();
			bulletlist->push_back(bullet2);
			bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, k, 0);
			bullet2->setrad();
			bulletlist->push_back(bullet2);
		}
	}
	else if(frame==NEWSDESK_SECONDSHOT||frame==NEWSDESK_FOURTHSHOT){
		lastrandnum=1;
		soundlist->at(5)->play(true, false);
		bullet=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, player->getx(), player->gety(), 0);
		bullet->setrad();
		for(i=0;i<NEWSDESK_NUMOFBULLET;i++){
			j=bullet->getradint()+i*NEWSDESK_ANGLE+NEWSDESK_ANGLE/2;
			k=bullet->getradint()-i*NEWSDESK_ANGLE-NEWSDESK_ANGLE/2;
			if(j>=360) j-=360;
			if(k<0) k+=360;
			bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, j, 1);
			bullet2->setrad();
			bulletlist->push_back(bullet2);
			bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, k, 1);
			bullet2->setrad();
			bulletlist->push_back(bullet2);
		}
		delete bullet;
	}
	if(frame==NEWSDESK_BLIND_START){
		soundlist->at(1)->play(false);
	}
	else if(frame>NEWSDESK_BLIND_START&&!bosslist->empty()){
		if(framesave==0){
			if(!soundlist->at(1)->getisplaying()){
				framesave=frame;
				soundlist->at(2)->play(false);
				bullet=*bosslist->begin();
				bullet->setusable(false);
			}
		}
		else{
			if((frame-framesave)%NEWSDESK_BLIND_SHOT_DELAY==0){
				lastrandnum=(lastrandnum+1)%2;
				if(lastrandnum==0){
					soundlist->at(4)->play(true, false);
					bullet=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, player->getx(), player->gety(), 0);
					bullet->setrad();
					bulletlist->push_back(bullet);
					for(i=0;i<NEWSDESK_NUMOFBULLET;i++){
						j=bullet->getradint()+(i+1)*NEWSDESK_ANGLE;
						k=bullet->getradint()-(i+1)*NEWSDESK_ANGLE;
						if(j>=360) j-=360;
						if(k<0) k+=360;
						bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, j, 0);
						bullet2->setrad();
						bulletlist->push_back(bullet2);
						bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, k, 0);
						bullet2->setrad();
						bulletlist->push_back(bullet2);
					}
				}
				else{
					soundlist->at(5)->play(true, false);
					bullet=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, player->getx(), player->gety(), 0);
					bullet->setrad();
					for(i=0;i<NEWSDESK_NUMOFBULLET;i++){
						j=bullet->getradint()+i*NEWSDESK_ANGLE+NEWSDESK_ANGLE/2;
						k=bullet->getradint()-i*NEWSDESK_ANGLE-NEWSDESK_ANGLE/2;
						if(j>=360) j-=360;
						if(k<0) k+=360;
						bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, j, 1);
						bullet2->setrad();
						bulletlist->push_back(bullet2);
						bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, k, 1);
						bullet2->setrad();
						bulletlist->push_back(bullet2);
					}
					delete bullet;
				}
			}
			else if((frame-framesave)%NEWSDESK_BLIND_SHOT_DELAY_FAST==0){
				if(!((*bosslist->begin())->getinmap())){
					lastrandnum=(lastrandnum+1)%2;
					if(lastrandnum==0){
						soundlist->at(4)->play(true, false);
						bullet=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, player->getx(), player->gety(), 0);
						bullet->setrad();
						bulletlist->push_back(bullet);
						for(i=0;i<NEWSDESK_NUMOFBULLET;i++){
							j=bullet->getradint()+(i+1)*NEWSDESK_ANGLE;
							k=bullet->getradint()-(i+1)*NEWSDESK_ANGLE;
							if(j>=360) j-=360;
							if(k<0) k+=360;
							bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, j, 0);
							bullet2->setrad();
							bulletlist->push_back(bullet2);
							bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, k, 0);
							bullet2->setrad();
							bulletlist->push_back(bullet2);
						}
					}
					else{
						soundlist->at(5)->play(true, false);
						bullet=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, player->getx(), player->gety(), 0);
						bullet->setrad();
						for(i=0;i<NEWSDESK_NUMOFBULLET;i++){
							j=bullet->getradint()+i*NEWSDESK_ANGLE+NEWSDESK_ANGLE/2;
							k=bullet->getradint()-i*NEWSDESK_ANGLE-NEWSDESK_ANGLE/2;
							if(j>=360) j-=360;
							if(k<0) k+=360;
							bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, j, 0);
							bullet2->setrad();
							bulletlist->push_back(bullet2);
							bullet2=new Bullet(400.0f, 300.0f, NEWSDESK_BULLET_VEL, k, 0);
							bullet2->setrad();
							bulletlist->push_back(bullet2);
						}
						delete bullet;
					}
				}
			}
			if(frame-framesave==NEWSDESK_OVERRUN){
				soundlist->at(3)->play(false);
				(*bosslist->begin())->setinmap(false);
			}
		}
	}

	if(!bosslist->empty()){
		bullet2=(*bosslist->begin());

		for(iter=player->getbulletlist()->begin();iter!=player->getbulletlist()->end();iter++){
			bullet=*iter;
			if(bullet->getusable()){
				x=bullet->getx()-bullet2->getx();
				y=bullet->gety()-bullet2->gety();
				if(x<NEWSDESK_WIDTH&&x>-NEWSDESK_WIDTH&&y<NEWSDESK_HEIGHT&&y>-NEWSDESK_HEIGHT){

					if(framesave!=0){
						hp-=2;
					}
					else{
						hp--;
					}
					bullet->setusable(false);
				}
			}
		}
	}

	if(hp<=0&&counter==0){
		hp=0;
		for(iter=bulletlist->begin();iter!=bulletlist->end();iter++){
			bullet=(*iter);
			if(bullet->getusable()){
				bullet->setusable(false);
				trashlist->push_back(bullet);
			}
		}
		player->settarget(NULL);
		bullet=(*bosslist->begin());
		delete bullet;
		bosslist->clear();
		soundlist->at(3)->stopnreset();
	}

	if(framesave==0||framesave==-1){
		player->move(true);
		for(iter=bulletlist->begin();iter!=bulletlist->end();iter++){
			bullet=(*iter);
			imglist->at(bullet->getnum()+2)->draw(bullet->getx(), bullet->gety(), bullet->getradfloat(), 0xFFFFFFFF, true);
		}
		if(!bosslist->empty()){
			bullet=*bosslist->begin();
			if(bullet->getusable()){
				imglist->at(0)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
			}
			else{
				imglist->at(1)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
			}
			player->drawtarget();
		}
	}
	else{
		player->move(false);
		imglist->at(4)->draw(player->getx(), player->gety(), 0xFFFFFFFF, true);
	}

	bulletlist->remove_if(bulletconditionptrwithnondel);

	if(!trashlist->empty()){
		for(list<Bullet*>::iterator traiter=trashlist->begin();traiter!=trashlist->end();traiter++){
			bullet=*traiter;
			delete bullet;
		}
		trashlist->clear();
	}

	player->deletebullet();
	this->frame++;
	if(bosslist->empty()){
		this->counter++;
		if(counter==90)
			framesave=-1;
		if(counter>=300)
			return 1;
	}
	return 0;
}