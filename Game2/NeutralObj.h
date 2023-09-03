#pragma once
class NeutralObj : public ObImage
{
public:
	NeutralObj(wstring imageFname)
	{
		dir = Vector2(0, 0), speed = 0;
		LoadFile(imageFname);
		SetScale().x = imageSize.x * IMG_SCALE;
		SetScale().y = imageSize.y * IMG_SCALE;		
	}
	void Update();
	void SetDirSpeed(Vector2 _dir, float _speed) { dir = _dir; speed = _speed; }
private:
	Vector2	dir;
	float	speed;
};

