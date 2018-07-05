#include "Unit.h"
#include <string>
#pragma once


Unit::Unit(int length, int speed, int lifes)
{
	setLife(lifes);
	setSpeed(speed);
	this->length = length;
	this->dimensionX = 2 * length;
	this->dimensionY = length;
	this->name = "unit" + std::to_string(Unit::number);
	Unit::number++;
}

Unit::~Unit()
{
	setLife(3);
	setSpeed(400);
}



void Unit::setLife(int lifes)
{
	this->life = lifes;
}


int Unit::getLifes()
{
	return this->life;
}


void Unit::setSpeed(int speed)
{
	this->speed = speed;
}

int Unit::getSpeed()
{
	return this->speed;
}

//used for projectile-enemies
bool Unit::Collide(projectile* u)
{
	bool collide = false;
	if (this->x + this->length > u->x && this->x - this->length < u->x)
	{
		if (this->y + this->length > u->y && this->y - this->length < u->y)
		{
			u->x = -1;
			this->life -= 1;
			if (this->life == 1)
			{
				this->length *= 0.5;
			}

			return true;
		}
	}

	return collide;
}

//used for players
bool Unit::Collide(Unit* u)
{
	bool collide = false;
	if (this->x + this->length > u->x && this->x - this->length < u->x)
	{
		if (this->y + this->length > u->y && this->y - this->length < u->y)
		{
			u->setCoord(-1, -1);
			this->life -= 1;
			return true;
		}
	}

	return collide;
}

void Unit::Fire(int direction)
{
}

std::string Unit::getName()
{
	return this->name;
}

void Unit::setCoord(int x, int y)
{
	this->x = x;
	this->y = y;
}
void Unit::setX(int x)
{
	this->x = x;
}
void Unit::setY(int x)
{
	this->y = x;
}
void Unit::addX(int x)
{
	this->x += x;
}
void Unit::addY(int x)
{
	this->y += x;
}
int* Unit::getCoord()
{
	int coord[2];
	coord[0] = this->x;
	coord[1] = this->y;
	return coord;
}

Unit::projectile Unit::projectile::create(int x, int y, int i, int cx, int cy)
{
	projectile p = projectile(x, y, i, cx, cy);
	return p;
}
