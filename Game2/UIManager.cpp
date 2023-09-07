#include "stdafx.h"
#include "GameManager.h"
#include "Stage.h"
#include "NeutralObj.h"
#include "MecanimManager.h"
#include "Player.h"
#include "UIManager.h"

ObRect* UIManager::UI_fadescreen = nullptr;
ObImage* UIManager::UI_standard = nullptr;
ObImage* UIManager::UI_enemy = nullptr;
ObRect* UIManager::player_HpBar = nullptr;
ObRect* UIManager::enemy_HpBar = nullptr;
ObRect* UIManager::backfaceUI = nullptr;
bool		UIManager::turnOn = true;

void UIManager::Init()
{
	UI_fadescreen = new ObRect();
	UI_standard = new ObImage();
	UI_enemy = new ObImage();
	player_HpBar = new ObRect();
	enemy_HpBar = new ObRect();
	backfaceUI = new ObRect();

	UI_fadescreen->SetScale().x = app.GetWidth();
	UI_fadescreen->SetScale().y = app.GetHeight();
	UI_fadescreen->color = Color(0, 0, 0, 0);

	UI_standard->LoadFile(L"UI_normal.png");
	UI_standard->SetScale().x = UI_standard->imageSize.x * IMG_SCALE;
	UI_standard->SetScale().y = UI_standard->imageSize.y * IMG_SCALE;
	UI_standard->SetPivot() = OFFSET_B;
	UI_standard->SetWorldPosY(app.GetHalfHeight() * -1);

	UI_enemy->LoadFile(L"UI_enemy.png");
	UI_enemy->SetScale().x = UI_enemy->imageSize.x * IMG_SCALE;
	UI_enemy->SetScale().y = UI_enemy->imageSize.y * IMG_SCALE;
	UI_enemy->SetPivot() = OFFSET_B;
	//UI_enemy->isVisible = false;
	UI_enemy->SetWorldPosY(app.GetHalfHeight() * -1);

	player_HpBar->SetScale().x = 60.0f * IMG_SCALE;
	player_HpBar->SetScale().y = 14.0f * IMG_SCALE;
	player_HpBar->color = Color(1, 0, 0);
	player_HpBar->SetPivot() = OFFSET_LB;
	player_HpBar->SetWorldPosX(-74 * IMG_SCALE);
	player_HpBar->SetWorldPosY(app.GetHalfHeight() * -1 + 24 * IMG_SCALE);

	enemy_HpBar->SetScale().x = 60.0f * IMG_SCALE;
	enemy_HpBar->SetScale().y = 14.0f * IMG_SCALE;
	enemy_HpBar->color = Color(0, 0, 1);
	enemy_HpBar->SetPivot() = OFFSET_RB;
	enemy_HpBar->SetWorldPosX(74 * IMG_SCALE);
	enemy_HpBar->SetWorldPosY(app.GetHalfHeight() * -1 + 24 * IMG_SCALE);

	backfaceUI->SetScale().x = UI_standard->imageSize.x * IMG_SCALE;
	backfaceUI->SetScale().y = UI_standard->imageSize.y * IMG_SCALE;
	backfaceUI->color = Color(0, 0, 0);
	backfaceUI->SetPivot() = OFFSET_B;
	backfaceUI->SetWorldPosY(app.GetHalfHeight() * -1);
}

void UIManager::Update()
{
	player_HpBar->SetScale().x = MAINPLAYER->hp / (float)PLAYER_MAX_HP * (60.0f * IMG_SCALE);
	if (!turnOn && UI_fadescreen->color.w < 0.5f)
	{
		UI_fadescreen->color.w += DELTA * 1.5f;
	}
	if (!turnOn && UI_fadescreen->color.w >= 0.5f)
	{
		GameManager::ChangeMainStage(GameManager::tmpStageImgName, GameManager::tmpPosListNum);
		turnOn = true;
	}
	if (turnOn && UI_fadescreen->color.w > 0.0f)
	{
		UI_fadescreen->color.w -= DELTA * 1.5f;
	}
}

void UIManager::Render(Camera* camUI)
{

	if (MAINSTAGE->mImageFName != L"empty.png")
	{
		backfaceUI->Render(camUI);
		player_HpBar->Render(camUI);
		//enemy_HpBar->Render(camUI);
		//UI_enemy->Render(camUI);
		UI_standard->Render(camUI);
	}
	UI_fadescreen->Render(camUI);
}

void UIManager::FadeScreen(bool _turnOn, wstring fname, int num)
{
	turnOn = _turnOn;
	GameManager::tmpStageImgName = fname;
	GameManager::tmpPosListNum = num;
}