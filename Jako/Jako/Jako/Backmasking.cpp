#include "Backmasking.h"

int Backmasking::run(){
	list<Bullet*>::iterator iter;
	list<Bullet*>* pbulletlist=player->getbulletlist();
	Bullet* bullet;
	int count=0;
	float distance=0.0f;
	
	imglist->at(0)->draw(0.0f, 0.0f, 0xFFFFFFFF, false);

	if(frame==0){
		bullet=new Bullet(400.0f, -35.0f, 0.0f, 0.0f, 0);
		bullet->setinmap(true);
		bosslist->push_back(bullet);
		player->settarget(bullet);
		soundlist->at(0)->play(true);
	}
	else{
		float tx, ty;
		int bulnum;

		if(!bosslist->empty()){
			if((*bosslist->begin())->getusable()){
				tx=(*bosslist->begin())->getx()-player->getx();
				ty=(*bosslist->begin())->gety()-player->gety();

				if(ty*ty+tx*tx<ARBITER_RAN){
					player->hit();
				}
			}
		}
		
		for(iter=player->getbulletlist()->begin();iter!=player->getbulletlist()->end();iter++){
			if(!bosslist->empty()){
				if((*bosslist->begin())->getusable()){
					bullet=(*iter);
					if(bullet->getusable()){
						tx=(*bosslist->begin())->getx()-bullet->getx();
						ty=(*bosslist->begin())->gety()-bullet->gety();

						if(-15.0f<tx&&tx<15.0f){
							if(ty*ty+tx*tx<ARBITER_RAN){
								hp-=2;
								bullet->setusable(false);
								if(hp<=0){
									(*bosslist->begin())->setusable(false);
									(*bosslist->begin())->setnum(27);
									player->settarget(NULL);
								}
							}
						}
					}
				}
			}
		}
		for(iter=bulletlist->begin();iter!=bulletlist->end();iter++){
			bullet=(*iter);
			bullet->move();
			tx=player->getx()-bullet->getx();
			ty=player->gety()-bullet->gety();
			bulnum=bullet->getnum();

			if(-15.0f<tx&&tx<15.0f){
				if(ty*ty+tx*tx<BULLET_RAN){
					player->hit();
				}
			}
			imglist->at(bulnum+27)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
			if(bulnum==0){
				bullet->setnum(4);
			}
			else{
				bullet->setnum(bulnum-1);
			}
		}
		for(iter=spritelist->begin();iter!=spritelist->end();iter++){
			bullet=(*iter);
			bullet->move();
			tx=player->getx()-bullet->getx();
			ty=player->gety()-bullet->gety();
			bulnum=bullet->getnum();

			if(-15.0f<tx&&tx<15.0f){
				if(ty*ty+tx*tx<BULLET_RAN){
					player->hit();
				}
			}
			tx=(*bosslist->begin())->getx()-bullet->getx();
			ty=(*bosslist->begin())->gety()-bullet->gety();

			if(-25.0f<tx&&tx<25.0f){
				if(ty*ty+tx*tx<ARBITER_RAN){
					bullet->setusable(false);
					bullet->setvel(BACKMASKING_BULLET_VEC+((float)(rand()%1000))*0.0015f, rand()%360);
					bulletlist->push_back(bullet);
				}
				else{
					bullet->setvel(bullet->getx(), bullet->gety(), BACKMASKING_BULLET_FAST_VEC, (*bosslist->begin())->getx(), (*bosslist->begin())->gety());
				}
			}
			else{
				bullet->setvel(bullet->getx(), bullet->gety(), BACKMASKING_BULLET_FAST_VEC, (*bosslist->begin())->getx(), (*bosslist->begin())->gety());
			}

			imglist->at(bullet->getnum()+27)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);

			if(bulnum==0){
				bullet->setnum(4);
			}
			else{
				bullet->setnum(bulnum-1);
			}
		}
		if(!bosslist->empty()){
			bullet=*bosslist->begin();
			if(bullet->getusable()){
				if(bullet->outofmap(0.0f, 0.0f)){
					bullet->setvel(bullet->getx(), bullet->gety(), ARBITER_VEC, 400.0f, 300.0f);
					bullet->setrad();
					bullet->setnum(rand()%45+120);
				}
				else if(bullet->getnum()<=0){
					bullet->setvel(ARBITER_VEC, rand()%360);
					bullet->setrad();
					bullet->setnum(rand()%600);
				}
				bullet->move();
				count=bullet->getradint()*8/45;
				switch(count){
				case 1:
				case 2:
					imglist->at(2)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 3:
				case 4:
					imglist->at(3)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 5:
				case 6:
					imglist->at(4)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 7:
				case 8:
					imglist->at(5)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 9:
				case 10:
					imglist->at(6)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 11:
				case 12:
					imglist->at(7)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 13:
				case 14:
					imglist->at(8)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 15:
				case 16:
					imglist->at(9)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 17:
				case 18:
					imglist->at(10)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 19:
				case 20:
					imglist->at(11)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 21:
				case 22:
					imglist->at(12)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 23:
				case 24:
					imglist->at(13)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 25:
				case 26:
					imglist->at(14)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 27:
				case 28:
					imglist->at(15)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 29:
				case 30:
					imglist->at(16)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 31:
				case 32:
					imglist->at(17)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				case 33:
				case 34:
					imglist->at(16)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 35:
				case 36:
					imglist->at(15)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 37:
				case 38:
					imglist->at(14)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 39:
				case 40:
					imglist->at(13)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 41:
				case 42:
					imglist->at(12)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 43:
				case 44:
					imglist->at(11)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 45:
				case 46:
					imglist->at(10)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 47:
				case 48:
					imglist->at(9)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 49:
				case 50:
					imglist->at(8)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 51:
				case 52:
					imglist->at(7)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 53:
				case 54:
					imglist->at(6)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 55:
				case 56:
					imglist->at(5)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 57:
				case 58:
					imglist->at(4)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 59:
				case 60:
					imglist->at(3)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				case 61:
				case 62:
					imglist->at(2)->draw(bullet->getx(), bullet->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
					break;
				default:
					imglist->at(1)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
					break;
				}
			}
			else{
				if(!bulletlist->empty()){
					for(iter=bulletlist->begin();iter!=bulletlist->end();iter++){
						trashlist->push_back(*iter);
					}
					bulletlist->clear();
				}
				if(!spritelist->empty()){
					for(iter=spritelist->begin();iter!=spritelist->end();iter++){
						if((*iter)->getusable())
							trashlist->push_back(*iter);
					}
					spritelist->clear();
				}
				if(bullet->getnum()==1){
					bosslist->clear();
					trashlist->push_back(bullet);
				}
				soundlist->at(1)->stopnreset();
				soundlist->at(2)->stopnreset();
				counter=(bullet->getnum()+2)/3+17;
				imglist->at(counter)->draw(bullet->getx(), bullet->gety(), 0xFFFFFFFF, true);
			}
			bullet->setnum(bullet->getnum()-1);

			if(frame==BACKMASKING_START_FRAME){
				for(int i=0;i<150;i++){
					bulletlist->push_back(new Bullet(bullet->getx(), bullet->gety(), BACKMASKING_BULLET_VEC+((float)(rand()%1000))*0.0015f, rand()%360, 4));
				}
				soundlist->at(1)->play(false);
			}
			else if(!bulletlist->empty()&&frame%BACKMASKING_WAIT_FRAME==BACKMASKING_FRAME){
				for(iter=bulletlist->begin();iter!=bulletlist->end();iter++){
					(*iter)->setusable(true);
					spritelist->push_back(*iter);
				}
				bulletlist->clear();
				soundlist->at(2)->play(true, false);
			}
		}
	}

	spritelist->remove_if(bulletconditionptrwithnondel);
	
	if(!trashlist->empty()){
		for(list<Bullet*>::iterator traiter=trashlist->begin();traiter!=trashlist->end();traiter++){
			bullet=*traiter;
			delete bullet;
		}
		trashlist->clear();
	}

	player->move(true);
	player->deletebullet();
	this->frame++;
	player->drawtarget();
	if(bosslist->empty()){
		this->counter++;
		if(counter>=300)
			return 1;
	}
	return 0;
}