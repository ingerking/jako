#include "Resolver.h"

int Resolver::run(){
	list<Bullet*>::iterator iter;
	list<Bullet*>* pbulletlist=player->getbulletlist();
	Bullet* bullet;
	int count=0;
	float distance=0.0f;
	
	imglist->at(0)->draw(0.0f, 0.0f, 0xFFFFFFFF, false);

	if(frame==0){
		hp=0;
		for(int i=0;i<31;i++){
			bullet=new Bullet(0.0f, (float)(i*20), WRAITH_VEC, 400.0f, 300.0f, 0);
			bulletlist->push_back(bullet);
			bullet=new Bullet(800.0f, (float)(i*20), WRAITH_VEC, 400.0f, 300.0f, 0);
			bulletlist->push_back(bullet);
		}
		for(int i=0;i<21;i++){
			bullet=new Bullet((float)(i*40), 0.0f, WRAITH_VEC, 400.0f, 300.0f, 0);
			bulletlist->push_back(bullet);
		}
		player->settarget(*(bulletlist->begin()));
		soundlist->at(0)->play(true);
	}
	else if(frame>0&&frame<START_FRAME){
		for(iter=bulletlist->begin();iter!=bulletlist->end();iter++){
			if((*iter)->getusable()){
				(*iter)->setvel((*iter)->getx(), (*iter)->gety(), WRAITH_VEC, 400.0f, 300.0f);
			}
		}
	}
	else if(frame==START_FRAME){
		for(iter=bulletlist->begin();iter!=bulletlist->end();iter++){
			if((*iter)->getusable()){
				(*iter)->setvel(WRAITH_VEC, rand()%360);
				(*iter)->setrad();
				(*iter)->setnum(rand()%600);
			}
		}
	}
	
	for(iter=spritelist->begin();iter!=spritelist->end();iter++){
		if((*iter)->getnum()==1){
			trashlist->push_back(*iter);
		}
		counter=((*iter)->getnum()+2)/3+17;
		imglist->at(counter)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);

		(*iter)->setnum((*iter)->getnum()-1);
	}
	
	for(iter=bulletlist->begin();iter!=bulletlist->end();iter++){
		float disx, disy, tempdis;
		if((*iter)->getusable()){
			if(frame>=START_FRAME){
				if((*iter)->outofmap(0.0f, 0.0f)){
					(*iter)->setvel((*iter)->getx(), (*iter)->gety(), WRAITH_VEC, 400.0f, 300.0f);
					(*iter)->setrad();
					(*iter)->setnum(rand()%45);
				}
				if((*iter)->getnum()<=0){
					(*iter)->setvel(WRAITH_VEC, rand()%360);
					(*iter)->setrad();
					(*iter)->setnum(rand()%600);
				}
			}
			disx=(*iter)->getx()-player->getx();
			disy=(*iter)->gety()-player->gety();
			tempdis=disx*disx+disy*disy;
			if(tempdis<WRAITH_RAN){
				if((*iter)==player->gettarget()){
					player->settarget(NULL);
				}
				(*iter)->setusable(false);
				(*iter)->setnum(27);
				spritelist->push_back((*iter));
				player->hit();
				soundlist->at(1)->play(true, false);
			}
			for(list<Bullet*>::iterator iter2=pbulletlist->begin();iter2!=pbulletlist->end();iter2++){
				if((*iter2)->getusable()){
					disx=(*iter)->getx()-(*iter2)->getx();
					disy=(*iter)->gety()-(*iter2)->gety();
					tempdis=disx*disx+disy*disy;
					if(tempdis<WRAITH_RAN){
						if((*iter)==player->gettarget()){
							player->settarget(NULL);
						}
						(*iter)->setusable(false);
						(*iter)->setnum(27);
						(*iter2)->setusable(false);
						spritelist->push_back((*iter));
						soundlist->at(1)->play(true, false);
					}
				}
			}
			(*iter)->move();

			count=(*iter)->getradint()*8/45;
			switch(count){
			case 1:
			case 2:
				imglist->at(2)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 3:
			case 4:
				imglist->at(3)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 5:
			case 6:
				imglist->at(4)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 7:
			case 8:
				imglist->at(5)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 9:
			case 10:
				imglist->at(6)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 11:
			case 12:
				imglist->at(7)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 13:
			case 14:
				imglist->at(8)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 15:
			case 16:
				imglist->at(9)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 17:
			case 18:
				imglist->at(10)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 19:
			case 20:
				imglist->at(11)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 21:
			case 22:
				imglist->at(12)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 23:
			case 24:
				imglist->at(13)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 25:
			case 26:
				imglist->at(14)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 27:
			case 28:
				imglist->at(15)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 29:
			case 30:
				imglist->at(16)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 31:
			case 32:
				imglist->at(17)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			case 33:
			case 34:
				imglist->at(16)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 35:
			case 36:
				imglist->at(15)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 37:
			case 38:
				imglist->at(14)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 39:
			case 40:
				imglist->at(13)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 41:
			case 42:
				imglist->at(12)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 43:
			case 44:
				imglist->at(11)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 45:
			case 46:
				imglist->at(10)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 47:
			case 48:
				imglist->at(9)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 49:
			case 50:
				imglist->at(8)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 51:
			case 52:
				imglist->at(7)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 53:
			case 54:
				imglist->at(6)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 55:
			case 56:
				imglist->at(5)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 57:
			case 58:
				imglist->at(4)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 59:
			case 60:
				imglist->at(3)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			case 61:
			case 62:
				imglist->at(2)->draw((*iter)->getx(), (*iter)->gety(), 0.0f, -1.0f, 1.0f, 0xFFFFFFFF, true);
				break;
			default:
				imglist->at(1)->draw((*iter)->getx(), (*iter)->gety(), 0xFFFFFFFF, true);
				break;
			}
		}
		
		if(!bulletlist->empty()){
			if(player->gettarget()==NULL){
				for(list<Bullet*>::iterator iter3=bulletlist->begin();iter3!=bulletlist->end();iter3++){
					if((*iter3)->getusable()){
						player->settarget(*iter3);
						break;
					}
				}
			}
		}
		(*iter)->setnum((*iter)->getnum()-1);
	}
	
	bulletlist->remove_if(bulletconditionptrwithnondel);
	spritelist->remove_if(bulletconditionwithzerowithnondel);
	
	for(list<Bullet*>::iterator traiter=trashlist->begin();traiter!=trashlist->end();traiter++){
		bullet=*traiter;
		delete bullet;
	}
	trashlist->clear();

	player->move(true);
	player->deletebullet();
	this->frame++;
	player->drawtarget();
	if(bulletlist->empty()){
		this->counter++;
		if(counter>=300)
			return 1;
	}
	return 0;
}