#include <fstream>
#include <sstream>
#include "scene03.h"

Scene03::Scene03() : MasterScene() {
	circle = new GameObject();
	circle->AddSpriteSheet("assets/face.tga", 4, 4);
	//circle->GetSprite()->Frame(0);
	circle->GetSprite()->IsAnimated(true);
	circle->GetSprite()->Fps(10);
	circle->position = Vector3(SWIDTH / 2, SHEIGHT / 2, 0);

	AddChild(circle);
}

Scene03::~Scene03() {
	RemoveChild(circle);
	delete circle;
}

void Scene03::Update(float deltaTime) {
	MasterScene::Update(deltaTime);
}