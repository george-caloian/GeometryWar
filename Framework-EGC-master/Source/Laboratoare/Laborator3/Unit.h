#pragma once
#include <string>
class Unit
{
public:
	static int number;
	Unit(int length, int speed, int lifes);
	~Unit();
	struct projectile
	{
		int x;
		int y;
		float angle;
		std::string names;
		projectile(int x, int y, int i, int cx, int cy) :
			x(x),
			y(y),
			names("projectile" + std::to_string(i)),
			angle(atan2(-float(cy - y), float(cx - x)))
		{}
		~projectile() {}
		projectile create(int x, int y, int i, int cx, int cy);
	};


private:

	float x;
	float y;
	int life;
	int speed;
	int dimensionX;
	int dimensionY;

	std::string name;

public:

	int length;
	float angle;
	void setLife(int lifes);
	int getLifes();
	void setSpeed(int speed);
	int getSpeed();
	bool Collide(Unit::projectile* u);
	bool Collide(Unit* u);
	void Fire(int direction);
	std::string getName();
	void setCoord(int x, int y);
	void setX(int x);
	void setY(int y);
	void addX(int x);
	void addY(int y);
	int* getCoord();




};

