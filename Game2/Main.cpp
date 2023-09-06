#include "stdafx.h"
#include "NeutralObj.h"
#include "Enemy.h"
#include "GameManager.h"
#include "WhispyWood.h"
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
	GameManager::StageList[0]->mBGType = BG_TYPE::REPEAT;
	GameManager::StageList[0]->AddBGImage(L"stage_1_bg_1-1.png", Vector2(-96, -8) * IMG_SCALE, 4, true);
	GameManager::StageList[0]->mBGImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6, false);
	GameManager::StageList[0]->AddEnemy(new Enemy(Vector2(150, -150), 10, ENEMY_SERIAL_NAME::WADDLE_DOO));
	GameManager::StageList[0]->AddEnemy(new Enemy(Vector2(280, -130), 10, ENEMY_SERIAL_NAME::WADDLE_DOO));
	GameManager::StageList[0]->AddPortal(Vector2(396, -136) * IMG_SCALE, L"stage_1-2.png");
	GameManager::StageList[0]->mPlayerInitPos.push_back(Vector2(50, -100) * IMG_SCALE);
	GameManager::StageList[0]->mPlayerInitPos.push_back(Vector2(432, -136) * IMG_SCALE);
	GameManager::StageList[0]->mLimitCameraPosX = Vector2(130, 750);
	GameManager::StageList[0]->mLimitCameraPosY = Vector2(-120, -120);

	GameManager::StageList.push_back(new Stage(L"stage_1-2.png", L"stage_1-2_collider.png", L"stage_1_bg_1.png"));
	GameManager::StageList[1]->mBGType = BG_TYPE::REPEAT;
	GameManager::StageList[1]->AddPortal(Vector2(156, -112) * IMG_SCALE, L"stage_1-1.png", 1);
	GameManager::StageList[1]->AddImage(L"stage_1_effect_G1.png", Vector2(0, -96) * IMG_SCALE);
	GameManager::StageList[1]->mImage[1]->SetScale().x = GameManager::StageList[1]->mImage[1]->imageSize.x / 6.0f * IMG_SCALE;
	GameManager::StageList[1]->mImage[1]->SetScale().y = GameManager::StageList[1]->mImage[1]->imageSize.y * IMG_SCALE;
	GameManager::StageList[1]->mImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	GameManager::StageList[1]->mImage[1]->maxFrame.x = 6;
	GameManager::StageList[1]->AddImage(L"stage_1_effect_G2.png", Vector2(240, -96) * IMG_SCALE);
	GameManager::StageList[1]->mImage[2]->SetScale().x = GameManager::StageList[1]->mImage[2]->imageSize.x / 6.0f * IMG_SCALE;
	GameManager::StageList[1]->mImage[2]->SetScale().y = GameManager::StageList[1]->mImage[2]->imageSize.y * IMG_SCALE;
	GameManager::StageList[1]->mImage[2]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	GameManager::StageList[1]->mImage[2]->maxFrame.x = 6;
	GameManager::StageList[1]->mPlayerInitPos.push_back(Vector2(128, -112) * IMG_SCALE);
	GameManager::StageList[1]->mLimitCameraPosX = Vector2(130, 132);
	GameManager::StageList[1]->mLimitCameraPosY = Vector2(-125, -115);

	GameManager::StageList.push_back(new Stage(L"stage_1-3.png", L"stage_1-3_collider.png", L"stage_1_bg_2.png"));
	GameManager::StageList[2]->mBGType = BG_TYPE::REPEAT;
	GameManager::StageList[2]->AddBGImage(L"stage_1_bg_2-1.png", Vector2(32, -132) * IMG_SCALE, 4);
	GameManager::StageList[2]->AddBGImage(L"stage_1_bg_2-2.png", Vector2(228, -132) * IMG_SCALE, 4);
	GameManager::StageList[2]->mBGImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 4, false);
	GameManager::StageList[2]->mBGImage[2]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 4, false);
	GameManager::StageList[2]->AddPortal(Vector2(396, -136) * IMG_SCALE, L"stage_1-4.png");
	GameManager::StageList[2]->mPlayerInitPos.push_back(Vector2(50, -100) * IMG_SCALE);
	GameManager::StageList[2]->mLimitCameraPosX = Vector2(130, 750);
	GameManager::StageList[2]->mLimitCameraPosY = Vector2(-120, -120);

	GameManager::StageList.push_back(new Stage(L"stage_1-4.png", L"stage_1-4_collider.png", L"stage_1_bg_3.png"));
	GameManager::StageList[3]->mBGType = BG_TYPE::REPEAT;
	GameManager::StageList[3]->AddPortal(Vector2(396, -136) * IMG_SCALE, L"stage_1-boss.png");
	GameManager::StageList[3]->mPlayerInitPos.push_back(Vector2(50, -100) * IMG_SCALE);
	GameManager::StageList[3]->mLimitCameraPosX = Vector2(130, 750);
	GameManager::StageList[3]->mLimitCameraPosY = Vector2(-120, -120);

	GameManager::StageList.push_back(new Stage(L"stage_1-boss.png", L"stage_1-boss_collider.png", L"stage_1_bg_3.png"));
	GameManager::StageList[4]->mBGType = BG_TYPE::ONCE;
	GameManager::StageList[4]->mPlayerInitPos.push_back(Vector2(100, -100) * IMG_SCALE);
	//GameManager::StageList[4]->mPlayerInitPos.push_back(Vector2(100, -600) * IMG_SCALE);
	GameManager::StageList[4]->AddEnemy(new WhispyWood());
	GameManager::StageList[4]->AddEnemy(new Enemy(Vector2(20, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	GameManager::StageList[4]->AddEnemy(new Enemy(Vector2(40, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	GameManager::StageList[4]->AddEnemy(new Enemy(Vector2(60, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	GameManager::StageList[4]->AddEnemy(new Enemy(Vector2(80, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	GameManager::StageList[4]->AddEnemy(new Enemy(Vector2(100, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	GameManager::StageList[4]->AddEnemy(new Enemy(Vector2(120, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	GameManager::StageList[4]->AddEnemy(new Enemy(Vector2(140, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	GameManager::StageList[4]->mLimitCameraPosX = Vector2(130, 130);
	GameManager::StageList[4]->mLimitCameraPosY = Vector2(-648, -120);
	GameManager::StageList[4]->mCamLockPos = Vector2(130, -648);
	GameManager::StageList[4]->mCamLockRangePosMin = Vector2(0, -648);
	GameManager::StageList[4]->mCamLockRangePosMax = Vector2(450, -630);
	GameManager::StageList[4]->mCamLockEventObject = GameManager::StageList[4]->mEnemyList[0];
	GameManager::StageList[4]->mCamLockEventType = CAM_LOCKIN_TYPE::CONTINUOS;

	if (!MAINPLAYER)
	{
		MAINPLAYER = &mainPlayer;
		MAINPLAYER->Init();
	}

	GameManager::ChangeMainStage(L"stage_1-2.png");
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
	if (ImGui::Button("Change Stage 1-3"))
	{
		GameManager::ChangeMainStage(L"stage_1-3.png");
	}
	if (ImGui::Button("Change Stage 1-4"))
	{
		GameManager::ChangeMainStage(L"stage_1-4.png");
	}
	if (ImGui::Button("Change Stage 1-boss"))
	{
		GameManager::ChangeMainStage(L"stage_1-boss.png");
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

	MAINPLAYER->Update();
	MAINSTAGE->Update();
	UIManager::Update();
}

void Main::LateUpdate()
{
	MAINPLAYER->LateUpdate();
	MAINSTAGE->LateUpdate();
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