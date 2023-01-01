#pragma once
#include <math.h>
class Bullet
{
private:
	float x;
	float y;
	float vx;
	float vy;
	float ax;
	float ay;
	float rad;
	int num;
	bool inmap;
	bool usable;
public:
	Bullet(float x, float y, float vx, float vy, int num);
	Bullet(float x, float y, float vec, float tx, float ty, int num);
	Bullet(float x, float y, float vec, float acc, float tx, float ty, int num);
	Bullet(float x, float y, float vec, int rad, float acc, int arad, int num);
	Bullet(float x, float y, float vec, int rad, int num);
	~Bullet(void);
	void move();
	int getnum();
	void setnum(int num);
	float getx();
	float gety();
	void setvel(float vx, float vy);
	void setvel(float x, float y, float vec, float tx, float ty);
	void setvel(float vec, int rad);
	void setacc(float ax, float ay);
	void setacc(float x, float y, float acc, float tx, float ty);
	void setacc(float acc, int arad);
	int getradint();
	float getradfloat();
	void setrad();
	bool getinmap();
	bool getusable();
	void setinmap(bool inmap);
	void setusable(bool usable);
	bool outofmap();
	bool outofmap(float fx, float fy);
	void setoutofmap();
	void setoutofmap(float fx, float fy);
};

bool bulletcondition(Bullet bullet);

bool bulletconditionptr(Bullet* bullet);

bool bulletconditionwithzero(Bullet* bullet);

bool bulletconditionptrwithnondel(Bullet* bullet);

bool bulletconditionwithzerowithnondel(Bullet* bullet);