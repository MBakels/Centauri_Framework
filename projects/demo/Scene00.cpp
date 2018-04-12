#include <fstream>
#include <sstream>
#include "scene00.h"

Scene00::Scene00() : Scene() {
	// Create sprites
	wood = new Sprite("assets/container.tga");
	pencils = new Sprite("assets/pencils.tga");
	kingkong = new Sprite("assets/kingkong.tga");

	woodObj = new GameObject();
	woodObj->addSprite(wood);
	woodObj->position = Vector2(220, 220);
	woodObj->scale = Vector2(0.7f, 0.7f);

	pencilsObj = new GameObject();
	pencilsObj->addSprite(pencils);
	pencilsObj->position = Vector2(500, 100);

	kingkongObj = new GameObject();
	kingkongObj->addSprite(kingkong);
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
	delete wood;
	delete pencils;
	delete kingkong;
	delete woodObj;
	delete pencilsObj;
	delete kingkongObj;
}

void Scene00::Update(float deltaTime) {

}