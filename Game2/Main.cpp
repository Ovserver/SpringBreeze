#include "stdafx.h"
#include "NeutralObj.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Text.h"
#include "Player.h"
#include "Main.h"

Main::Main()
{

}

Main::~Main()
{
}
void Main::Init()
{
	camUI.UpdateMatrix();
	

	GameManager::StageList.push_back(new Stage(L"stage_1-1.png", L"stage_1-1_collider.png", L"stage_1_bg_1.png"));
	GameManager::StageList[0]->AddBGImage(L"stage_1_bg_1-1.png", Vector2(-96, -8) * IMG_SCALE, 4, true);
	GameManager::StageList[0]->mBGImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6, false);
	GameManager::StageList[0]->AddEnemy(new Enemy(Vector2(150, -150), 10, ENEMY_SERIAL_NAME::WADDLE_DOO));
	GameManager::StageList[0]->AddEnemy(new Enemy(Vector2(280, -130), 10, ENEMY_SERIAL_NAME::WADDLE_DOO));
	GameManager::StageList[0]->AddPortal(new ObRect(), L"stage_1-2.png");
	GameManager::StageList[0]->mPortalList[0].rect.SetWorldPos(Vector2(396, -136) * IMG_SCALE);
	GameManager::StageList[0]->mPortalList[0].rect.SetScale().x = 24 * IMG_SCALE;
	GameManager::StageList[0]->mPortalList[0].rect.SetScale().y = 30 * IMG_SCALE;
	GameManager::StageList[0]->mPlayerInitPos.push_back(Vector2(50, -100) * IMG_SCALE);
	GameManager::StageList[0]->mPlayerInitPos.push_back(Vector2(432, -136) * IMG_SCALE);

	GameManager::StageList.push_back(new Stage(L"stage_1-2.png", L"stage_1-2_collider.png", L"stage_1_bg_1.png"));
	GameManager::StageList[1]->AddPortal(new ObRect(), L"stage_1-1.png", 1);
	GameManager::StageList[1]->AddImage(L"stage_1_effect_G1.png", Vector2(0, -96) * IMG_SCALE);
	GameManager::StageList[1]->AddImage(L"stage_1_effect_G2.png", Vector2(240, -96) * IMG_SCALE);
	GameManager::StageList[1]->mImage[1]->SetScale().x = GameManager::StageList[1]->mImage[1]->imageSize.x / 6.0f * IMG_SCALE;
	GameManager::StageList[1]->mImage[1]->SetScale().y = GameManager::StageList[1]->mImage[1]->imageSize.y * IMG_SCALE;
	GameManager::StageList[1]->mImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	GameManager::StageList[1]->mImage[1]->maxFrame.x = 6;
	GameManager::StageList[1]->mImage[2]->SetScale().x = GameManager::StageList[1]->mImage[2]->imageSize.x / 6.0f * IMG_SCALE;
	GameManager::StageList[1]->mImage[2]->SetScale().y = GameManager::StageList[1]->mImage[2]->imageSize.y * IMG_SCALE;
	GameManager::StageList[1]->mImage[2]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	GameManager::StageList[1]->mImage[2]->maxFrame.x = 6;
	GameManager::StageList[1]->mPortalList[0].rect.SetWorldPos(Vector2(156, -112) * IMG_SCALE);
	GameManager::StageList[1]->mPortalList[0].rect.SetScale().x = 24 * IMG_SCALE;
	GameManager::StageList[1]->mPortalList[0].rect.SetScale().y = 30 * IMG_SCALE;
	GameManager::StageList[1]->mPlayerInitPos.push_back(Vector2(128, -112) * IMG_SCALE);

	if (!MAINPLAYER)
	{
		MAINPLAYER = &mainPlayer;
		MAINPLAYER->Init();
	}

	GameManager::ChangeMainStage(L"stage_1-1.png");
	//MAINPLAYER->SetWorldPos(Vector2(100, -100) * IMG_SCALE);

	//UI_normal.LoadFile(L"UI_normal.png");
	//UI_normal.SetScale().x = UI_normal.imageSize.x * IMG_SCALE;
	//UI_normal.SetScale().y = UI_normal.imageSize.y * IMG_SCALE;
	//UI_normal.SetPivot() = OFFSET_B;
	//UI_normal.SetWorldPosY(app.GetHalfHeight() * -1);
	
	UIManager::Init();
}

void Main::Release()
{

}
int posX = 0;
int posY = 0;
void Main::Update()
{
	ImGui::SliderInt("POS_X", &posX, 0, 808);
	ImGui::SliderInt("POS_Y", &posY, 0, 192);
	if (ImGui::Button("Change Stage 1-1"))
	{
		GameManager::ChangeMainStage(L"stage_1-1.png");
	}
	if (ImGui::Button("Change Stage 1-2"))
	{
		GameManager::ChangeMainStage(L"stage_1-2.png");
	}
	if (ImGui::Button("Debug Mode"))
	{
		GameManager::DebugMode = !GameManager::DebugMode;
	}
	if (ImGui::Button("Debug Mode Player"))
	{
		MAINPLAYER->testAnimFSM = !MAINPLAYER->testAnimFSM;
	}
	if (GameManager::DebugMode)
		cout << "pPos : " << MAINPLAYER->GetWorldPos().x << "   " << MAINPLAYER->GetWorldPos().y << endl;
	//cout << "TextureDataR" <<(unsigned int)*(TEXTURE->GetTextureData(L"stage_1-1_collider_test.png").GetPixels() + posX * 4 + posY * 808 * 4 + 2) << endl;
	//cout << "TextureDataG" <<(unsigned int)*(TEXTURE->GetTextureData(L"stage_1-1_collider_test.png").GetPixels() + posX * 4 + posY * 808 * 4 + 1) << endl;
	//cout << "TextureDataB" <<(unsigned int)*(TEXTURE->GetTextureData(L"stage_1-1_collider_test.png").GetPixels() + posX * 4 + posY * 808 * 4) << endl;

	MAINPLAYER->Update();
	MAINSTAGE->Update();
	if (INPUT->KeyDown('R'))
	{
		MAINPLAYER->Release();
		this->Init();
	}
	app.maincam->SetWorldPos(MAINPLAYER->GetWorldPos());
	UIManager::Update();
}

void Main::LateUpdate()
{
	app.maincam->SetWorldPosY(-240);
	if (app.maincam->GetWorldPos().x < 130 * IMG_SCALE)
		app.maincam->SetWorldPosX(130 * IMG_SCALE);
	if (app.maincam->GetWorldPos().x > 750 * IMG_SCALE)
		app.maincam->SetWorldPosX(750 * IMG_SCALE);

	MAINSTAGE->SetBGImagePos(app.maincam->GetWorldPos().x, app.maincam->GetWorldPos().y);
	MAINPLAYER->LateUpdate();
}

void Main::Render()
{
	MAINSTAGE->Render();
	MAINPLAYER->Render();
	UIManager::Render(&camUI);
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(512.0f, 450.0f); // 248, 265
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}