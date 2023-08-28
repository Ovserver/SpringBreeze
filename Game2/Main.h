#pragma once
#define NUM_FOOD_INSTANCE 20
#define NUM_PLANE 47
#define NUM_SCORETEXT 6
#define NUM_SAFETYTEXT 2

enum class FoodType {
	NONE, HP, SAFETYUP, DRIVE
};

struct Item {
	static const int FoodFrame = 17;
	ObImage image;
	FoodType type = FoodType::NONE;
	bool active = true;
};
class Main : public Scene
{
private:
	Player mainPlayer;

	ObImage bg1;
	ObImage plane[NUM_PLANE];
	ObImage planeImg[NUM_PLANE];
	ObImage	player;
	ObImage kirby_none_L;
	ObImage kirby_none_R;
	ObImage kirby_move_L;
	ObImage kirby_move_R;
	ObImage kirby_drive;
	ObImage kirby_slide;
	ObImage kirby_jump_L;
	ObImage kirby_jump_R;
	ObImage kirby_ouch;
	ObImage drive_effect;
	ObImage enemy;
	Item*	food;
	ObImage ui;
	Text	scoreText[NUM_SCORETEXT];
	Text	safetyText[NUM_SAFETYTEXT];
	ObRect	hpBar;
	ObRect	boostBar;
	ObImage	gameoverUI;
	int		score;
	float	maxHp = 100;
	float	hp;
public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
