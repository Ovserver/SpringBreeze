#include "stdafx.h"
#include "Text.h"
#include "NeutralObj.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Stage.h"
#include "UIManager.h"
#include "WhispyWood.h"
#include "MecanimManager.h"
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

	GameManager::StageList.push_back(new Stage(L"empty.png", L"empty.png", L"title_bg.png", true));
	STAGE_VEC_END->mBGType = BG_TYPE::REPEAT;
	STAGE_VEC_END->AddBGImage(L"title_newgame.png", Vector2(0, -80), 2, false, true);
	STAGE_VEC_END->mBGImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 4);
	STAGE_VEC_END->mPlayerInitPos.push_back(Vector2(-500, -500));
	STAGE_VEC_END->mLimitCameraPosX = Vector2(0, 0);
	STAGE_VEC_END->mLimitCameraPosY = Vector2(0, 0);
	STAGE_VEC_END->mBGMkey = "title";

	GameManager::StageList.push_back(new Stage(L"stage_1-1_another.png", L"stage_1-1_collider.png", L"stage_1_bg_1.png"));
	STAGE_VEC_END->mBGType = BG_TYPE::REPEAT;
	STAGE_VEC_END->AddBGImage(L"stage_1_bg_1-1.png", Vector2(-96, -8) * IMG_SCALE, 4, true);
	STAGE_VEC_END->mBGImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6, false);
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(254, -77) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::WADDLE_DOO));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(342, -113) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::WADDLE_DEE));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(585, -65) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::BRONTO_BURT));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(800, -89) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::TWIZZY));
	STAGE_VEC_END->AddPortal(Vector2(396, -136) * IMG_SCALE, L"stage_1-2.png");
	STAGE_VEC_END->AddPortal(Vector2(734, -112) * IMG_SCALE, L"stage_1-3.png");
	STAGE_VEC_END->mPlayerInitPos.push_back(Vector2(50, -100) * IMG_SCALE);
	STAGE_VEC_END->mPlayerInitPos.push_back(Vector2(432, -136) * IMG_SCALE);
	STAGE_VEC_END->mLimitCameraPosX = Vector2(130, 750);
	STAGE_VEC_END->mLimitCameraPosY = Vector2(-120, -120);
	STAGE_VEC_END->mBGMkey = "stage1_loop";

	GameManager::StageList.push_back(new Stage(L"stage_1-2.png", L"stage_1-2_collider.png", L"stage_1_bg_1.png"));
	STAGE_VEC_END->mBGType = BG_TYPE::REPEAT;
	STAGE_VEC_END->AddPortal(Vector2(156, -112) * IMG_SCALE, L"stage_1-1_another.png", 1);
	STAGE_VEC_END->AddImage(L"stage_1_effect_G1.png", Vector2(0, -96) * IMG_SCALE);
	STAGE_VEC_END->mImage[1]->SetScale().x = STAGE_VEC_END->mImage[1]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[1]->SetScale().y = STAGE_VEC_END->mImage[1]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[1]->maxFrame.x = 6;
	STAGE_VEC_END->AddImage(L"stage_1_effect_G2.png", Vector2(240, -96) * IMG_SCALE);
	STAGE_VEC_END->mImage[2]->SetScale().x = STAGE_VEC_END->mImage[2]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[2]->SetScale().y = STAGE_VEC_END->mImage[2]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[2]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[2]->maxFrame.x = 6;
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(148, -158) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::WADDLE_DEE));
	STAGE_VEC_END->mPlayerInitPos.push_back(Vector2(128, -112) * IMG_SCALE);
	STAGE_VEC_END->mLimitCameraPosX = Vector2(130, 132);
	STAGE_VEC_END->mLimitCameraPosY = Vector2(-125, -115);
	STAGE_VEC_END->mBGMkey = "stage1_loop";

	GameManager::StageList.push_back(new Stage(L"stage_1-3.png", L"stage_1-3_collider.png", L"stage_1_bg_2.png"));
	STAGE_VEC_END->mBGType = BG_TYPE::REPEAT;
	STAGE_VEC_END->AddBGImage(L"stage_1_bg_2-1.png", Vector2(32, -132) * IMG_SCALE, 4);
	STAGE_VEC_END->AddBGImage(L"stage_1_bg_2-2.png", Vector2(228, -132) * IMG_SCALE, 4);
	STAGE_VEC_END->mBGImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 4, false);
	STAGE_VEC_END->mBGImage[2]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 4, false);
	STAGE_VEC_END->AddImage(L"stage_1_effect_G1.png", Vector2(192, -144) * IMG_SCALE);
	STAGE_VEC_END->mImage[1]->SetScale().x = STAGE_VEC_END->mImage[1]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[1]->SetScale().y = STAGE_VEC_END->mImage[1]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[1]->maxFrame.x = 6;
	STAGE_VEC_END->AddImage(L"stage_1_effect_G1.png", Vector2(216, -144) * IMG_SCALE);
	STAGE_VEC_END->mImage[2]->SetScale().x = STAGE_VEC_END->mImage[2]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[2]->SetScale().y = STAGE_VEC_END->mImage[2]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[2]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[2]->maxFrame.x = 6;
	STAGE_VEC_END->AddImage(L"stage_1_effect_G1.png", Vector2(264, -144) * IMG_SCALE);
	STAGE_VEC_END->mImage[3]->SetScale().x = STAGE_VEC_END->mImage[3]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[3]->SetScale().y = STAGE_VEC_END->mImage[3]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[3]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[3]->maxFrame.x = 6;
	STAGE_VEC_END->AddImage(L"stage_1_effect_G1.png", Vector2(288, -144) * IMG_SCALE);
	STAGE_VEC_END->mImage[4]->SetScale().x = STAGE_VEC_END->mImage[4]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[4]->SetScale().y = STAGE_VEC_END->mImage[4]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[4]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[4]->maxFrame.x = 6;
	STAGE_VEC_END->AddImage(L"stage_1_effect_G1.png", Vector2(312, -144) * IMG_SCALE);
	STAGE_VEC_END->mImage[5]->SetScale().x = STAGE_VEC_END->mImage[5]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[5]->SetScale().y = STAGE_VEC_END->mImage[5]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[5]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[5]->maxFrame.x = 6;
	STAGE_VEC_END->AddImage(L"stage_1_effect_G3.png", Vector2(480, -72) * IMG_SCALE);
	STAGE_VEC_END->mImage[6]->SetScale().x = STAGE_VEC_END->mImage[6]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[6]->SetScale().y = STAGE_VEC_END->mImage[6]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[6]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[6]->maxFrame.x = 6;
	STAGE_VEC_END->AddImage(L"stage_1_effect_G3.png", Vector2(576, -72) * IMG_SCALE);
	STAGE_VEC_END->mImage[7]->SetScale().x = STAGE_VEC_END->mImage[7]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[7]->SetScale().y = STAGE_VEC_END->mImage[7]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[7]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[7]->maxFrame.x = 6;
	STAGE_VEC_END->AddImage(L"stage_1_effect_F1.png", Vector2(504, -144) * IMG_SCALE);
	STAGE_VEC_END->mImage[8]->SetScale().x = STAGE_VEC_END->mImage[8]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[8]->SetScale().y = STAGE_VEC_END->mImage[8]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[8]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[8]->maxFrame.x = 6;
	STAGE_VEC_END->AddImage(L"stage_1_effect_F2.png", Vector2(600, -120) * IMG_SCALE);
	STAGE_VEC_END->mImage[9]->SetScale().x = STAGE_VEC_END->mImage[9]->imageSize.x / 6.0f * IMG_SCALE;
	STAGE_VEC_END->mImage[9]->SetScale().y = STAGE_VEC_END->mImage[9]->imageSize.y * IMG_SCALE;
	STAGE_VEC_END->mImage[9]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	STAGE_VEC_END->mImage[9]->maxFrame.x = 6;
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(194, -148) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::WADDLE_DOO));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(460, -85) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::WADDLE_DEE));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(577, -69) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::BRONTO_BURT));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(798, -74) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::TWIZZY));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(641, -113) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::GRIZZO));
	STAGE_VEC_END->AddPortal(Vector2(780, -111) * IMG_SCALE, L"stage_1-4.png");
	STAGE_VEC_END->mPlayerInitPos.push_back(Vector2(50, -100) * IMG_SCALE);
	STAGE_VEC_END->mLimitCameraPosX = Vector2(130, 758);
	STAGE_VEC_END->mLimitCameraPosY = Vector2(-120, -120);
	STAGE_VEC_END->mBGMkey = "stage1_loop";

	GameManager::StageList.push_back(new Stage(L"stage_1-4.png", L"stage_1-4_collider.png", L"stage_1_bg_3.png"));
	STAGE_VEC_END->mBGType = BG_TYPE::ONCE;
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(254, -365) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::WADDLE_DOO));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(129, -277) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::GRIZZO));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(205, -147) * IMG_SCALE, 10, ENEMY_SERIAL_NAME::WADDLE_DEE));
	STAGE_VEC_END->AddPortal(Vector2(180, -111) * IMG_SCALE, L"stage_1-boss.png");
	STAGE_VEC_END->mPlayerInitPos.push_back(Vector2(104, -396) * IMG_SCALE);
	STAGE_VEC_END->mLimitCameraPosX = Vector2(130, 230);
	STAGE_VEC_END->mLimitCameraPosY = Vector2(-400, -120);
	STAGE_VEC_END->mBGMkey = "stage1_loop";

	GameManager::StageList.push_back(new Stage(L"stage_1-boss.png", L"stage_1-boss_collider.png", L"stage_1_bg_3.png"));
	STAGE_VEC_END->mBGType = BG_TYPE::ONCE;
	STAGE_VEC_END->mPlayerInitPos.push_back(Vector2(100, -100) * IMG_SCALE);
	//STAGE_VEC_END->mPlayerInitPos.push_back(Vector2(100, -600) * IMG_SCALE);
	STAGE_VEC_END->AddEnemy(new WhispyWood());
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(20, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(40, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(60, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(80, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(100, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(120, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	STAGE_VEC_END->AddEnemy(new Enemy(Vector2(140, -570) * IMG_SCALE, 1, ENEMY_SERIAL_NAME::WHISPY_APPLE));
	STAGE_VEC_END->mLimitCameraPosX = Vector2(130, 130);
	STAGE_VEC_END->mLimitCameraPosY = Vector2(-648, -120);
	STAGE_VEC_END->mCamLockPos = Vector2(130, -648);
	STAGE_VEC_END->mCamLockRangePosMin = Vector2(0, -648);
	STAGE_VEC_END->mCamLockRangePosMax = Vector2(450, -630);
	STAGE_VEC_END->mCamLockEventObject = STAGE_VEC_END->mEnemyList[0];
	STAGE_VEC_END->mCamLockEventType = CAM_LOCKIN_TYPE::SINGLE;
	STAGE_VEC_END->mBGMkey = "boss_loop";
	
	GameManager::StageList.push_back(new Stage(L"stage_1-clear.png", L"stage_1-clear_collider.png", L"stage_1_bg_3.png"));
	STAGE_VEC_END->mBGType = BG_TYPE::ONCE;
	STAGE_VEC_END->mPlayerInitPos.push_back(Vector2(100, -650) * IMG_SCALE);
	STAGE_VEC_END->mLimitCameraPosX = Vector2(130, 130);
	STAGE_VEC_END->mLimitCameraPosY = Vector2(-648, -120);
	STAGE_VEC_END->mBGMkey = "clear";

	if (!MAINPLAYER)
	{
		MAINPLAYER = &mainPlayer;
		MAINPLAYER->Init();
	}
	GameManager::Init();
	MAINSTAGE = GameManager::StageList[0];
	GameManager::ChangeMainStage(L"empty.png");
	SOUND->Play(MAINSTAGE->mBGMkey);
	UIManager::Init();
	for (size_t i = 0; i < NUM_SCORETEXT; i++)
	{
		scoreText[i].Init();
		scoreText[i].value = 0;
		scoreText[i].scaler = 0.3f;
		scoreText[i].SetWorldPos(Vector2(215 - i*12,-159));
		scoreText[i].Update();
		scoreText[i].UpdateMatrix();
	}
}

void Main::Release()
{

}
float scalers = 1;
float posX = 0;
float posY = 0;
float deathTime = 8;
void Main::Update()
{
	ImGui::SliderFloat("FadeScreen Alpha", &UIManager::UI_fadescreen->color.w, 0.0f, 0.5f);
	ImGui::SliderFloat("Master Volume", &app.soundScale, 0.0f, 1.0f);
	//ImGui::SliderFloat("posx", &posX, -800.0f, 800.0f);
	//ImGui::SliderFloat("posy", &posY, -800.0f, 800.0f);
	//ImGui::SliderFloat("scale", &scalers, 0.0f, 1.0f);

	if (MAINSTAGE->mImageFName == L"stage_1-clear.png")
		deathTime -= DELTA;
	if (deathTime <= 0)
	{
		UIManager::FadeScreen(false, L"empty.png", 0);
		deathTime = 8.5f;
	}

	SOUND->SetMasterVolume();
	if (INPUT->KeyDown(VK_NEXT))
	{
		if (app.soundScale > 0)
			app.soundScale -= 0.1f;
			SOUND->SetMasterVolume();
	}
	if (INPUT->KeyDown(VK_PRIOR))
	{
		if (app.soundScale < 1.0f)
			app.soundScale += 0.1f;
		SOUND->SetMasterVolume();
	}
	if (MAINSTAGE->mImageFName == L"empty.png" && INPUT->KeyDown('A'))
		UIManager::FadeScreen(false, L"stage_1-1_another.png", 0);

	if (ImGui::Button("Effect Test - Spread Star"))
	{
		GameManager::ActiveEffect(MAINPLAYER, UP * 10 * IMG_SCALE);
	}
	if (ImGui::Button("Sound Test - Attack"))
	{
		SOUND->Stop("attack");
		SOUND->Play("attack");
	}
	if (ImGui::Button("Go To Title"))
	{
		GameManager::ChangeMainStage(L"empty.png");
	}
	if (ImGui::Button("Change Stage 1-1"))
	{
		GameManager::ChangeMainStage(L"stage_1-1_another.png");
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
	if (ImGui::Button("Change Stage 1-clear"))
	{
		GameManager::ChangeMainStage(L"stage_1-clear.png");
	}

	MAINPLAYER->Update();
	MAINSTAGE->Update();
	GameManager::Update();
	UIManager::Update();

	int temp = GameManager::Score;
	for (size_t i = 0; i < NUM_SCORETEXT; i++)
	{		
		scoreText[i].value = temp % 10;
		temp /= 10;
		scoreText[i].SetWorldPosX(posX);
		scoreText[i].SetWorldPosY(posY);
		scoreText[i].Update();
	}
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
	GameManager::Render();
	UIManager::Render(&camUI);
	if (MAINSTAGE->mImageFName != L"empty.png")
	{
		for (size_t i = 0; i < NUM_SCORETEXT; i++)
		{
			scoreText[i].Render(&camUI);
		}
	}
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(248.0f * IMG_SCALE, 225.0f * IMG_SCALE); // 248, 225
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}