#include "player.h"


Player::Player(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3d_dev, AudioDevicePtr aud_dev, float& size, float volume, DWORD colorkey)
{
	Image* image;
	Sound* sound;

	bulletlist=NULL;

	initialize();

	image=new Image(d3d, d3d_dev, L"res\\player\\00.png", size, colorkey);//bg
	imglist.push_back(image);
	image=new Image(d3d, d3d_dev, L"res\\player\\01.png", size, colorkey);//bg
	imglist.push_back(image);
	image=new Image(d3d, d3d_dev, L"res\\player\\03.png", size, colorkey);//bg
	imglist.push_back(image);

	sound=new Sound(aud_dev, "res\\player\\00.wav", volume);//fire
	soundlist.push_back(sound);
	sound=new Sound(aud_dev, "res\\player\\01.wav", volume);//fire
	soundlist.push_back(sound);
}


Player::~Player(void)
{
	Image* image;
	Sound* sound;
	Bullet* bullet;

	for(vector<Image*>::iterator imgiter=imglist.begin();imgiter!=imglist.end();imgiter++){
		image=*imgiter;
		delete image;
	}
	imglist.clear();
	for(vector<Sound*>::iterator snditer=soundlist.begin();snditer!=soundlist.end();snditer++){
		sound=*snditer;
		delete sound;
	}
	soundlist.clear();
	if(bulletlist!=NULL){
		for(list<Bullet*>::iterator buliter=bulletlist->begin();buliter!=bulletlist->end();buliter++){
			bullet=*buliter;
			delete bullet;
		}
		bulletlist->clear();
		delete bulletlist;
	}
}

void Player::initialize(){
	Bullet* bullet;
	target=NULL;

	radian=0;
	bulletleft=0;
	bulletdelay=0;
	shotdelay=0;
	x=400.0f;
	y=500.0f;
	deathcounter=0;
	dash=false;
	movable=false;
	keynotinput=true;
	if(bulletlist!=NULL){
		for(list<Bullet*>::iterator iter=bulletlist->begin();iter!=bulletlist->end();iter++){
			bullet=*iter;
			delete bullet;
		}
		bulletlist->clear();
	}
	else{
		bulletlist=new list<Bullet*>;
	}

}

