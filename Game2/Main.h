#pragma once
#define NUM_FOOD_INSTANCE 20
#define NUM_PLANE 47
#define NUM_SCORETEXT 6
#define NUM_SAFETYTEXT 2

enum StageColliderNum
{
	STAGE_1_1_GROUND = 8,
	STAGE_1_1_WALL_L = 5,
	STAGE_1_1_WALL_R = 3,
	STAGE_1_1_SLOPE = 1,
};

enum class FoodType {
	HP, FOOLHP, ONEUP
};

struct Item {
	static const int FoodFrame = 17;
	ObImage image;
	FoodType type = FoodType::HP;
	bool active = true;
};
class Main : public Scene
{
private:
	Player mainPlayer;
	ObImage	UI_normal;
	ObImage bg1;
	ObImage	bg1_sub;
	ObImage stage_1_1;
	ObImage stage_1_1_col;
	ObRect	stage_1_1_coll_ground[STAGE_1_1_GROUND];
	ObRect	stage_1_1_coll_wall_L[STAGE_1_1_WALL_L];
	ObRect	stage_1_1_coll_wall_R[STAGE_1_1_WALL_R];
	ObRect	stage_1_1_coll_slope[STAGE_1_1_SLOPE];
	Item* food;
	Text	scoreText[NUM_SCORETEXT];
	Text	safetyText[NUM_SAFETYTEXT];
	ObRect	HpBar;
	ObImage	leftWall;
	ObImage	rightWall;
	Camera	camUI;
	int		score;
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
