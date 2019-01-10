#include <fstream>
#include <sstream>
#include "scene02.h"

Scene02::Scene02() : MasterScene() {
	circle10 = new GameObject();
	circle10->AddBasicShape()->CreateCircle(80, 10);
	circle10->position = Vector3(200, SHEIGHT / 2, 0);
	circle10->GetBasicShape()->color = RED;

	circle50 = new GameObject();
	circle50->AddBasicShape()->CreateCircle(150, 50);
	circle50->position = Vector3(SWIDTH / 2, SHEIGHT / 2, 0);
	circle50->GetBasicShape()->color = BLUE;

	triangle = new GameObject();
	triangle->AddBasicShape()->CreateTriangle(160);
	triangle->position = Vector3(SWIDTH - 200, SHEIGHT / 2, 0);
	triangle->GetBasicShape()->color = CYAN;

	AddChild(circle10);
	AddChild(circle50);
	AddChild(triangle);

	sceneText = new GameObject();
	sceneText->position = Vector3(10, 30, 1);
	sceneText->AddText("Demo scene 02 | BasicShape demo\nSwitch scenes with the [ ] keys", "fonts/acari-sans/AcariSans-Regular.ttf");
	AddChild(sceneText);
}

Scene02::~Scene02() {
	RemoveChild(circle10);
	RemoveChild(circle50);
	RemoveChild(triangle);
	RemoveChild(sceneText);
	delete circle10;
	delete circle50;
	delete triangle;
	delete sceneText;
}

void Scene02::Update() {
	MasterScene::Update();
}