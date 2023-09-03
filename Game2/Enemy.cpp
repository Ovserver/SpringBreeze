#include "stdafx.h"
#include "NeutralObj.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"

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
		MoveWorldPos(dir * DELTA * 100.0f);
	}
}
