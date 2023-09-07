#include "stdafx.h"
#include "NeutralObj.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"

int				GameManager::tmpPosListNum = 0;
wstring			GameManager::tmpStageImgName;
int				MecanimManager::ComboHistory[MAX_COMBO_HISTORY] = { 0 };
bool			GameManager::DebugMode = false;
Stage*			GameManager::MainStage = nullptr;
Player*			GameManager::MainPlayer = nullptr;
vector<Stage*>	GameManager::StageList;
vector<Effect*> GameManager::Effect_SpreadStar;

ObRect*		UIManager::UI_fadescreen = nullptr;
ObImage*	UIManager::UI_standard = nullptr;
ObImage*	UIManager::UI_enemy = nullptr;
ObRect*		UIManager::player_HpBar = nullptr;
ObRect*		UIManager::enemy_HpBar = nullptr;
ObRect*		UIManager::backfaceUI = nullptr;
bool		UIManager::turnOn = true;

Stage::Stage(wstring _stageImgName, wstring _stageColName, wstring _stageBGImgName, bool nonScale)
{
	mCamLock = false;
	mCamLockEventObject = nullptr;
	mImage.push_back(new ObImage());
	mImageFName = _stageImgName;
	mImage[0]->LoadFile(mImageFName);

	mCollider = new ObImage();
	mColFName = _stageColName;
	mCollider->LoadFile(mColFName);

	mBGImage.push_back(new ObImage());
	mBGImage[0]->LoadFile(_stageBGImgName);

	mImage[0]->SetScale().x = mImage[0]->imageSize.x * (nonScale ? 1 : IMG_SCALE);
	mImage[0]->SetScale().y = mImage[0]->imageSize.y * (nonScale ? 1 : IMG_SCALE);
	mImage[0]->SetPivot() = OFFSET_LT;

	mCollider->SetScale().x = mImage[0]->imageSize.x * (nonScale ? 1 : IMG_SCALE);
	mCollider->SetScale().y = mImage[0]->imageSize.y * (nonScale ? 1 : IMG_SCALE);
	mCollider->SetPivot() = OFFSET_LT;

	mBGImage[0]->SetScale().x = mBGImage[0]->imageSize.x * (nonScale ? 1 : IMG_SCALE);
	mBGImage[0]->SetScale().y = mBGImage[0]->imageSize.y * (nonScale ? 1 : IMG_SCALE);

	mImagePos.push_back(Vector2(0, 0));
	mBGImagePos.push_back(Vector2(0, 0));

	mLimitCameraPosX = RIGHT;
	mLimitCameraPosY = RIGHT;
}
void Stage::Init()
{
	for (size_t i = 0; i < mEnemyList.size(); i++)
	{
		mEnemyList[i]->Init();
	}
}
void Stage::Update()
{
	for (size_t i = 0; i < mEnemyList.size(); i++)
	{
		mEnemyList[i]->Update();
	}
}
void Stage::LateUpdate()
{
	app.maincam->SetWorldPos(MAINPLAYER->GetWorldPos());

	if (app.maincam->GetWorldPos().y < mLimitCameraPosY.x * IMG_SCALE)
		app.maincam->SetWorldPosY(mLimitCameraPosY.x * IMG_SCALE);
	if (app.maincam->GetWorldPos().y > mLimitCameraPosY.y * IMG_SCALE)
		app.maincam->SetWorldPosY(mLimitCameraPosY.y * IMG_SCALE);

	if (app.maincam->GetWorldPos().x < mLimitCameraPosX.x * IMG_SCALE)
		app.maincam->SetWorldPosX(mLimitCameraPosX.x * IMG_SCALE);
	if (app.maincam->GetWorldPos().x > mLimitCameraPosX.y * IMG_SCALE)
		app.maincam->SetWorldPosX(mLimitCameraPosX.y * IMG_SCALE);

	if (mCamLock)
		app.maincam->SetWorldPos(mCamLockPos * IMG_SCALE);

	SetBGImagePos(app.maincam->GetWorldPos());

	if (mBGType == BG_TYPE::ONCE)
	{
		float camX, camY;
		camX = abs(app.maincam->GetWorldPos().x / (mLimitCameraPosX.y * IMG_SCALE));
		camY = abs(app.maincam->GetWorldPos().y / (mLimitCameraPosY.y * IMG_SCALE));
		//cout << camX << "  " << camY << endl;
		mBGImage[0]->uv.x;
		mBGImage[0]->uv.z;
		mBGImage[0]->uv.y = 0 + camY * 0.05f;
		mBGImage[0]->uv.w = 1 + camY * 0.05f;
	}
	if (mCamLockEventObject)
	{
		if (mCamLockEventObject->isVisible)
		{
			if (MAINPLAYER->GetWorldPos().x > mCamLockRangePosMin.x * IMG_SCALE &&
				MAINPLAYER->GetWorldPos().x < mCamLockRangePosMax.x * IMG_SCALE &&
				MAINPLAYER->GetWorldPos().y > mCamLockRangePosMin.y * IMG_SCALE &&
				MAINPLAYER->GetWorldPos().y < mCamLockRangePosMax.y * IMG_SCALE)
			{
				mCamLock = true;
			}
		}
		else
		{
			if (mCamLockEventType == CAM_LOCKIN_TYPE::SINGLE && mCamLock)
				mCamLock = false;
		}
	}
	for (size_t i = 0; i < mEnemyList.size(); i++)
	{
		mEnemyList[i]->LateUpdate();
	}
}
void Stage::Render()
{
	for (size_t i = 0; i < mBGImage.size(); i++)
	{
		mBGImage[i]->Render();
	}
	for (size_t i = 0; i < mImage.size(); i++)
	{
		mImage[i]->Render();
	}
	for (size_t i = 0; i < mPortalList.size(); i++)
	{
		mPortalList[i].Render();
	}
	for (size_t i = 0; i < mEnemyList.size(); i++)
	{
		mEnemyList[i]->Render();
	}
}
void Stage::SetImagePos(Vector2 pos)
{
	mImage[0]->SetWorldPos(mImagePos[0] + pos);
	mCollider->SetWorldPos(pos);
}
void Stage::SetBGImagePos(Vector2 pos)
{
	for (size_t i = 0; i < mBGImage.size(); i++)
	{
		mBGImage[i]->SetWorldPos(mBGImagePos[i] + pos);
	}
}
void Stage::AddImage(wstring _stageImgName, Vector2 imagePos)
{
	ObImage* tmp = new ObImage();
	tmp->LoadFile(_stageImgName);
	tmp->SetWorldPos(imagePos);
	tmp->SetPivot() = OFFSET_LT;
	mImage.push_back(tmp);
	mImagePos.push_back(imagePos);
}
void Stage::AddBGImage(wstring _stageImgName, Vector2 imagePos, int frame, bool isVertical, bool nonScale)
{
	ObImage* tmp = new ObImage();
	tmp->LoadFile(_stageImgName);
	tmp->SetWorldPos(imagePos * IMG_SCALE);
	tmp->SetScale().x = tmp->imageSize.x / (!isVertical ? frame : 1) * (nonScale ? 1 : IMG_SCALE);
	tmp->SetScale().y = tmp->imageSize.y / (isVertical ? frame : 1) * (nonScale ? 1 : IMG_SCALE);
	if (isVertical) { tmp->uv.w = 1.0f / frame; tmp->maxFrame.y = frame; }
	else { tmp->uv.z = 1.0f / frame; tmp->maxFrame.x = frame; }
	mBGImage.push_back(tmp);
	mBGImagePos.push_back(imagePos);
}
void Stage::AddEnemy(Enemy* enemy)
{
	mEnemyList.push_back(enemy);
}
void Stage::AddPortal(Vector2 pos, wstring _destStageName, int _initPosNum)
{
	Portal temp = Portal(pos);
	temp.destStageFname = _destStageName;
	temp.initPosNum = _initPosNum;
	mPortalList.push_back(temp);
}
bool Stage::PortalCollisionCheck(GameObject* col)
{
	for (size_t i = 0; i < mPortalList.size(); i++)
	{
		if (mPortalList[i].rect.Intersect(col))
		{
			SOUND->Stop("portal");
			SOUND->Play("portal");
			UIManager::FadeScreen(false, mPortalList[i].destStageFname, mPortalList[i].initPosNum);
			return true;
		}
	}
	return false;
}
void Stage::EnemyCollisionCheck(GameObject* col, COLLISION_CHECK_TYPE checkType, int damage,bool attackBoss)
{
	NeutralObj* neutraltmp = (NeutralObj*)col;
	Player* playertmp = (Player*)col;
	for (size_t i = 0; i < mEnemyList.size(); i++)
	{
		if (mEnemyList[i]->isVisible && mEnemyList[i]->hp > 0 && col->Intersect(mEnemyList[i]))
		{
			if (!mEnemyList[i]->isStasisType && checkType == COLLISION_CHECK_TYPE::INHOLE)
				mEnemyList[i]->isInhole = true;
			if (checkType == COLLISION_CHECK_TYPE::ATTACK_BULLET_ONCE)
			{
				if (!attackBoss && mEnemyList[i]->GetSerialName() == ENEMY_SERIAL_NAME::WHISPY_WOOD)
				{

				}
				else
				{
					mEnemyList[i]->Damage(damage);
					col->isVisible = false;
				}
				return;
			}
			if (checkType == COLLISION_CHECK_TYPE::ATTACK_BULLET_ASSAULT)
			{
				if (neutraltmp->interactObjList.size() == 0)
				{
					mEnemyList[i]->Damage(damage);
					neutraltmp->interactObjList.push_back(mEnemyList[i]);
				}
				else
				{
					for (size_t j = 0; j < neutraltmp->interactObjList.size(); j++)
					{
						if (neutraltmp->interactObjList[j] == mEnemyList[i])
							break;
						else
						{
							mEnemyList[i]->Damage(damage);
							neutraltmp->interactObjList.push_back(mEnemyList[i]);
						}
					}
				}
			}
			if (checkType == COLLISION_CHECK_TYPE::COLLISION_OBJECT)
			{
				if (!mEnemyList[i]->isInhole && mEnemyList[i]->GetSerialName() != ENEMY_SERIAL_NAME::WHISPY_WOOD)
				{
					mEnemyList[i]->Damage(5);
					if (playertmp->slideTime <= 0)
						playertmp->Damage(15);
				}
			}
		}
	}
}
bool Stage::EnemyInholingCheck()
{
	for (size_t i = 0; i < mEnemyList.size(); i++)
	{
		if (mEnemyList[i]->isInhole)
			return true;
	}
	return false;
}
void MecanimManager::ComboInput(int keyCode)
{
	for (size_t i = MAX_COMBO_HISTORY - 1; i > 0; i--)
	{
		ComboHistory[i] = ComboHistory[i - 1];
	}
	ComboHistory[0] = keyCode;
}

void MecanimManager::ComboClear()
{
	for (size_t i = 0; i < MAX_COMBO_HISTORY; i++)
	{
		ComboHistory[i] = 0;
	}
}

bool MecanimManager::ComboMatch(ComboMap* comboMap)
{
	for (size_t i = 0; i < comboMap->comboLength; i++)
	{
		if (ComboHistory[i] != comboMap->comboMaps[i])
			return false;
	}
	return true;
}

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

	for (size_t i = 0; i < 10; i++)
	{
		ObImage* temp = new ObImage();
		temp->LoadFile(L"effect_spreadstar.png");
		temp->SetScale().x = temp->imageSize.x / 5.0f * IMG_SCALE;
		temp->SetScale().y = temp->imageSize.y * IMG_SCALE;
		temp->maxFrame.x = 5;
		temp->ChangeAnim(ANIMSTATE::ONCE, 1.0f / 18);
		temp->isVisible = false;
		Effect_SpreadStar.push_back(new Effect(temp,0.3f));
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
