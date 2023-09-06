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
	isInhole = false;
	upVector = 0;
	if (serialName == ENEMY_SERIAL_NAME::WADDLE_DOO)
	{
		fowardVector = 1;
		isVisible = true;
		isStasisType = false;
		isMove = true;
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

		enemy_ouch.SetScale().x = enemy_ouch.imageSize.x * IMG_SCALE;
		enemy_ouch.SetScale().y = enemy_ouch.imageSize.y * IMG_SCALE;
		enemy_ouch.SetPivot() = OFFSET_B;

		SetScale().x = enemy_ouch.GetScale().x;
		SetScale().y = enemy_ouch.GetScale().y;
	}
	if (serialName == ENEMY_SERIAL_NAME::WHISPY_APPLE)
	{
		fowardVector = 0;
		isRight = RANDOM->Int(0, 1);
		isVisible = false;
		isStasisType = false;
		isMove = true;
		enemy_Idle.LoadFile(L"object_apple.png");
		enemy_move.LoadFile(L"object_apple.png");

		enemy_Idle.SetScale().x = enemy_Idle.imageSize.x / 4.0f * IMG_SCALE;
		enemy_Idle.SetScale().y = enemy_Idle.imageSize.y * IMG_SCALE;
		enemy_Idle.SetPivot() = OFFSET_B;
		enemy_Idle.uv.z = 1.0f / 4;

		enemy_move.SetScale().x = enemy_Idle.imageSize.x / 4.0f * IMG_SCALE;
		enemy_move.SetScale().y = enemy_Idle.imageSize.y * IMG_SCALE;
		enemy_move.SetPivot() = OFFSET_B;
		enemy_move.maxFrame.x = 4;
		if (isRight)
			enemy_move.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
		else
			enemy_move.ChangeAnim(ANIMSTATE::REVERSE_LOOP, 1.0f / 12);

		SetScale().x = enemy_Idle.GetScale().x;
		SetScale().y = enemy_Idle.GetScale().y;
	}
}

void Enemy::Update()
{
	if (!isVisible)
		return;
	if (isInhole)
	{
		Vector2 dir = MAINPLAYER->GetWorldPos() - GetWorldPos();
		if (dir.Length() < 10 * IMG_SCALE)
		{
			isInhole = false;
			isVisible = false;
			isStay = true;
			SetWorldPos(initPos);
			MAINPLAYER->inholeEnemyList.push_back(this);
			return;
		}
		dir.Normalize();
		MoveWorldPos(dir * DELTA * 100.0f * accel);
		accel += DELTA * 5;
	}
	else
	{
		if (serialName == ENEMY_SERIAL_NAME::WHISPY_APPLE)
		{
			upVector += DELTA * 10.0f;
			if (LANDING_AREA)
			{
				upVector *= -1;
				fowardVector = 1.5f;
			}
			if (upVector > 3.5f) upVector = 3.5f;
			MoveWorldPos(DOWN * DELTA * 100.0f * upVector);
			MoveWorldPos(RIGHT * DELTA * 100.0f * fowardVector * (isRight ? 1 : -1));
			if (INTERPOL_AREA_RISE)
			{
				while (INTERPOL_AREA_RISE) {
					MoveWorldPos(UP);
					UPDATE_COLOR;
				}
			}
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
					UPDATE_COLOR;
				}
			}
			else if (INTERPOL_AREA_PULL_RIGHT)
			{
				isRight = true;
				while (INTERPOL_AREA_PULL_RIGHT) {
					MoveWorldPos(RIGHT);
					UPDATE_COLOR;
				}
			}
		}
	}
	UPDATE_COLOR;
}

void Enemy::LateUpdate()
{
	if (isVisible &&
		!(GetWorldPos().x > app.maincam->GetWorldPos().x - app.GetHalfWidth() * 1.3f &&
			GetWorldPos().x < app.maincam->GetWorldPos().x + app.GetHalfWidth() * 1.3f &&
			GetWorldPos().y > app.maincam->GetWorldPos().y - app.GetHalfHeight() * 1.3f &&
			GetWorldPos().y < app.maincam->GetWorldPos().y + app.GetHalfHeight() * 1.3f))
	{
		cout << "false" << endl;
		SetWorldPos(initPos);
		isVisible = false;
	}
	if (!isVisible &&
		((initPos.x > app.maincam->GetWorldPos().x - app.GetHalfWidth() * 1.3f &&
			initPos.x < app.maincam->GetWorldPos().x - app.GetHalfWidth() * 1.2f) ||
			(initPos.x < app.maincam->GetWorldPos().x + app.GetHalfWidth() * 1.3f &&
			initPos.x > app.maincam->GetWorldPos().x + app.GetHalfWidth() * 1.2f) ||
			(initPos.y > app.maincam->GetWorldPos().y - app.GetHalfHeight() * 1.3f &&
			initPos.y < app.maincam->GetWorldPos().y - app.GetHalfHeight() * 1.2f) ||
			(initPos.y < app.maincam->GetWorldPos().y + app.GetHalfHeight() * 1.3f &&
			initPos.y > app.maincam->GetWorldPos().y + app.GetHalfHeight() * 1.2f)) &&
		(GetWorldPos().x < app.maincam->GetWorldPos().x - app.GetHalfWidth() * 1.15f ||
			GetWorldPos().x > app.maincam->GetWorldPos().x + app.GetHalfWidth() * 1.15f ||
			GetWorldPos().y < app.maincam->GetWorldPos().y - app.GetHalfHeight() * 1.15f ||
			GetWorldPos().y > app.maincam->GetWorldPos().y + app.GetHalfHeight() * 1.15f))
	{
		cout << "late enemy init" << endl;
		Init();
	}
}

void Enemy::Render()
{
	UpdateSpritePos();
	if (isVisible)
	{
		if (serialName == ENEMY_SERIAL_NAME::WADDLE_DOO)
		{
			if (isDamage || isInhole)
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
		if (serialName == ENEMY_SERIAL_NAME::WHISPY_APPLE)
		{
			if (isInhole)
				enemy_Idle.Render();
			else
				enemy_move.Render();
		}
	}
}

void Enemy::Damage(int value)
{
	hp -= value;
	cout << value << endl;
	if (hp <= 0)
	{
		isVisible = false;
	}
}

void Enemy::UpdateSpritePos()
{
	enemy_Idle.SetWorldPos(GetWorldPos());
	enemy_attack.SetWorldPos(GetWorldPos());
	enemy_move.SetWorldPos(GetWorldPos());
	enemy_ouch.SetWorldPos(GetWorldPos());
}