void Player::keyinput(unsigned char key){
	if(key&MYKEY_DASH){
		if(!dashend){
			dash=true;
			bulletdelay=0;
			bulletleft=0;
			shotdelay=0;
		}
	}
	else{
		dashend=false;
		if(bulletdelay==0&&bulletleft==0){
			dash=false;
		}
	}
	if(dash){
		if(bulletdelay==0&&bulletleft==0){
			if(key&MYKEY_LEFT){
				if(key&MYKEY_UP){
					if(keynotinput){
						radian=315;
					}
					else{
						if(radian==315){
							;
						}
						else if(radian<315&&radian>135){
							radian+=RAD_PLUS;
						}
						else{
							radian-=RAD_PLUS;
							if(radian<0)
								radian+=360;
						}
					}
				}
				else if(key&MYKEY_DOWN){
					if(keynotinput){
						radian=225;
					}
					else{
						if(radian==225){
							;
						}
						else if(radian<225&&radian>45){
							radian+=RAD_PLUS;
						}
						else{
							radian-=RAD_PLUS;
							if(radian<0)
								radian+=360;
						}
					}
				}
				else{
					if(keynotinput){
						radian=270;
					}
					else{
						if(radian==270){
							;
						}
						else if(radian>90&&radian<270){
							radian+=RAD_PLUS;
						}
						else{
							radian-=RAD_PLUS;
							if(radian<0){
								radian+=360;
							}
						}
					}
				}
				keynotinput=false;
			}
			else if(key&MYKEY_RIGHT){
				if(key&MYKEY_UP){
					if(keynotinput){
						radian=45;
					}
					else{
						if(radian==45){
							;
						}
						else if(radian>45&&radian<225){
							radian-=RAD_PLUS;
						}
						else{
							radian+=RAD_PLUS;
							if(radian>=360)
								radian-=360;
						}
					}
				}
				else if(key&MYKEY_DOWN){
					if(keynotinput){
						radian=135;
					}
					else{
						if(radian==135){
							;
						}
						else if(radian>135&&radian<315){
							radian-=RAD_PLUS;
						}
						else{
							radian+=RAD_PLUS;
							if(radian>=360){
								radian-=360;
							}
						}
					}
				}
				else{
					if(keynotinput){
						radian=90;
					}
					else{
						if(radian==90){
							;
						}
						else if(radian>90&&radian<270){
							radian-=RAD_PLUS;
						}
						else{
							radian+=RAD_PLUS;
							if(radian>=360){
								radian-=360;
							}
						}
					}
				}
				keynotinput=false;
			}
			else if(key&MYKEY_UP){
				if(keynotinput){
					radian=0;
				}
				else{
					if(radian==0){
						;
					}
					else if(radian>=0&&radian<180){
						radian-=RAD_PLUS;
					}
					else{
						radian+=RAD_PLUS;
						if(radian>=360){
							radian-=360;
						}
					}
				}
				keynotinput=false;
			}
			else if(key&MYKEY_DOWN){
				if(keynotinput){
					radian=180;
				}
				else{
					if(radian==180){
						;
					}
					else if(radian>=0&&radian<180){
						radian+=RAD_PLUS;
					}
					else{
						radian-=RAD_PLUS;
					}
				}
				keynotinput=false;
			}
			else{
				keynotinput=true;
			}
		}
	}
	else{
		if(key&MYKEY_LEFT){
			movable=true;
			if(key&MYKEY_UP){
				radian=315;
			}
			else if(key&MYKEY_DOWN){
				radian=225;
			}
			else{
				radian=270;
			}
		}
		else if(key&MYKEY_RIGHT){
			movable=true;
			if(key&MYKEY_UP){
				radian=45;
			}
			else if(key&MYKEY_DOWN){
				radian=135;
			}
			else{
				radian=90;
			}
		}
		else if(key&MYKEY_UP){
			movable=true;
			radian=0;
		}
		else if(key&MYKEY_DOWN){
			movable=true;
			radian=180;
		}
		else{
			movable=false;
			keynotinput=true;
			if(target!=NULL){
				if(target->gety()==y){
					if(x<target->getx())
						radian=90;
					else
						radian=270;
				}
				else{
					float frad=atan((x-target->getx())/(target->gety()-y));
					if(y<target->gety()){
						frad+=3.141592f;
					}
					if(frad<0.0f){
						frad+=6.283185f;
					}
					radian=(int)(frad*180.0f/3.14f);
				}
			}
		}
	}
	if(key&MYKEY_SHOT){
		if(bulletleft==0&&bulletdelay==0){
			bulletleft=PLAYER_NUM;
		}
		if(dash){
			dashend=true;
			keynotinput=true;
			if(((key&0x0F)==0)&&target!=NULL){
				if(target->gety()==y){
					if(x<target->getx())
						radian=90;
					else
						radian=270;
				}
				else{
					float frad=atan((x-target->getx())/(target->gety()-y));
					if(y<target->gety()){
						frad+=3.141592f;
					}
					if(frad<0.0f){
						frad+=6.283185f;
					}
					radian=(int)(frad*180.0f/3.14f);
				}
			}
		}
	}
}

