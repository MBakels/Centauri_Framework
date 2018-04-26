#include <fstream>
#include <sstream>
#include "scene00.h"

Scene00::Scene00() : Scene() {
	woodObj = new GameObject();
	woodObj->AddSprite("assets/container.tga");
	woodObj->position = Vector2(220, 220);
	woodObj->scale = Vector2(0.7f, 0.7f);

	pencilsObj = new GameObject();
	pencilsObj->AddSprite("assets/pencils.tga");
	pencilsObj->position = Vector2(600, 100);
	pencilsObj->GetSprite()->size = Point2(300, 150);
	pencilsObj->GetSprite()->uvoffset = Point2(0.2f, 0);

	kingkongObj = new GameObject();
	kingkongObj->AddSprite("assets/kingkong.tga");
	kingkongObj->GetSprite()->Fragmentshader(DEFAULTGRAYSCALEFRAGMENTSHADER);
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
	delete woodObj;
	delete pencilsObj;
	delete kingkongObj;
}

void Scene00::Update(float deltaTime) {
	if (GetInput()->GetKey(KeyCode::EscapeKey)) {
		GetInput()->ExitApplication();
	}
}