#ifndef PINGUIN_H
#define PINGUIN_H

#include "gameobject.h"

class Pinguin : public GameObject {
public:
	Pinguin();
	virtual ~Pinguin();

	virtual void Update();

	void MoveTo(Point2 tilePos, Vector2 direction);

	bool IsMoving() { return (moveDirection != Vector2(0, 0)) ? true : false; };

	int x, y;

private:
	Vector2 moveDirection;
	Point2 targetPos;
	int moveSpeed;

	void TargetPosReached();

};

#endif
