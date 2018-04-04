#include <fstream>
#include <sstream>
#include "scene00.h"

Scene00::Scene00() : Scene() {
	// Create sprites
	wood = new Sprite("assets/container.tga");
	pencils = new Sprite("assets/pencils.tga");
	kingkong = new Sprite("assets/kingkong.tga");

	woodObj = new GameObject();
	woodObj->AddSprite(wood);
	woodObj->position = Vector2(220, 220);
	woodObj->scale = Vector2(0.7f, 0.7f);

	pencilsObj = new GameObject();
	pencilsObj->AddSprite(pencils);
	pencilsObj->position = Vector2(500, 100);

	kingkongObj = new GameObject();
	kingkongObj->AddSprite(kingkong);
	kingkongObj->position = Vector2(750, 500);
	kingkongObj->scale = Vector2(2.0f, 2.0f);

	AddChild(woodObj);
	AddChild(pencilsObj);
	AddChild(kingkongObj);
}

Scene00::~Scene00() {
	RemoveChild(woodObj);
	RemoveChild(pencilsObj);
	RemoveChild(kingkongObj);
	delete wood;
	delete pencils;
	delete kingkong;
	delete woodObj;
	delete pencilsObj;
	delete kingkongObj;
}

void Scene00::Update(float deltaTime) {

}