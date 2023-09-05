#include "stdafx.h"
#include "GameManager.h"
#include "NeutralObj.h"
#include "Player.h"
#include "Enemy.h"
#include "WhispyWood.h"

WhispyWood::WhispyWood()
{
	maxHp = 40;
	hp = maxHp;
	isStasisType = true;
	
	initPos = Vector2(197, -660) * IMG_SCALE;
	SetWorldPos(initPos);
	serialName = ENEMY_SERIAL_NAME::WHISPY_WOOD;

	enemy_Idle.LoadFile(L"whispywood_idle.png");
	enemy_Idle.SetScale().x = enemy_Idle.imageSize.x / 6.0f * IMG_SCALE;
	enemy_Idle.SetScale().y = enemy_Idle.imageSize.y * IMG_SCALE;
	enemy_Idle.maxFrame.x = 6;
	enemy_Idle.SetPivot() = OFFSET_B;
	enemy_Idle.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 18);

	enemy_attack.LoadFile(L"whispywood_attack.png");
	enemy_attack.SetScale().x = enemy_attack.imageSize.x / 3.0f * IMG_SCALE;
	enemy_attack.SetScale().y = enemy_attack.imageSize.y * IMG_SCALE;
	enemy_attack.maxFrame.x = 3;
	enemy_attack.SetPivot() = OFFSET_B;

	enemy_ouch.LoadFile(L"whispywood_ouch1.png");
	enemy_ouch.SetScale().x = enemy_ouch.imageSize.x * IMG_SCALE;
	enemy_ouch.SetScale().y = enemy_ouch.imageSize.y * IMG_SCALE;
	enemy_ouch.SetPivot() = OFFSET_B;

	enemy_ouch2.LoadFile(L"whispywood_ouch2.png");
	enemy_ouch2.SetScale().x = enemy_ouch2.imageSize.x / 2.0f * IMG_SCALE;
	enemy_ouch2.SetScale().y = enemy_ouch2.imageSize.y * IMG_SCALE;
	enemy_ouch2.maxFrame.x = 2;
	enemy_ouch2.SetPivot() = OFFSET_B;

	enemy_over.LoadFile(L"whispywood_over.png");
	enemy_over.SetScale().x = enemy_over.imageSize.x / 2.0f * IMG_SCALE;
	enemy_over.SetScale().y = enemy_over.imageSize.y * IMG_SCALE;
	enemy_over.maxFrame.x = 2;
	enemy_over.SetPivot() = OFFSET_B;

	col.SetScale().x = enemy_Idle.imageSize.x / 6.0f * IMG_SCALE;
	col.SetScale().y = enemy_Idle.imageSize.y * IMG_SCALE;
	col.isFilled = false;
	col.SetPivot() = OFFSET_B;
	SetScale().x = col.GetScale().x;
	SetScale().y = col.GetScale().y;
	collider = COLLIDER::RECT;
	SetPivot() = OFFSET_B;

	isActive = false;
	UpdateSpritePos();
}

void WhispyWood::Init()
{

}

void WhispyWood::Update()
{
	if (MAINSTAGE->mImageFName == L"stage_1-boss.png" && MAINPLAYER->GetWorldPos().y < -650 * IMG_SCALE)
		isActive = true;
	if (isActive)
	{

	}
	cout << hp << endl;
}

void WhispyWood::Render()
{
	col.Render();
	if (hp <= 0)
		enemy_over.Render();
	else if (isDamage)
		enemy_ouch.Render();
	else if (atkTime > 0)
		enemy_attack.Render();
	else
		enemy_Idle.Render();
}

void WhispyWood::UpdateSpritePos()
{
	Enemy::UpdateSpritePos();
	enemy_ouch2.SetWorldPos(GetWorldPos());
	enemy_over.SetWorldPos(GetWorldPos());
	col.SetWorldPos(GetWorldPos());
}
