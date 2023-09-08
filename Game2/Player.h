#pragma once
#define	PLAYER_MAX_HP 100
class Enemy;

enum class PLAYER_COPY_STATE
{
	NORMAL, BEAM, SWORD
};

enum class ANIM_GROUP_BEAM
{

};
enum class ANIM_GROUP_SWORD
{

};
enum class ANIM_GROUP_NORMAL
{
	IDLE,
	MOVE,
	DASH,
	CROUCH,
	SLIDE,
	JUMP,
	JUMPDOWN,
	FALLDOWN,
	OUCH,
	HOVER,
	HOVER_END,
	HOVER_OUCH,
	INHOLE,
	INHOLEIT,
	INHOLEIT_MOVE,
	INHOLEIT_DASH,
	INHOLEIT_JUMP,
	INHOLEIT_OUCH,
	CONSUME,
	SPITOUT,
	COPY,
	PORTAL,
	OVER,
};

class Player : public ObImage
{
public:
	bool				isPortaling;
	bool				testAnimFSM;
	int					hp;
	void*				currentAnimGroup;
	float				slideTime;
	const int			maxObjectNum = 5;
	Color				pointColor;
	PLAYER_COPY_STATE	copyState;
	ANIM_GROUP_NORMAL	STATE;
	vector<Enemy*>		inholeEnemyList;
	vector<NeutralObj*>	starBulletList;
	vector<NeutralObj*>	starBulletStrList;
	vector<NeutralObj*>	breathList;
public:
	void Init();
	void InitAnimState();
	void Release();
	void Update();
	void LateUpdate();
	void Render();
	void Damage(int value);
	void UpdateSpritePos();
	void UpdatePointColor(Stage* stage);
	void SetAnimGroup(PLAYER_COPY_STATE copyState);
private:

	bool		isRight;
	bool		isCrouch;
	bool		isJump;
	bool		isMove;
	bool		isDash;
	bool		isHovering;
	bool		isInhole;
	bool		isInholeIt;
	bool		jumpable;
	bool		lockInLeft;
	bool		lockInRight;
	float		deathTime = 1;
	const float	slideTimeInterval = 0.6f;
	float		slidePower;
	float		upVector;
	float		fowardVector;
	float		attackUpVector;
	float		attackFowardVector;
	const float	maxFowardVector = 1.5f;
	const float	maxFowardVectorDash = 2.0f;
	const float	maxFowardVectorSlide = 2.5f;
	float		cmdTime;
	const float	btweenCmdTime = 0.4f;
	float		consumeTime;
	const float	consumeTimeInterval = 0.3f;
	float		spitoutTime;
	const float	spitoutTimeInterval = 0.15f;
	float		invisibleTime;
	float		invisibleTimeInterval = 0.7f;
	float		attackTime;
	float		attackTimeInterval = 0.5f;
	ObRect	inholeArea;
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
	ObImage kirby_falldown_L;
	ObImage kirby_falldown_R;
	ObImage kirby_hover_L;
	ObImage kirby_hover_R;
	ObImage kirby_inhole_L;
	ObImage kirby_inhole_R;
	ObImage kirby_inholeIt_L;
	ObImage kirby_inholeIt_R;
	ObImage kirby_inholeIt_move_L;
	ObImage kirby_inholeIt_move_R;
	ObImage kirby_inholeIt_dash_L;
	ObImage kirby_inholeIt_dash_R;
	ObImage kirby_inholeIt_jump_L;
	ObImage kirby_inholeIt_jump_R;
	ObImage kirby_inholeIt_ouch_L;
	ObImage kirby_inholeIt_ouch_R;
	ObImage kirby_spitout_L;
	ObImage kirby_spitout_R;
	ObImage kirby_consume;
	ObImage kirby_ouch_L;
	ObImage kirby_ouch_R;
	ObImage kirby_portal_L;
	ObImage kirby_portal_R;

	ComboMap Dash_L;
	ComboMap Dash_R;
	ComboMap Slide;
private:
	void ChangeSprite(ObImage* sprite);
	void UpdateAnim();
	void UpdateAnimFSM();
	void ShootBreath()
	{
		for (size_t i = 0; i < breathList.size(); i++)
		{
			if (!breathList[i]->isVisible)
			{
				breathList[i]->SetWorldPos(GetWorldPos() + UP * 5 * IMG_SCALE + (isRight ? RIGHT : LEFT) * 10 * IMG_SCALE);
				breathList[i]->isVisible = true;
				breathList[i]->SetDirSpeed(isRight ? RIGHT : LEFT, 75.0f * IMG_SCALE);
				breathList[i]->lifeTime = 0.4f;
				return;
			}
		}
	}
};

