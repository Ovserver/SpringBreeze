#include "stdafx.h"
#include "NeutralObj.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"

int				MecanimManager::ComboHistory[MAX_COMBO_HISTORY] = { 0 };
bool			GameManager::DebugMode = false;
Stage* GameManager::MainStage = nullptr;
Player* GameManager::MainPlayer = nullptr;
vector<Stage*>	GameManager::StageList;

ObImage* UIManager::UI_standard = nullptr;
ObImage* UIManager::UI_enemy = nullptr;
ObRect* UIManager::player_HpBar = nullptr;
ObRect* UIManager::enemy_HpBar = nullptr;
ObRect* UIManager::backfaceUI = nullptr;

Stage::Stage(wstring _stageImgName, wstring _stageColName, wstring _stageBGImgName)
{
	mImage.push_back(new ObImage());
	mImageFName = _stageImgName;
	mImage[0]->LoadFile(mImageFName);

	mCollider = new ObImage();
	mColFName = _stageColName;
	mCollider->LoadFile(mColFName);

	mBGImage.push_back(new ObImage());
	mBGImage[0]->LoadFile(_stageBGImgName);

	mImage[0]->SetScale().x = mImage[0]->imageSize.x * IMG_SCALE;
	mImage[0]->SetScale().y = mImage[0]->imageSize.y * IMG_SCALE;
	mImage[0]->SetPivot() = OFFSET_LT;

	mCollider->SetScale().x = mImage[0]->imageSize.x * IMG_SCALE;
	mCollider->SetScale().y = mImage[0]->imageSize.y * IMG_SCALE;
	mCollider->SetPivot() = OFFSET_LT;

	mBGImage[0]->SetScale().x = mBGImage[0]->imageSize.x * IMG_SCALE;
	mBGImage[0]->SetScale().y = mBGImage[0]->imageSize.y * IMG_SCALE;

	mImagePos.push_back(Vector2(0, 0));
	mBGImagePos.push_back(Vector2(0, 0));

	limitCameraPosX = RIGHT;
	limitCameraPosY = RIGHT;
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
	if (app.maincam->GetWorldPos().y < limitCameraPosY.x * IMG_SCALE)
		app.maincam->SetWorldPosY(limitCameraPosY.x * IMG_SCALE);
	if (app.maincam->GetWorldPos().y > limitCameraPosY.y * IMG_SCALE)
		app.maincam->SetWorldPosY(limitCameraPosY.y * IMG_SCALE);

	if (app.maincam->GetWorldPos().x < limitCameraPosX.x * IMG_SCALE)
		app.maincam->SetWorldPosX(limitCameraPosX.x * IMG_SCALE);
	if (app.maincam->GetWorldPos().x > limitCameraPosX.y * IMG_SCALE)
		app.maincam->SetWorldPosX(limitCameraPosX.y * IMG_SCALE);
	SetBGImagePos(app.maincam->GetWorldPos());
	if (mBGType == BG_TYPE::ONCE)
	{
		float camX, camY;
		camX = abs(app.maincam->GetWorldPos().x / (limitCameraPosX.y * IMG_SCALE));
		camY = abs(app.maincam->GetWorldPos().y / (limitCameraPosY.y * IMG_SCALE));
		//cout << camX << "  " << camY << endl;
		mBGImage[0]->uv.x;
		mBGImage[0]->uv.z;
		mBGImage[0]->uv.y = 0 + camY * 0.05f;
		mBGImage[0]->uv.w = 1 + camY * 0.05f;
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
	//mCollider->Render();
	for (size_t i = 0; i < mPortalList.size(); i++)
	{
		mPortalList[i].rect.Render();
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
void Stage::AddBGImage(wstring _stageImgName, Vector2 imagePos, int frame, bool isVertical)
{
	ObImage* tmp = new ObImage();
	tmp->LoadFile(_stageImgName);
	tmp->SetWorldPos(imagePos * IMG_SCALE);
	tmp->SetScale().x = tmp->imageSize.x / (!isVertical ? frame : 1) * IMG_SCALE;
	tmp->SetScale().y = tmp->imageSize.y / (isVertical ? frame : 1) * IMG_SCALE;
	if (isVertical) { tmp->uv.w = 1.0f / frame; tmp->maxFrame.y = frame; }
	else { tmp->uv.z = 1.0f / frame; tmp->maxFrame.x = frame; }
	mBGImage.push_back(tmp);
	mBGImagePos.push_back(imagePos);
}
void Stage::AddEnemy(Enemy* enemy)
{
	mEnemyList.push_back(enemy);
}
void Stage::AddPortal(ObRect* _rect, wstring _destStageName, int _initPosNum)
{
	Portal temp;
	temp.rect.SetPivot() = OFFSET_B;
	temp.rect.collider = COLLIDER::RECT;
	temp.rect.isFilled = false;
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
			GameManager::ChangeMainStage(mPortalList[i].destStageFname, mPortalList[i].initPosNum);
			return true;
		}
	}
	return false;
}
void Stage::EnemyCollisionCheck(GameObject* col, COLLISION_CHECK_TYPE checkType, int damage)
{
	for (size_t i = 0; i < mEnemyList.size(); i++)
	{
		//cout << "i " << i << "/isvi : "<<mEnemyList[i]->isVisible << "/intersect : " << col->Intersect(mEnemyList[i]) << (mEnemyList[i]->hp) <<endl;
		cout << (mEnemyList[i]->collider == COLLIDER::RECT) << endl;
		//cout << col->GetWorldPos().x << " XX " << mEnemyList[i]->GetWorldPos().x << endl;
		//cout << col->GetWorldPos().y << " YY " << mEnemyList[i]->GetWorldPos().y << endl;
		if (mEnemyList[i]->isVisible && col->Intersect(mEnemyList[i]))
		{
			cout << "colcheck" << endl;
			if (!mEnemyList[i]->isStasisType && checkType == COLLISION_CHECK_TYPE::INHOLE)
				mEnemyList[i]->isInhole = true;
			if (checkType == COLLISION_CHECK_TYPE::ATTACK_BULLET_ONCE)
			{
				cout << "damaged" << endl;
				mEnemyList[i]->Damage(damage);
				col->isVisible = false;
				return;
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

bool GameManager::IsColorMatch(Color& cl, float r, float g, float b)
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
			MainStage = StageList[i];
			MainStage->Init();
			MainPlayer->SetWorldPos(MainStage->mPlayerInitPos[posListNum]);
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
	UI_standard = new ObImage();
	UI_enemy = new ObImage();
	player_HpBar = new ObRect();
	enemy_HpBar = new ObRect();
	backfaceUI = new ObRect();

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
}

void UIManager::Render(Camera* camUI)
{
	backfaceUI->Render(camUI);
	player_HpBar->Render(camUI);
	//enemy_HpBar->Render(camUI);
	//UI_enemy->Render(camUI);
	UI_standard->Render(camUI);
}