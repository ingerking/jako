#include "bullet.h"


Bullet::Bullet(float x, float y, float vx, float vy, int num){
	this->x=x;
	this->y=y;
	this->vx=vx;
	this->vy=vy;
	this->ax=0.0f;
	this->ay=0.0f;
	this->num=num;
	inmap=false;
	usable=true;
}

Bullet::Bullet(float x, float y, float vec, float tx, float ty, int num){
	float frad=0.0f;
	if(ty==y){
		if(x<tx)
			frad=3.14159f/2.0f;
		else
			frad=3.14159f*1.5f;
	}
	else{
		frad=atan((x-tx)/(ty-y));
		if(y<ty){
			frad+=3.141592f;
		}
		if(frad<0.0f){
			frad+=6.283185f;
		}
	}
	this->x=x;
	this->y=y;
	this->vx=vec*sin(frad);
	this->vy=vec*-cos(frad);
	this->ax=0.0f;
	this->ay=0.0f;
	this->num=num;
	this->rad=frad;
	inmap=false;
	usable=true;
}

Bullet::Bullet(float x, float y, float vec, float acc, float tx, float ty, int num){
	float frad=0.0f;
	if(ty==y){
		if(x<tx)
			frad=3.14159f/2.0f;
		else
			frad=3.14159f*1.5f;
	}
	else{
		frad=atan((x-tx)/(ty-y));
		if(y<ty){
			frad+=3.141592f;
		}
		if(frad<0.0f){
			frad+=6.283185f;
		}
	}
	this->x=x;
	this->y=y;
	this->vx=vec*sin(frad);
	this->ax=acc*sin(frad);
	this->vy=vec*-cos(frad);
	this->ay=acc*-cos(frad);
	this->num=num;
	this->rad=frad;
	inmap=false;
	usable=true;
}

Bullet::Bullet(float x, float y, float vec, int rad, float acc, int arad, int num){
	float frad=(float)rad*3.14f/180.0f;
	float farad=(float)arad*3.14f/180.0f;
	this->x=x;
	this->y=y;
	this->vx=vec*sin(frad);
	this->vy=vec*-cos(frad);
	this->ax=acc*sin(farad);
	this->ay=acc*-cos(farad);
	this->num=num;
	this->rad=frad;
	inmap=false;
	usable=true;
}

Bullet::Bullet(float x, float y, float vec, int rad, int num){
	float frad=(float)rad*3.14f/180.0f;
	this->x=x;
	this->y=y;
	this->vx=vec*sin(frad);
	this->vy=vec*-cos(frad);
	this->ax=0.0f;
	this->ay=0.0f;
	this->num=num;
	this->rad=frad;
	inmap=false;
	usable=true;
}

Bullet::~Bullet(void)
{
	return;
}

void Bullet::move(){
	x+=vx;
	y+=vy;
	vx+=ax;
	vy+=ay;
}

int Bullet::getnum(){
	return num;
}

void Bullet::setnum(int num){
	this->num=num;
}

float Bullet::getx(){
	return x;
}

float Bullet::gety(){
	return y;
}

void Bullet::setvel(float vx, float vy){
	this->vx=vx;
	this->vy=vy;
}

void Bullet::setvel(float x, float y, float vec, float tx, float ty){
	float frad=0.0f;
	if(ty==y){
		if(x<tx)
			frad=3.14159f/2.0f;
		else
			frad=3.14159f*1.5f;
	}
	else{
		frad=atan((x-tx)/(ty-y));
		if(y<ty){
			frad+=3.141592f;
		}
		if(frad<0.0f){
			frad+=6.283185f;
		}
	}
	this->vx=vec*sin(frad);
	this->vy=vec*-cos(frad);
	this->rad=frad;
}

void Bullet::setvel(float vec, int rad){
	float frad=(float)rad*3.14f/180.0f;
	this->vx=vec*sin(frad);
	this->vy=vec*-cos(frad);
}

