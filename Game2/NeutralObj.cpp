#include "stdafx.h"
#include "NeutralObj.h"

NeutralObj::NeutralObj(OBJECT_SERIAL_NAME _serialName)
{
	serialName = _serialName;
	dir = Vector2(0, 0), speed = 0;
	if (_serialName == OBJECT_SERIAL_NAME::STAR_BULLET)
	{
		LoadFile(L"object_starbullet.png");
		SetScale().x = imageSize.x / 4.0f * IMG_SCALE * 1.5f;
		SetScale().y = imageSize.y * IMG_SCALE * 1.5f;
		maxFrame.x = 4;
		ChangeAnim(ANIMSTATE::LOOP, 1.0f / 24);
		isVisible = false;
		collider = COLLIDER::CIRCLE;
		SetPivot() = OFFSET_B;
	}
}

void NeutralObj::Update()
{
	if (isVisible)
	{
		MoveWorldPos(dir * speed * DELTA);
	}
}
