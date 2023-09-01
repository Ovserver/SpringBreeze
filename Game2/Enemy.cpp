#include "stdafx.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Player.h"

void Enemy::Update()
{
	if (isInhole)
	{
		Vector2 dir = MAINPLAYER->GetWorldPos() - GetWorldPos();
		if (dir.Length() < 10 * IMG_SCALE) { isInhole = false; isVisible = false; return; }
		dir.Normalize();
		MoveWorldPos(dir * DELTA * 100.0f);
	}
}
