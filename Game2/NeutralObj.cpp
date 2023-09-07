#include "stdafx.h"
#include "GameManager.h"
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
		ChangeAnim(ANIMSTATE::LOOP, 1.0f / 18);
		isVisible = false;
		collider = COLLIDER::CIRCLE;
		SetPivot() = OFFSET_B;
	}
	if (_serialName == OBJECT_SERIAL_NAME::STAR_BULLET_STRENGTH)
	{
		LoadFile(L"object_starbullet.png");
		SetScale().x = imageSize.x / 4.0f * IMG_SCALE * 2.0f;
		SetScale().y = imageSize.y * IMG_SCALE * 2.0f;
		maxFrame.x = 4;
		ChangeAnim(ANIMSTATE::LOOP, 1.0f / 18);
		isVisible = false;
		collider = COLLIDER::CIRCLE;
		SetPivot() = OFFSET_B;

		subImage.push_back(new ObImage());
		subImage[0]->LoadFile(L"effect_blink.png");
		subImage[0]->SetScale().x = subImage[0]->imageSize.x / 2.0f * IMG_SCALE * 1.5f;
		subImage[0]->SetScale().y = subImage[0]->imageSize.y * IMG_SCALE * 1.5f;
		subImage[0]->maxFrame.x = 2;
		subImage[0]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 18);
		subImage[0]->isVisible = true;
		subImage[0]->SetPivot() = OFFSET_B;
	}
	if (_serialName == OBJECT_SERIAL_NAME::KIRBY_BREATH)
	{
		LoadFile(L"kirby_breath.png");
		SetScale().x = imageSize.x * IMG_SCALE;
		SetScale().y = imageSize.y * IMG_SCALE;
		isVisible = false;
		collider = COLLIDER::CIRCLE;
		SetPivot() = OFFSET_B;
	}
}

void NeutralObj::Update()
{
	MoveWorldPos(dir * speed * DELTA);
	for (size_t i = 0; i < subImage.size(); i++)
	{
		subImage[i]->SetWorldPos(GetWorldPos() + DOWN * 16);
	}
	UPDATE_COLOR;
	if (serialName == OBJECT_SERIAL_NAME::STAR_BULLET)
	{
		if (WALL_AREA_LEFT || WALL_AREA_RIGHT)
		{
			SOUND->Stop("starbulletend");
			SOUND->Play("starbulletend");
			GameManager::ActiveEffect(this, UP * 4 * IMG_SCALE);
			isVisible = false;
			interactObjList.clear();
		}
	}
	if (serialName == OBJECT_SERIAL_NAME::STAR_BULLET_STRENGTH)
	{
		if (!(GetWorldPos().x > app.maincam->GetWorldPos().x - app.GetHalfWidth() * 1.15f &&
			GetWorldPos().x < app.maincam->GetWorldPos().x + app.GetHalfWidth() * 1.15f &&
			GetWorldPos().y > app.maincam->GetWorldPos().y - app.GetHalfHeight() * 1.15f &&
			GetWorldPos().y < app.maincam->GetWorldPos().y + app.GetHalfHeight() * 1.15f))
		{
			GameManager::ActiveEffect(this);
			isVisible = false;
			interactObjList.clear();
		}
	}
	if (serialName == OBJECT_SERIAL_NAME::KIRBY_BREATH)
	{
		if(lifeTime > 0)
			lifeTime -= DELTA;
		if (WALL_AREA_LEFT || WALL_AREA_RIGHT || INTERPOL_AREA_PULL_LEFT|| INTERPOL_AREA_PULL_RIGHT || lifeTime <= 0)
		{
			isVisible = false;
			interactObjList.clear();
		}
	}
}

void NeutralObj::DrawCall()
{
	if (isVisible)
	{
		for (size_t i = 0; i < subImage.size(); i++)
		{
			subImage[i]->Render();
		}
	}
	Render();
}

void NeutralObj::SetDirSpeed(Vector2 _dir, float _speed)
{
	 dir = _dir; speed = _speed; 
	 if (dir.x > 0)
	 {
		 if (GetScale().x < 0)
		 SetScale().x = GetScale().x * -1;
	 }
	 else
	 {
		 if (GetScale().x > 0)
		 SetScale().x = GetScale().x * -1;
	 }
	
}

