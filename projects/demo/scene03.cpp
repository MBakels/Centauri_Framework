#include <fstream>
#include <sstream>
#include "scene03.h"

Scene03::Scene03() : MasterScene() {
	animatedFace = new GameObject();
	animatedFace->AddSpriteSheet("assets/face.tga", 4, 4);
	animatedFace->GetSprite()->IsAnimated(true);
	animatedFace->GetSprite()->Fps(10);
	animatedFace->position = Vector3(SWIDTH / 2, SHEIGHT / 2, 0);

	AddChild(animatedFace);

	sceneText = new GameObject();
	sceneText->position = Vector3(10, 30, 1);
	sceneText->AddText("Demo scene 03 | Animated sprite demo\nSwitch scenes with the [ ] keys", "fonts/acari-sans/AcariSans-Regular.ttf");
	AddChild(sceneText);
}

Scene03::~Scene03() {
	RemoveChild(animatedFace);
	RemoveChild(sceneText);
	delete animatedFace;
	delete sceneText;
}

void Scene03::Update() {
	MasterScene::Update();
}