#ifndef LASER_H
#define LASER_H

#include "gameobject.h"

class Laser : public GameObject {
public:
	Laser(Point3 pos);
	virtual ~Laser();

	virtual void Update();

private:
	float speed;
};

#endif