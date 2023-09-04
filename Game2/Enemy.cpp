#include "stdafx.h"
#include "NeutralObj.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"

void Enemy::Init()
{
	SetWorldPos(initPos);
	hp = maxHp;
	accel = 1;
	isStay = false;
	isDamage = false;
	isVisible = true;
	isMove = true;
	if (serialName == ENEMY_SERIAL_NAME::WADDLE_DOO)
	{
		enemy_Idle.LoadFile(L"waddleDoo_idle.png");	
		enemy_move.LoadFile(L"waddleDoo_idle.png");
		enemy_ouch.LoadFile(L"waddleDoo_ouch.png");

		enemy_Idle.SetScale().x = enemy_Idle.imageSize.x / 2.0f * IMG_SCALE;
		enemy_Idle.SetScale().y = enemy_Idle.imageSize.y * IMG_SCALE;
		enemy_Idle.SetPivot() = OFFSET_B;
		enemy_Idle.uv.z = 0.5f;

		enemy_move.SetScale().x = enemy_Idle.imageSize.x / 2.0f * IMG_SCALE;
		enemy_move.SetScale().y = enemy_Idle.imageSize.y * IMG_SCALE;
		enemy_move.SetPivot() = OFFSET_B;
		enemy_move.maxFrame.x = 2;
		enemy_move.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 8);		

		enemy_ouch.SetScale().x = enemy_Idle.imageSize.x * IMG_SCALE;
		enemy_ouch.SetScale().y = enemy_Idle.imageSize.y * IMG_SCALE;
		enemy_ouch.SetPivot() = OFFSET_B;

		SetScale().x = enemy_Idle.GetScale().x;
		SetScale().y = enemy_Idle.GetScale().y;
	}
}

void Enemy::Update()
{

	if (isInhole)
	{
		Vector2 dir = MAINPLAYER->GetWorldPos() - GetWorldPos();
		if (dir.Length() < 10 * IMG_SCALE)
		{
			isInhole = false;
			isVisible = false;
			isStay = true;
			MAINPLAYER->inholeEnemyList.push_back(this);
			return;
		}
		dir.Normalize();
		MoveWorldPos(dir * DELTA * 100.0f * accel);
		accel += DELTA * 3;
	}
	else
	{
		upVector += DELTA * 15.0f;

		if (LANDING_AREA && upVector > 0)
		{
			upVector = 0;
		}
		if (upVector > 3.5f) upVector = 3.5f;

		MoveWorldPos(DOWN * DELTA * 100.0f * upVector);
		MoveWorldPos(RIGHT * DELTA * 100.0f * fowardVector * (isRight ? 1 : -1));
		if (INTERPOL_AREA_PULL_LEFT)
		{
			isRight = false;
			while (INTERPOL_AREA_PULL_LEFT) {
				MoveWorldPos(LEFT);
				UpdatePointColor(MAINSTAGE);
			}
		}
		else if (INTERPOL_AREA_PULL_RIGHT)
		{
			isRight = true;
			while (INTERPOL_AREA_PULL_RIGHT) {
				MoveWorldPos(RIGHT);
				UpdatePointColor(MAINSTAGE);
			}
		}
	}
	UpdatePointColor(MAINSTAGE);
}

void Enemy::UpdatePointColor(Stage* stage)
{
	ObImage* stageInfo = stage->mCollider;
	wstring fileName = stage->mColFName;

	Vector2 PixelPos = GetWorldPos() - stageInfo->GetWorldPos();
	PixelPos /= IMG_SCALE;

	// boundary values [X (0 ~ imageSize.x), Y (0 ~ imageSize.y)]
	if (PixelPos.x < 0) PixelPos.x = 0;
	if (PixelPos.x > stageInfo->imageSize.x) PixelPos.x = stageInfo->imageSize.x;
	if (PixelPos.y > 0) PixelPos.y = 0;
	if (PixelPos.y < 0) PixelPos.y *= -1;
	if (PixelPos.y > stageInfo->imageSize.y) PixelPos.y = stageInfo->imageSize.y;

	// GetPixels() : it's 0,0 Pixels pointer. is uInt8(1byte)
	// PixelPos.x  : 1Pixel is 32bit(RGBA) but, layout info(BGRA)
	// PixelPos.y  : Access the next row ->	Add all pixels from the previous row
	pointColor.w = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4) + 3);
	pointColor.x = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4) + 2);
	pointColor.y = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4) + 1);
	pointColor.z = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4));
}
void Enemy::Render()
{
	UpdateSpritePos();
	if (isVisible)
	{
		if (isDamage)
		{
			if (isRight)
			{
				enemy_ouch.SetRotation().y = 0;
				enemy_ouch.Render();
			}
			else {
				enemy_ouch.SetRotation().y = 0;
				enemy_ouch.Render();

			}
		}
		else if (isMove)
		{
			if (isRight)
			{
				enemy_move.SetRotation().y = 0;
				enemy_move.Render();
			}
			else
			{
				enemy_move.SetRotation().y = 180 * ToRadian;
				enemy_move.Render();
			}
		}
		else
		{
			if (isRight)
			{
				enemy_move.SetRotation().y = 0;
				enemy_move.Render();
			}
			else
			{
				enemy_move.SetRotation().y = 180 * ToRadian;
				enemy_move.Render();
			}
		}
	}
}

void Enemy::Damage(int value)
{
	hp -= value;
	if (hp <= 0)
	{
		isVisible = false;
	}
}

void Enemy::UpdateSpritePos()
{
	enemy_Idle.SetWorldPos(GetWorldPos());
	enemy_move.SetWorldPos(GetWorldPos());
	enemy_ouch.SetWorldPos(GetWorldPos());
}
