#pragma once
#define NUM_SPRITE_COUNT 12
enum class PlayerState
{
	NONE, MOVE, DASH, SLIDE, JUMP, OUCH, OVER
};

class Player : public ObImage
{
public:
	PlayerState	STATE;
	int			hp;

public:
	void Init();
	void Release() { delete[] mSprites; };
	void Update();
	void Render();
	void SpritePosUpdate();
	void Active(PlayerState state);
private:
	bool	isRight;
	bool	isJump;
	bool	isMove;
	bool	jumpable;
	float	comboCount;
	float	slideTime;
	float	upVector;

	ObImage** mSprites;
	ObImage kirby_none_L;
	ObImage kirby_none_R;
	ObImage kirby_move_L;
	ObImage kirby_move_R;
	ObImage kirby_dash_L;
	ObImage kirby_dash_R;
	ObImage kirby_slide_L;
	ObImage kirby_slide_R;
	ObImage kirby_jump_L;
	ObImage kirby_jump_R;
	ObImage kirby_ouch_L;
	ObImage kirby_ouch_R;

	ComboMap Dash_L;
	ComboMap Dash_R;
	ComboMap Slide_L;
	ComboMap Slide_R;
private:
	void UpdateMove();
};

