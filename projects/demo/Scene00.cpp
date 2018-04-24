#include <fstream>
#include <sstream>
#include "scene00.h"

Scene00::Scene00() : Scene() {
	woodObj = new GameObject();
	woodObj->addSprite("assets/container.tga");
	woodObj->position = Vector2(220, 220);
	woodObj->scale = Vector2(0.7f, 0.7f);

	pencilsObj = new GameObject();
	pencilsObj->addSprite("assets/pencils.tga");
	pencilsObj->position = Vector2(600, 100);
	pencilsObj->sprite()->size = Point2(300, 150);
	pencilsObj->sprite()->uvoffset = Point2(0.2f, 0);

	kingkongObj = new GameObject();
	kingkongObj->addSprite("assets/kingkong.tga");
	kingkongObj->position = Vector2(750, 500);
	kingkongObj->scale = Vector2(2.0f, 2.0f);

	addChild(woodObj);
	addChild(pencilsObj);
	addChild(kingkongObj);
}

Scene00::~Scene00() {
	removeChild(woodObj);
	removeChild(pencilsObj);
	removeChild(kingkongObj);
	delete woodObj;
	delete pencilsObj;
	delete kingkongObj;
}

void Scene00::update(float deltaTime) {
	if (input()->getKey(KeyCode::EscapeKey)) {
		input()->exitApplication();
	}
}