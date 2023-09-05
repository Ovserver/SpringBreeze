#pragma once
class WhispyWood : public Enemy
{
public:
	bool isActive;
	float atkTime;
	const float atkTimeInterval = 1.0f;
public:
	WhispyWood();
	void Init();
	void Update();
	void Render();
	void UpdateSpritePos() override;
private:
	ObImage	enemy_ouch2;
	ObImage	enemy_over;
	ObRect	col;
};

