#include <fstream>
#include <sstream>
#include "scene01.h"

#include "font.h"

Scene01::Scene01() : MasterScene() {
	woodObj = new GameObject();
	woodObj->AddSprite("assets/container.tga");
	woodObj->position = Vector3(450, 220, 0);
	woodObj->scale = Vector3(0.7f, 0.7f, 1);

	pencilsObj = new GameObject();
	pencilsObj->AddSprite("assets/pencils.tga");
	pencilsObj->position = Vector3(600, 200, 5);
	pencilsObj->GetSprite()->size = Point2(300, 150);
	pencilsObj->GetSprite()->uvoffset = Point2(0.2f, 0);

	kingkongObj = new GameObject();
	kingkongObj->AddSprite("assets/kingkong.tga");
	kingkongObj->GetSprite()->Fragmentshader(DEFAULTGRAYSCALEFRAGMENTSHADER);
	kingkongObj->position = Vector3(750, 500, -10);
	kingkongObj->scale = Vector3(2.0f, 2.0f, 1);

	grassObj = new GameObject();
	grassObj->AddSprite("assets/grass.tga");
	grassObj->position = Vector3(500, 220, 3);

	AddChild(woodObj);
	AddChild(pencilsObj);
	AddChild(kingkongObj);
	AddChild(grassObj);

	Font* font = new Font("fonts/acari-sans/AcariSans-Regular.ttf");
	GameObject* textTest = new GameObject();
	//textTest->AddSprite("assets/pencils.tga");
	//textTest->GetSprite()->size = Point2(100, 20);
	textTest->position = Vector3(80, 80, 1);
	textTest->AddText("testing", font);
	AddChild(textTest);

}

Scene01::~Scene01() {
	RemoveChild(woodObj);
	RemoveChild(pencilsObj);
	RemoveChild(kingkongObj);
	RemoveChild(grassObj);
	delete woodObj;
	delete pencilsObj;
	delete kingkongObj;
	delete grassObj;
}

void Scene01::Update(float deltaTime) {
	MasterScene::Update(deltaTime);
}