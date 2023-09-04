#pragma once

#define AIR_AREA GameManager::IsColorMatch(pointColor, 255, 0, 255)					//Non-Render Color
#define WALL_AREA_LEFT GameManager::IsColorMatch(pointColor, 0, 255, 0)				//Green
#define WALL_AREA_RIGHT GameManager::IsColorMatch(pointColor, 0, 0, 255)			//Blue
#define LANDING_AREA GameManager::IsColorMatch(pointColor, 255, 0, 0)				//Red
#define INTERPOL_AREA_RISE GameManager::IsColorMatch(pointColor, 0, 0, 0)			//Black
#define INTERPOL_AREA_DESC_SLOPE GameManager::IsColorMatch(pointColor, 0, 255, 255)	//Sky
#define INTERPOL_AREA_DESC GameManager::IsColorMatch(pointColor, 128, 255, 255)		//Bright Sky
#define INTERPOL_AREA_PULL_LEFT GameManager::IsColorMatch(pointColor, 128, 255, 0)	//Grass
#define INTERPOL_AREA_PULL_RIGHT GameManager::IsColorMatch(pointColor, 128, 0, 255)	//Purple

class Enemy;

enum class PlayerCopyState
{
	NORMAL, BEAM, SWORD
};

enum class AnimGroupBeam
{

};
enum class AnimGroupNormal
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
	OVER
};

class Player : public ObImage
{
public:
	bool				testAnimFSM;
	int					hp;
	void*				currentAnimGroup;
	const int			maxStarBullet = 3;
	Color				pointColor;
	PlayerCopyState		copyState;
	AnimGroupNormal		STATE;
	vector<Enemy*>		inholeEnemyList;
	vector<NeutralObj*>	starBulletList;
public:
	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void Render();
	void UpdateSpritePos();
	void UpdatePointColor(Stage* stage);
	void SetAnimGroup(PlayerCopyState copyState);
private:

	bool	isRight;
	bool	isCrouch;
	bool	isJump;
	bool	isMove;
	bool	isDash;
	bool	isHovering;
	bool	isInhole;
	bool	isInholeIt;
	bool	jumpable;
	bool	lockInLeft;
	bool	lockInRight;
	float	slideTime;
	const float	slideTimeInterval = 0.6f;
	float	slidePower;
	float	upVector;
	float	fowardVector;
	float	cmdTime;
	const float	btweenCmdTime = 0.4f;
	float	consumeTime;
	const float	consumeTimeInterval = 0.5f;
	float	spitoutTime;
	const float	spitoutTimeInterval = 0.5f;

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
	ObImage kirby_spitout_L;
	ObImage kirby_spitout_R;
	ObImage kirby_consume;
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

