#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	active = false;
}

void Bullet::Init(Vector2 FirePos, float rotation, float power)
{
	SetScale().x = 20.0f;
	SetScale().y = 20.0f;
	speed = power;
	SetWorldPos(FirePos);
	lifeTime = 13.5f;
	fireDir.x = cos(rotation);
	fireDir.y = sin(rotation);

	speed2 = 0.0f;
	fireDir2.x = 0.0f;
	fireDir2.y = 1.0f;
}

void Bullet::Update()
{
	MoveWorldPos(fireDir * speed * DELTA);
	//MoveWorldPos(fireDir2 * speed2 * DELTA);

	speed2 += ((fireDir2.y > 0) ? -200.0f : 200.0f) * DELTA;

	lifeTime -= DELTA;

	/*if (GetWorldPos().y < -app.GetHalfHeight())
	{
		fireDir.y = -fireDir.y;
		fireDir2.y = -fireDir2.y;
		SetWorldPosY(-app.GetHalfHeight());
		speed *= 0.7f;
		speed2 *= 0.7f;
	}
	if (GetWorldPos().y > app.GetHalfHeight())
	{
		fireDir.y = -fireDir.y;
		fireDir2.y = -fireDir2.y;
		SetWorldPosY(app.GetHalfHeight());
		speed *= 0.7f;
		speed2 *= 0.7f;
	}
	
	if (GetWorldPos().x > app.GetHalfWidth())
	{
		fireDir.x = -fireDir.x;
		SetWorldPosX(app.GetHalfWidth());
	}
	if (GetWorldPos().x< -app.GetHalfWidth())
	{
		fireDir.x = -fireDir.x;
		SetWorldPosX(-app.GetHalfWidth());
	}
	*/
}
