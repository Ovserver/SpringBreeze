#include "stdafx.h"
#include "Enemy.h"
#include "Stage.h"
#include "NeutralObj.h"
#include "MecanimManager.h"
#include "Player.h"
#include "GameManager.h"
#include "UIManager.h"
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
void Stage::EnemyCollisionCheck(GameObject* col, COLLISION_CHECK_TYPE checkType, int damage, bool attackBoss)
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