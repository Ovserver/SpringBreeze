#pragma once
class Bullet : public ObCircle
{
	float speed;
	Vector2 fireDir;

	float speed2;
	Vector2 fireDir2;
public:
	float lifeTime;
	bool  active;
	Bullet();
	void Init(Vector2 FirePos, float rotation, float power);		//√ ±‚»≠
	void Update();
};



