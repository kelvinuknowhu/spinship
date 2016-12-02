#include <math.h>
#include "Vector2.hpp"
#include "LTexture.hpp"

#ifndef GRAVITY_H
#define GRAVITY_H value

#define PI 3.14159265

class Gravity : public LTexture
{
public:
	Gravity(Vector2 position, int size, int nframes = 1):LTexture(nframes){
		this->position = position;
		this->size = size;
		this->gravity_level = 10 * size;
		this->angle_co = PI / 180.0f;
		this->angle = 0;
	}
	void update(Leader *element, float ticks);
	void update(Bullet *element, float ticks);
	void update(float ticks);
	Vector2 position;

private:
	int size;
	int gravity_level;
	float angle_co;

};

void Gravity::update(Leader *element, float ticks = 1){
	float distance = position.Distance(element->position)/30;
	Vector2 temp = position - element->position;
	if (temp.Length() > 10){
		element->position += temp * (gravity_level / (distance * distance)) * ticks * 0.5;
	}
}

void Gravity::update(Bullet *element, float ticks = 1){
	float distance = position.Distance(element->position)/30;
	Vector2 temp = position - element->position;
	if (temp.Length() > 10){
		element->position += temp * (gravity_level / (distance * distance)) * ticks;
	}
}

void Gravity::update(float ticks = 1){
	angle -= ticks * angle_co * 1000;
}

#endif