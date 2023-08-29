#pragma once
#define NUM_SPRITE_COUNT 12
enum class PlayerState
{
	IDLE, 
	MOVE,
	DASH, 
	CROUCH, 
	SLIDE,
	JUMP,
	JUMPDOWN,
	INHOLE,
	INHOLEIT,
	INHOLEIT_MOVE,
	INHOLEIT_JUMP,
	CONSUME,
	COPY,
	OUCH, 
	OVER
};

class Player : public ObImage
{
public:
	PlayerState	STATE;
	int			hp;

public:
	void Init();
	void Release() {};
	void Update();
	void LateUpdate();
	void Render();
	void UpdateSpritePos();
	void Active(PlayerState state);
private:
	bool	isRight;
	bool	isCrouch;
	bool	isJump;
	bool	isMove;
	bool	isDash;
	bool	isHovering;
	bool	isInhole;
	bool	jumpable;
	float	slideTime;
	float	upVector;
	float	fowardVector;
	float	cmdTime;
	const float	btweenCmdTime = 0.4f;

	vector<ObImage*> mSprites;
	ObImage kirby_idle_L;
	ObImage kirby_idle_R;
	ObImage kirby_move_L;
	ObImage kirby_move_R;
	ObImage kirby_dash_L;
	ObImage kirby_dash_R;
	ObImage kirby_crouch_L;
	ObImage kirby_crouch_R;
	ObImage kirby_slide_L;
	ObImage kirby_slide_R;
	ObImage kirby_jump_L;
	ObImage kirby_jump_R;
	ObImage kirby_jumpdown_L;
	ObImage kirby_jumpdown_R;
	ObImage kirby_hover_L;
	ObImage kirby_hover_R;
	ObImage kirby_inhole_L;
	ObImage kirby_inhole_R;
	ObImage kirby_ouch_L;
	ObImage kirby_ouch_R;

	ComboMap Dash_L;
	ComboMap Dash_R;
	ComboMap Slide;
private:
	void ChangeSprite(ObImage* sprite);
	void UpdateAnim();
	void UpdateAnimFSM();
};

