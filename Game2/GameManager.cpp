#include "stdafx.h"
#include "NeutralObj.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"

int		MecanimManager::ComboHistory[MAX_COMBO_HISTORY] = { 0 };
bool	GameManager::DebugMode = false;
Stage* GameManager::MainStage = nullptr;
Player* GameManager::MainPlayer = nullptr;
vector<Stage*> GameManager::StageList;

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
void Stage::Render()
{
	for (size_t i = 0; i < mBGImage.size(); i++)
	{
		mBGImage[i]->Render();
	}
	for (size_t i = 0; i < mImage.size(); i++)
	{
		mImage[0]->Render();
	}
	mCollider->Render();
	for (size_t i = 0; i < mEnemyList.size(); i++)
	{
		mEnemyList[i]->Render();
	}
}
void Stage::SetImagePos(float x, float y)
{
	mImage[0]->SetWorldPosX(mImagePos[0].x + x);
	mImage[0]->SetWorldPosY(mImagePos[0].x + y);

	mCollider->SetWorldPosX(x);
	mCollider->SetWorldPosY(y);
}
void Stage::SetBGImagePos(float x, float y)
{
	for (size_t i = 0; i < mBGImage.size(); i++)
	{
		mBGImage[i]->SetWorldPosX(mBGImagePos[i].x + x);
		mBGImage[i]->SetWorldPosY(mBGImagePos[i].y + y);
	}
}
void Stage::AddImage(wstring _stageImgName, Vector2 imagePos)
{
	ObImage* tmp = new ObImage();
	tmp->LoadFile(_stageImgName);
	tmp->SetWorldPos(imagePos);
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
void Stage::PortalCollisionCheck(GameObject* col)
{
	
}
void Stage::EnemyCollisionCheck(GameObject* col)
{
	for (size_t i = 0; i < mEnemyList.size(); i++)
	{
		if (mEnemyList[i]->isVisible && col->Intersect(mEnemyList[i]))
			mEnemyList[i]->isInhole = true;
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

bool GameManager::ChangeMainStage(wstring _stageImgName)
{
	for (size_t i = 0; i < StageList.size(); i++)
	{
		if (StageList[i]->mImageFName == _stageImgName)
		{
			MainStage = StageList[i];
			return true;
		}
	}
	return false;
}