void Player::move(bool drawable){
	float radianfloat=(float)radian*3.14f/180.0f;
	if(dash){
		switch(radian){
		case 0:
			y-=DASH_VEL;
			break;
		case 45:
			x+=DASH_VEL*0.7f;
			y-=DASH_VEL*0.7f;
			break;
		case 90:
			x+=DASH_VEL;
			break;
		case 135:
			x+=DASH_VEL*0.7f;
			y+=DASH_VEL*0.7f;
			break;
		case 180:
			y+=DASH_VEL;
			break;
		case 225:
			x-=DASH_VEL*0.7f;
			y+=DASH_VEL*0.7f;
			break;
		case 270:
			x-=DASH_VEL;
			break;
		case 315:
			x-=DASH_VEL*0.7f;
			y-=DASH_VEL*0.7f;
			break;
		default:
			x+=DASH_VEL*sin(radianfloat);
			y+=DASH_VEL*-cos(radianfloat);
			break;
		}
	}
	else if(movable){
		switch(radian){
		case 0:
			y-=PLAYER_VEL;
			break;
		case 45:
			x+=PLAYER_VEL*0.7f;
			y-=PLAYER_VEL*0.7f;
			break;
		case 90:
			x+=PLAYER_VEL;
			break;
		case 135:
			x+=PLAYER_VEL*0.7f;
			y+=PLAYER_VEL*0.7f;
			break;
		case 180:
			y+=PLAYER_VEL;
			break;
		case 225:
			x-=PLAYER_VEL*0.7f;
			y+=PLAYER_VEL*0.7f;
			break;
		case 270:
			x-=PLAYER_VEL;
			break;
		case 315:
			x-=PLAYER_VEL*0.7f;
			y-=PLAYER_VEL*0.7f;
			break;
		default:
			x+=PLAYER_VEL*sin(radianfloat);
			y+=PLAYER_VEL*cos(radianfloat);
			break;
		}
	}
	setmap();

	for(list<Bullet*>::iterator i=bulletlist->begin();i!=bulletlist->end();i++){
		Bullet* bullet=*i;
		bullet->move();
		if(bullet->outofmap())
			bullet->setusable(false);
		if(drawable){
			imglist.at(bullet->getnum())->draw(bullet->getx(), bullet->gety(), bullet->getradfloat(), 0xFFFFFFFF, true);
		}
	}

	if(bulletleft!=0&&bulletdelay==0&&shotdelay==0){
		bulletleft-=1;
		if(bulletleft==0){
			shotdelay=5*PLAYER_DEL;
		}

		bulletdelay=PLAYER_DEL;
		soundlist.at(0)->play(true, false);
		if(target==NULL){
			Bullet* bullet=new Bullet(x, y, BULLET_VEL, radian, 1);
			if(drawable){
				imglist.at(bullet->getnum())->draw(bullet->getx(), bullet->gety(), bullet->getradfloat(), 0xFFFFFFFF, true);
			}
			bulletlist->push_back(bullet);
		}
		else{
			Bullet* bullet2=new Bullet(x, y, BULLET_VEL, target->getx(), target->gety(), 1);
			if(drawable){
				imglist.at(bullet2->getnum())->draw(bullet2->getx(), bullet2->gety(), bullet2->getradfloat(), 0xFFFFFFFF, true);
			}
			bulletlist->push_back(bullet2);
		}
	}
	else if(bulletdelay!=0)
		bulletdelay--;
	if(shotdelay!=0)
		shotdelay--;
	if(dashend&&bulletdelay==0&&bulletleft==0)
		dash=false;

	if(drawable){
		imglist.at(2)->draw(x, y, 0x88FFFFFF, true);
	}
	//player->draw;
}

void Player::drawtarget(){
	Image* image;
	if(target!=NULL){
		image=imglist.at(0);
		image->draw(target->getx(), target->gety(), D3DCOLOR_ARGB(127, 255, 255, 255), true);
	}
}

void Player::setmap(){
	if(x<0.0f)
		x=0.0f;
	else if(x>800.0f)
		x=800.0f;
	if(y<0.0f)
		y=0.0f;
	else if(y>600.0f)
		y=600.0f;
}

void Player::settarget(Bullet* target){
	this->target=target;
}

Bullet* Player::gettarget(){
	return target;
}

list<Bullet*>* Player::getbulletlist(){
	return bulletlist;
}

void Player::deletebullet(){
	bulletlist->remove_if(bulletconditionptr);
}

void Player::hit(){
	soundlist.at(1)->play(true, false);
	deathcounter++;
}

float Player::getx(){
	return x;
}

float Player::gety(){
	return y;
}

void Player::setvolume(float volume){
	vector<Sound*>::iterator iter;
	for(iter=soundlist.begin();iter!=soundlist.end();iter++){
		if(*iter!=NULL){
			(*iter)->setvolume(volume);
		}
	}
}