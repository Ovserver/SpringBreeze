#pragma once
#define MAX_APPLE_NUM 10
class WhispyWood : public Enemy
{
public:
	bool		isActive;
	float		atkTime;
	const float atkTime_Interval = 1.0f;
	float		pattern1_Time;
	const float pattern1_Time_Interval = 5.0f;
	float		pattern1_cooldown;
	const float	pattern1_cooldown_Interval = 0.3f;
public:
	WhispyWood();
	void Init();
	void Update();
	void LateUpdate() override;
	void Render();
	void UpdateSpritePos() override;
private:
	ObImage	enemy_ouch2;
	ObImage	enemy_over;
	ObRect	col;
	Enemy*	apples[MAX_APPLE_NUM];
};

