#pragma once

class Player;

class Enemy : public ObImage
{
public:
	int		hp;
	int		maxHp;
	bool	isInhole;
	bool	isStay;
	Vector2	initPos;
public:
	Enemy(Vector2 _initPos, int _maxHp, wstring imageFname) : hp(_maxHp), maxHp(_maxHp), isInhole(false), isStay(false), initPos(_initPos)
	{
		SetPivot() = OFFSET_B;
		LoadFile(imageFname);
		SetScale().x = imageSize.x * IMG_SCALE;
		SetScale().y = imageSize.y * IMG_SCALE;
		collider = COLLIDER::RECT;
	}
	void Init()
	{
		SetWorldPos(initPos);
		hp = maxHp;
	}
	void Update();
};