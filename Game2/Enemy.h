#pragma once
class Enemy : public ObImage
{
public:
	int		hp;
	int		maxHp;
	bool	isInhole;
	Vector2	initPos;
public:
	Enemy() : hp(100), maxHp(100), isInhole(false), initPos(UP) { LoadFile(L"empty.png"); }
	Enemy(Vector2 _initPos, int _maxHp, wstring imageFname) : hp(_maxHp), maxHp(_maxHp), isInhole(false), initPos(_initPos)
	{
		LoadFile(imageFname);
	}
};

