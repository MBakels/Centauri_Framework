#include <fstream>
#include <sstream>
#include "scene02.h"

Scene02::Scene02() : MasterScene() {
	circle10 = new GameObject();
	circle10->AddBasicShape()->CreateCircle(80, 10);
	circle10->position = Vector3(200, SHEIGHT / 2, 0);

	circle50 = new GameObject();
	circle50->AddBasicShape()->CreateCircle(150, 50);
	circle50->position = Vector3(SWIDTH / 2, SHEIGHT / 2, 0);

	triangle = new GameObject();
	triangle->AddBasicShape()->CreateTriangle(160);
	triangle->position = Vector3(SWIDTH - 200, SHEIGHT / 2, 0);

	AddChild(circle10);
	AddChild(circle50);
	AddChild(triangle);
}

Scene02::~Scene02() {
	RemoveChild(circle10);
	RemoveChild(circle50);
	RemoveChild(triangle);
	delete circle10;
	delete circle50;
	delete triangle;
}

void Scene02::Update(float deltaTime) {
	MasterScene::Update(deltaTime);
}