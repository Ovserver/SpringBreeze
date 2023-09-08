#include "stdafx.h"
#include "NeutralObj.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Stage.h"
#include "MecanimManager.h"
#include "Player.h"

int				GameManager::Score = 0;
int				GameManager::tmpPosListNum = 0;
wstring			GameManager::tmpStageImgName;
bool			GameManager::DebugMode = false;
Stage* GameManager::MainStage = nullptr;
Player* GameManager::MainPlayer = nullptr;
vector<Stage*>	GameManager::StageList;
vector<Effect*> GameManager::Effect_SpreadStar;



void GameManager::Init()
{
	SOUND->AddSound("spit.wav", "spitout");
	SOUND->AddSound("spit.wav", "spitout");
	SOUND->AddSound("slide.wav", "slide");
	SOUND->AddSound("sprint.wav", "dash");
	SOUND->AddSound("star-hit.wav", "starbulletend");
	SOUND->AddSound("suck_long.wav", "inhole");
	SOUND->AddSound("inholeit.wav", "inholeit");
	SOUND->AddSound("swallow.wav", "swallow");
	SOUND->AddSound("jump.wav", "jump");
	SOUND->AddSound("fly.wav", "hover");
	SOUND->AddSound("fly-spit.wav", "hoverend");
	SOUND->AddSound("hurt.wav", "ouch");
	SOUND->AddSound("hit2.wav", "attack");
	SOUND->AddSound("boss-defeat.wav", "bossdefeat");
	SOUND->AddSound("enter-door.wav", "portal");

	SOUND->AddSound("bg_spring_breeze.mp3", "title", true);
	SOUND->AddSound("bg_greengreens_intro.mp3", "stage1_intro");
	SOUND->AddSound("bg_greengreens_loop.mp3", "stage1_loop", true);
	SOUND->AddSound("bg_boss_battle_intro.mp3", "boss_intro");
	SOUND->AddSound("bg_boss_battle_loop.mp3", "boss_loop", true);
	SOUND->AddSound("bg_victory_dance.mp3", "clear");
	SOUND->AddSound("bg_healthover.mp3", "healthover");

	for (size_t i = 0; i < 10; i++)
	{
		ObImage* temp = new ObImage();
		temp->LoadFile(L"effect_spreadstar.png");
		temp->SetScale().x = temp->imageSize.x / 5.0f * IMG_SCALE;
		temp->SetScale().y = temp->imageSize.y * IMG_SCALE;
		temp->maxFrame.x = 5;
		temp->ChangeAnim(ANIMSTATE::ONCE, 1.0f / 18);
		temp->isVisible = false;
		Effect_SpreadStar.push_back(new Effect(temp, 0.3f));
	}
}

void GameManager::InitEffect(Effect* effect)
{
	effect->image->ChangeAnim(ANIMSTATE::ONCE, 1.0f / 18);
	effect->image->isVisible = true;
}

void GameManager::ActiveEffect(GameObject* ob, Vector2 pos)
{
	for (size_t i = 0; i < 10; i++)
	{
		if (!Effect_SpreadStar[i]->image->isVisible)
		{
			cout << "true" << endl;
			Effect_SpreadStar[i]->image->SetWorldPos(ob->GetWorldPos() + pos);
			Effect_SpreadStar[i]->image->isVisible = true;
			Effect_SpreadStar[i]->image->ChangeAnim(ANIMSTATE::ONCE, 1.0f / 18);
			Effect_SpreadStar[i]->lifeTime = Effect_SpreadStar[i]->maxLifeTime;
			return;
		}
	}
}

void GameManager::Update()
{
	for (size_t i = 0; i < 10; i++)
	{
		if (Effect_SpreadStar[i]->lifeTime > 0)
		{
			Effect_SpreadStar[i]->lifeTime -= DELTA;
		}
		if (Effect_SpreadStar[i]->lifeTime <= 0)
		{
			Effect_SpreadStar[i]->image->isVisible = false;
		}
	}
}

void GameManager::Render()
{
	for (size_t i = 0; i < 10; i++)
	{
		Effect_SpreadStar[i]->image->Render();
	}
}

bool GameManager::IsColorMatch(Color& cl, float r, float g, float b, float a)
{
	if (cl.x == r && cl.y == g && cl.z == b)
		return true;
	else
		return false;
}

bool GameManager::ChangeMainStage(wstring _stageImgName, int posListNum)
{
	for (size_t i = 0; i < StageList.size(); i++)
	{
		if (StageList[i]->mImageFName == _stageImgName)
		{
			if (MainStage->mBGMkey != StageList[i]->mBGMkey)
			{
				SOUND->Stop(MainStage->mBGMkey);
				SOUND->Play(StageList[i]->mBGMkey);
			}
			MainStage = StageList[i];
			if (MainStage->mImageFName == L"empty.png")
			{
				MAINPLAYER->hp = 100;
				MAINPLAYER->isPortaling = true; 
				Score = 0;
			}
			MainStage->Init();
			MainPlayer->SetWorldPos(MainStage->mPlayerInitPos[posListNum]);
			MainPlayer->InitAnimState();
			tmpStageImgName = L"";
			tmpPosListNum = 0;
			return true;
		}
	}
	return false;
}

Color GameManager::GetPointColor(GameObject* gameObject)
{
	ObImage* stageInfo = MainStage->mCollider;
	wstring fileName = MainStage->mColFName;

	Vector2 PixelPos = gameObject->GetWorldPos() - stageInfo->GetWorldPos();
	PixelPos /= IMG_SCALE;

	// boundary values [X (0 ~ imageSize.x), Y (0 ~ imageSize.y)]
	if (PixelPos.x < 0) PixelPos.x = 0;
	if (PixelPos.x > stageInfo->imageSize.x) PixelPos.x = stageInfo->imageSize.x;
	if (PixelPos.y > 0) PixelPos.y = 0;
	if (PixelPos.y < 0) PixelPos.y *= -1;
	if (PixelPos.y > stageInfo->imageSize.y) PixelPos.y = stageInfo->imageSize.y;

	Color pointColor;
	// GetPixels() : it's 0,0 Pixels pointer. is uInt8(1byte)
	// PixelPos.x  : 1Pixel is 32bit(RGBA) but, layout info(BGRA)
	// PixelPos.y  : Access the next row ->	Add all pixels from the previous row
	pointColor.w = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4) + 3);
	pointColor.x = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4) + 2);
	pointColor.y = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4) + 1);
	pointColor.z = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4));

	return pointColor;
}