void Bullet::setacc(float ax, float ay){
	this->ax=ax;
	this->ay=ay;
}

void Bullet::setacc(float x, float y, float acc, float tx, float ty){
	float frad=0.0f;
	if(ty==y){
		if(x<tx)
			frad=3.14159f/2.0f;
		else
			frad=3.14159f*1.5f;
	}
	else{
		frad=atan((x-tx)/(ty-y));
		if(y<ty){
			frad+=3.141592f;
		}
		if(frad<0.0f){
			frad+=6.283185f;
		}
	}
	this->ax=acc*sin(frad);
	this->ay=acc*-cos(frad);
}

void Bullet::setacc(float acc, int arad){
	float farad=(float)arad*3.14f/180.0f;
	this->ax=acc*sin(farad);
	this->ay=acc*-cos(farad);
}

int Bullet::getradint(){
	return (int)(rad*180.0f/3.14f);
}

float Bullet::getradfloat(){
	return rad;
}

void Bullet::setrad(){
	float frad=0.0f;
	if(vy==0.0f){
		if(0.0f<vx)
			frad=3.14159f/2.0f;
		else
			frad=3.14159f*1.5f;
	}
	else{
		frad=atan(-vx/vy);
		if(0.0f<vy){
			frad+=3.141592f;
		}
		if(frad<0.0f){
			frad+=6.283185f;
		}
	}
	rad=frad;
}

bool Bullet::getinmap(){
	return inmap;
}

bool Bullet::getusable(){
	return usable;
}

void Bullet::setinmap(bool inmap){
	this->inmap=inmap;
}

void Bullet::setusable(bool usable){
	this->usable=usable;
}

bool Bullet::outofmap(){
	if(inmap){
		if(x<-50.0f||x>850.0f||y<-50.0f||y>650.0f){
			return true;
		}
	}
	else{
		if(x>=-50.0f&&x<=850.0f){
			if(y>=-50.0f&&y<=650.0f){
				inmap=true;
			}
		}
	}
	return false;
}

bool Bullet::outofmap(float fx, float fy){
	if(inmap){
		if(x<-fx||x>800.0f+fx||y<-fy||y>600.0f+fy){
			return true;
		}
	}
	else{
		if(x>=-fx&&x<=800.0f+fx){
			if(y>=-fy&&y<=600.0f+fy){
				inmap=true;
			}
		}
	}
	return false;
}

void Bullet::setoutofmap(){
	if(inmap){
		if(x<-50.0f||x>850.0f||y<-50.0f||y>650.0f){
			usable=false;
			return;
		}
	}
	else{
		if(x>=-50.0f&&x<=850.0f){
			if(y>=-50.0f&&y<=650.0f){
				inmap=true;
			}
		}
	}
	usable=true;	
}

void Bullet::setoutofmap(float fx, float fy){
	if(inmap){
		if(x<-fx||x>800.0f+fx||y<-fy||y>600.0f+fy){
			usable=false;
			return;
		}
	}
	else{
		if(x>=-fx&&x<=800.0f+fx){
			if(y>=-fy&&y<=600.0f+fy){
				inmap=true;
			}
		}
	}
	usable=true;	
}





bool bulletcondition(Bullet bullet){
	if(!bullet.getusable()){
		return true;
	}
	return false;
}

bool bulletconditionptr(Bullet* bullet){
	if(!bullet->getusable()){
		delete bullet;
		return true;
	}
	return false;
}

bool bulletconditionwithzero(Bullet* bullet){
	if(!bullet->getusable()){
		if(bullet->getnum()==0){
			delete bullet;
			return true;
		}
	}
	return false;
}

bool bulletconditionptrwithnondel(Bullet* bullet){
	if(!bullet->getusable()){
		return true;
	}
	return false;
}

bool bulletconditionwithzerowithnondel(Bullet* bullet){
	if(!bullet->getusable()){
		if(bullet->getnum()==0){
			return true;
		}
	}
	return false;
}