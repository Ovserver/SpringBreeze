#include "stdafx.h"
#include "NeutralObj.h"
#include "GameManager.h"
#include "MecanimManager.h"
#include "Player.h"
#include "Stage.h"
#include "UIManager.h"
#include "Enemy.h"

void Player::Init()
{
	isPortaling = false;
	testAnimFSM = true;
	currentAnimGroup = nullptr;
	copyState = PLAYER_COPY_STATE::NORMAL;
	SetAnimGroup(copyState);

	isRight = true;
	isCrouch = false;
	isJump = true;
	isMove = false;
	isDash = false;
	isHovering = false;
	isInhole = false;
	isInholeIt = false;
	jumpable = true;
	lockInLeft = false;
	lockInRight = false;
	slideTime = 0;
	consumeTime = 0;
	spitoutTime = 0;
	invisibleTime = 0;
	attackTime = 0;
	slidePower = 1.75f * IMG_SCALE;
	upVector = 0;
	fowardVector = 0;
	cmdTime = 0;
	STATE = ANIM_GROUP_NORMAL::IDLE;
	hp = PLAYER_MAX_HP;

	collider = COLLIDER::RECT;
	SetPivot() = OFFSET_B;
	SetScale().x = 24 * IMG_SCALE;
	SetScale().y = 24 * IMG_SCALE;

	mSprites.push_back(&kirby_idle_L);
	mSprites.push_back(&kirby_idle_R);
	mSprites.push_back(&kirby_move_L);
	mSprites.push_back(&kirby_move_R);
	mSprites.push_back(&kirby_dash_L);
	mSprites.push_back(&kirby_dash_R);
	mSprites.push_back(&kirby_slide_L);
	mSprites.push_back(&kirby_slide_R);
	mSprites.push_back(&kirby_hover_L);
	mSprites.push_back(&kirby_hover_R);
	mSprites.push_back(&kirby_crouch_L);
	mSprites.push_back(&kirby_crouch_R);
	mSprites.push_back(&kirby_inhole_L);
	mSprites.push_back(&kirby_inhole_R);
	mSprites.push_back(&kirby_inholeIt_L);
	mSprites.push_back(&kirby_inholeIt_R);
	mSprites.push_back(&kirby_inholeIt_move_L);
	mSprites.push_back(&kirby_inholeIt_move_R);
	mSprites.push_back(&kirby_inholeIt_dash_L);
	mSprites.push_back(&kirby_inholeIt_dash_R);
	mSprites.push_back(&kirby_inholeIt_jump_L);
	mSprites.push_back(&kirby_inholeIt_jump_R);
	mSprites.push_back(&kirby_inholeIt_ouch_L);
	mSprites.push_back(&kirby_inholeIt_ouch_R);
	mSprites.push_back(&kirby_spitout_L);
	mSprites.push_back(&kirby_spitout_R);
	mSprites.push_back(&kirby_consume);
	mSprites.push_back(&kirby_jump_L);
	mSprites.push_back(&kirby_jump_R);
	mSprites.push_back(&kirby_jumpdown_L);
	mSprites.push_back(&kirby_jumpdown_R);
	mSprites.push_back(&kirby_falldown_L);
	mSprites.push_back(&kirby_falldown_R);
	mSprites.push_back(&kirby_ouch_L);
	mSprites.push_back(&kirby_ouch_R);
	mSprites.push_back(&kirby_portal_L);
	mSprites.push_back(&kirby_portal_R);

	for (size_t i = 0; i < maxObjectNum; i++)
	{
		starBulletList.push_back(new NeutralObj(OBJECT_SERIAL_NAME::STAR_BULLET));
		starBulletStrList.push_back(new NeutralObj(OBJECT_SERIAL_NAME::STAR_BULLET_STRENGTH));
		breathList.push_back(new NeutralObj(OBJECT_SERIAL_NAME::KIRBY_BREATH));
	}

	inholeArea.SetScale().x = 50 * IMG_SCALE;
	inholeArea.SetScale().y = 25 * IMG_SCALE;
	inholeArea.SetPivot() = OFFSET_B;
	inholeArea.collider = COLLIDER::RECT;
	inholeArea.isFilled = false;

	//kirby_idle_L.LoadFile(L"kirby_none_R.png");
	//kirby_idle_L.SetScale().x = kirby_idle_L.imageSize.x / 3.0f * IMG_SCALE * -1;
	//kirby_idle_L.SetScale().y = kirby_idle_L.imageSize.y * IMG_SCALE;
	//kirby_idle_L.SetPivot() = OFFSET_B;
	//kirby_idle_L.maxFrame.x = 3;
	//kirby_idle_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 3);
	//kirby_idle_L.isVisible = false;

	kirby_idle_R.LoadFile(L"kirby_none_R.png");
	kirby_idle_R.SetScale().x = kirby_idle_R.imageSize.x / 3.0f * IMG_SCALE;
	kirby_idle_R.SetScale().y = kirby_idle_R.imageSize.y * IMG_SCALE;
	kirby_idle_R.SetPivot() = OFFSET_B;
	kirby_idle_R.maxFrame.x = 3;
	kirby_idle_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 3);
	//kirby_none_R.isVisible = false;

	kirby_move_L.LoadFile(L"kirby_move_R.png");
	kirby_move_L.SetScale().x = kirby_move_L.imageSize.x / 6.0f * IMG_SCALE * -1;
	kirby_move_L.SetScale().y = kirby_move_L.imageSize.y * IMG_SCALE;
	kirby_move_L.SetPivot() = OFFSET_B;
	kirby_move_L.maxFrame.x = 6;
	kirby_move_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	kirby_move_L.isVisible = false;

	kirby_move_R.LoadFile(L"kirby_move_R.png");
	kirby_move_R.SetScale().x = kirby_move_R.imageSize.x / 6.0f * IMG_SCALE;
	kirby_move_R.SetScale().y = kirby_move_R.imageSize.y * IMG_SCALE;
	kirby_move_R.SetPivot() = OFFSET_B;
	kirby_move_R.maxFrame.x = 6;
	kirby_move_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6);
	kirby_move_R.isVisible = false;

	kirby_dash_L.LoadFile(L"kirby_dash_test.png");
	kirby_dash_L.SetScale().x = kirby_dash_L.imageSize.x / 8.0f * IMG_SCALE * -1;
	kirby_dash_L.SetScale().y = kirby_dash_L.imageSize.y * IMG_SCALE;
	kirby_dash_L.SetPivot() = OFFSET_B;
	kirby_dash_L.maxFrame.x = 8;
	kirby_dash_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 18);
	kirby_dash_L.isVisible = false;

	kirby_dash_R.LoadFile(L"kirby_dash_test.png");
	kirby_dash_R.SetScale().x = kirby_dash_R.imageSize.x / 8.0f * IMG_SCALE;
	kirby_dash_R.SetScale().y = kirby_dash_R.imageSize.y * IMG_SCALE;
	kirby_dash_R.SetPivot() = OFFSET_B;
	kirby_dash_R.maxFrame.x = 8;
	kirby_dash_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 18);
	kirby_dash_R.isVisible = false;

	kirby_slide_L.LoadFile(L"kirby_slide_R.png");
	kirby_slide_L.SetScale().x = kirby_slide_L.imageSize.x * IMG_SCALE * -1;
	kirby_slide_L.SetScale().y = kirby_slide_L.imageSize.y * IMG_SCALE;
	kirby_slide_L.SetPivot() = OFFSET_B;
	kirby_slide_L.isVisible = false;

	kirby_slide_R.LoadFile(L"kirby_slide_R.png");
	kirby_slide_R.SetScale().x = kirby_slide_R.imageSize.x * IMG_SCALE;
	kirby_slide_R.SetScale().y = kirby_slide_R.imageSize.y * IMG_SCALE;
	kirby_slide_R.SetPivot() = OFFSET_B;
	kirby_slide_R.isVisible = false;

	kirby_crouch_L.LoadFile(L"kirby_crouch_R.png");
	kirby_crouch_L.SetScale().x = kirby_crouch_L.imageSize.x * IMG_SCALE * -1;
	kirby_crouch_L.SetScale().y = kirby_crouch_L.imageSize.y * IMG_SCALE;
	kirby_crouch_L.SetPivot() = OFFSET_B;
	kirby_crouch_L.isVisible = false;

	kirby_crouch_R.LoadFile(L"kirby_crouch_R.png");
	kirby_crouch_R.SetScale().x = kirby_crouch_R.imageSize.x * IMG_SCALE;
	kirby_crouch_R.SetScale().y = kirby_crouch_R.imageSize.y * IMG_SCALE;
	kirby_crouch_R.SetPivot() = OFFSET_B;
	kirby_crouch_R.isVisible = false;

	kirby_jump_L.LoadFile(L"kirby_jump_R.png");
	kirby_jump_L.SetScale().x = kirby_jump_L.imageSize.x / 5.0f * IMG_SCALE * -1;
	kirby_jump_L.SetScale().y = kirby_jump_L.imageSize.y * IMG_SCALE;
	kirby_jump_L.SetPivot() = OFFSET_B;
	kirby_jump_L.uv.x = 0;
	kirby_jump_L.uv.z = 1.0f / 5;
	kirby_jump_L.isVisible = false;

	kirby_jump_R.LoadFile(L"kirby_jump_R.png");
	kirby_jump_R.SetScale().x = kirby_jump_R.imageSize.x / 5.0f * IMG_SCALE;
	kirby_jump_R.SetScale().y = kirby_jump_R.imageSize.y * IMG_SCALE;
	kirby_jump_R.SetPivot() = OFFSET_B;
	kirby_jump_R.uv.x = 0;
	kirby_jump_R.uv.z = 1.0f / 5;
	kirby_jump_R.isVisible = false;

	kirby_jumpdown_L.LoadFile(L"kirby_jump_R.png");
	kirby_jumpdown_L.SetScale().x = kirby_jumpdown_L.imageSize.x / 5.0f * IMG_SCALE * -1;
	kirby_jumpdown_L.SetScale().y = kirby_jumpdown_L.imageSize.y * IMG_SCALE;
	kirby_jumpdown_L.SetPivot() = OFFSET_B;
	kirby_jumpdown_L.maxFrame.x = 5;
	kirby_jumpdown_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
	kirby_jumpdown_L.isVisible = false;

	kirby_jumpdown_R.LoadFile(L"kirby_jump_R.png");
	kirby_jumpdown_R.SetScale().x = kirby_jumpdown_R.imageSize.x / 5.0f * IMG_SCALE;
	kirby_jumpdown_R.SetScale().y = kirby_jumpdown_R.imageSize.y * IMG_SCALE;
	kirby_jumpdown_R.SetPivot() = OFFSET_B;
	kirby_jumpdown_R.maxFrame.x = 5;
	kirby_jumpdown_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
	kirby_jumpdown_R.isVisible = false;

	kirby_falldown_L.LoadFile(L"kirby_jump_R.png");
	kirby_falldown_L.SetScale().x = kirby_jumpdown_L.imageSize.x / 5.0f * IMG_SCALE * -1;
	kirby_falldown_L.SetScale().y = kirby_jumpdown_L.imageSize.y * IMG_SCALE;
	kirby_falldown_L.uv.x = 1.0f / 5 * 4;
	kirby_falldown_L.uv.z = 1;
	kirby_falldown_L.SetPivot() = OFFSET_B;
	kirby_falldown_L.isVisible = false;

	kirby_falldown_R.LoadFile(L"kirby_jump_R.png");
	kirby_falldown_R.SetScale().x = kirby_jumpdown_R.imageSize.x / 5.0f * IMG_SCALE;
	kirby_falldown_R.SetScale().y = kirby_jumpdown_R.imageSize.y * IMG_SCALE;
	kirby_falldown_R.uv.x = 1.0f / 5 * 4;
	kirby_falldown_R.uv.z = 1;
	kirby_falldown_R.SetPivot() = OFFSET_B;
	kirby_falldown_R.isVisible = false;

	kirby_hover_L.LoadFile(L"kirby_hover_R.png");
	kirby_hover_L.SetScale().x = kirby_hover_L.imageSize.x / 2.0f * IMG_SCALE * -1;
	kirby_hover_L.SetScale().y = kirby_hover_L.imageSize.y * IMG_SCALE;
	kirby_hover_L.SetPivot() = OFFSET_B;
	kirby_hover_L.maxFrame.x = 2;
	kirby_hover_L.isVisible = false;

	kirby_hover_R.LoadFile(L"kirby_hover_R.png");
	kirby_hover_R.SetScale().x = kirby_hover_R.imageSize.x / 2.0f * IMG_SCALE;
	kirby_hover_R.SetScale().y = kirby_hover_R.imageSize.y * IMG_SCALE;
	kirby_hover_R.SetPivot() = OFFSET_B;
	kirby_hover_R.maxFrame.x = 2;
	kirby_hover_R.isVisible = false;

	kirby_inhole_L.LoadFile(L"kirby_inhole_R.png");
	kirby_inhole_L.SetScale().x = kirby_inhole_L.imageSize.x / 2.0f * IMG_SCALE * -1;
	kirby_inhole_L.SetScale().y = kirby_inhole_L.imageSize.y * IMG_SCALE;
	kirby_inhole_L.SetPivot() = OFFSET_B;
	kirby_inhole_L.maxFrame.x = 2;
	kirby_inhole_L.isVisible = false;

	kirby_inhole_R.LoadFile(L"kirby_inhole_R.png");
	kirby_inhole_R.SetScale().x = kirby_inhole_R.imageSize.x / 2.0f * IMG_SCALE;
	kirby_inhole_R.SetScale().y = kirby_inhole_R.imageSize.y * IMG_SCALE;
	kirby_inhole_R.SetPivot() = OFFSET_B;
	kirby_inhole_R.maxFrame.x = 2;
	kirby_inhole_R.isVisible = false;

	kirby_inholeIt_L.LoadFile(L"kirby_inholeit_none.png");
	kirby_inholeIt_L.SetScale().x = kirby_inholeIt_L.imageSize.x * IMG_SCALE * -1;
	kirby_inholeIt_L.SetScale().y = kirby_inholeIt_L.imageSize.y * IMG_SCALE;
	kirby_inholeIt_L.SetPivot() = OFFSET_B;
	kirby_inholeIt_L.isVisible = false;

	kirby_inholeIt_R.LoadFile(L"kirby_inholeit_none.png");
	kirby_inholeIt_R.SetScale().x = kirby_inholeIt_R.imageSize.x * IMG_SCALE;
	kirby_inholeIt_R.SetScale().y = kirby_inholeIt_R.imageSize.y * IMG_SCALE;
	kirby_inholeIt_R.SetPivot() = OFFSET_B;
	kirby_inholeIt_R.isVisible = false;

	kirby_inholeIt_move_L.LoadFile(L"kirby_inholeit_move.png");
	kirby_inholeIt_move_L.SetScale().x = kirby_inholeIt_move_L.imageSize.x / 6.0f * IMG_SCALE * -1;
	kirby_inholeIt_move_L.SetScale().y = kirby_inholeIt_move_L.imageSize.y * IMG_SCALE;
	kirby_inholeIt_move_L.SetPivot() = OFFSET_B;
	kirby_inholeIt_move_L.maxFrame.x = 6;
	kirby_inholeIt_move_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
	kirby_inholeIt_move_L.isVisible = false;

	kirby_inholeIt_move_R.LoadFile(L"kirby_inholeit_move.png");
	kirby_inholeIt_move_R.SetScale().x = kirby_inholeIt_move_R.imageSize.x / 6.0f * IMG_SCALE;
	kirby_inholeIt_move_R.SetScale().y = kirby_inholeIt_move_R.imageSize.y * IMG_SCALE;
	kirby_inholeIt_move_R.SetPivot() = OFFSET_B;
	kirby_inholeIt_move_R.maxFrame.x = 6;
	kirby_inholeIt_move_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
	kirby_inholeIt_move_R.isVisible = false;

	kirby_inholeIt_dash_L.LoadFile(L"kirby_inholeit_move.png");
	kirby_inholeIt_dash_L.SetScale().x = kirby_inholeIt_dash_L.imageSize.x / 6.0f * IMG_SCALE * -1;
	kirby_inholeIt_dash_L.SetScale().y = kirby_inholeIt_dash_L.imageSize.y * IMG_SCALE;
	kirby_inholeIt_dash_L.SetPivot() = OFFSET_B;
	kirby_inholeIt_dash_L.maxFrame.x = 6;
	kirby_inholeIt_dash_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 24);
	kirby_inholeIt_dash_L.isVisible = false;

	kirby_inholeIt_dash_R.LoadFile(L"kirby_inholeit_move.png");
	kirby_inholeIt_dash_R.SetScale().x = kirby_inholeIt_dash_L.imageSize.x / 6.0f * IMG_SCALE;
	kirby_inholeIt_dash_R.SetScale().y = kirby_inholeIt_dash_L.imageSize.y * IMG_SCALE;
	kirby_inholeIt_dash_R.SetPivot() = OFFSET_B;
	kirby_inholeIt_dash_R.maxFrame.x = 6;
	kirby_inholeIt_dash_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 24);
	kirby_inholeIt_dash_R.isVisible = false;

	kirby_inholeIt_jump_L.LoadFile(L"kirby_inholeit_jump.png");
	kirby_inholeIt_jump_L.SetScale().x = kirby_inholeIt_jump_L.imageSize.x * IMG_SCALE * -1;
	kirby_inholeIt_jump_L.SetScale().y = kirby_inholeIt_jump_L.imageSize.y * IMG_SCALE;
	kirby_inholeIt_jump_L.SetPivot() = OFFSET_B;
	kirby_inholeIt_jump_L.isVisible = false;

	kirby_inholeIt_jump_R.LoadFile(L"kirby_inholeit_jump.png");
	kirby_inholeIt_jump_R.SetScale().x = kirby_inholeIt_jump_L.imageSize.x * IMG_SCALE;
	kirby_inholeIt_jump_R.SetScale().y = kirby_inholeIt_jump_L.imageSize.y * IMG_SCALE;
	kirby_inholeIt_jump_R.SetPivot() = OFFSET_B;
	kirby_inholeIt_jump_R.isVisible = false;

	kirby_inholeIt_ouch_L.LoadFile(L"kirby_inholeit_ouch.png");
	kirby_inholeIt_ouch_L.SetScale().x = kirby_inholeIt_ouch_L.imageSize.x * IMG_SCALE * -1;
	kirby_inholeIt_ouch_L.SetScale().y = kirby_inholeIt_ouch_L.imageSize.y * IMG_SCALE;
	kirby_inholeIt_ouch_L.SetPivot() = OFFSET_B;
	kirby_inholeIt_ouch_L.isVisible = false;

	kirby_inholeIt_ouch_R.LoadFile(L"kirby_inholeit_ouch.png");
	kirby_inholeIt_ouch_R.SetScale().x = kirby_inholeIt_ouch_R.imageSize.x * IMG_SCALE;
	kirby_inholeIt_ouch_R.SetScale().y = kirby_inholeIt_ouch_R.imageSize.y * IMG_SCALE;
	kirby_inholeIt_ouch_R.SetPivot() = OFFSET_B;
	kirby_inholeIt_ouch_R.isVisible = false;

	kirby_spitout_L.LoadFile(L"kirby_spitout.png");
	kirby_spitout_L.SetScale().x = kirby_spitout_L.imageSize.x / 2.0f * IMG_SCALE * -1;
	kirby_spitout_L.SetScale().y = kirby_spitout_L.imageSize.y * IMG_SCALE;
	kirby_spitout_L.SetPivot() = OFFSET_B;
	kirby_spitout_L.maxFrame.x = 2;
	kirby_spitout_L.isVisible = false;

	kirby_spitout_R.LoadFile(L"kirby_spitout.png");
	kirby_spitout_R.SetScale().x = kirby_spitout_R.imageSize.x / 2.0f * IMG_SCALE;
	kirby_spitout_R.SetScale().y = kirby_spitout_R.imageSize.y * IMG_SCALE;
	kirby_spitout_R.SetPivot() = OFFSET_B;
	kirby_spitout_R.maxFrame.x = 2;
	kirby_spitout_R.isVisible = false;

	kirby_consume.LoadFile(L"kirby_consume.png");
	kirby_consume.SetScale().x = kirby_consume.imageSize.x * IMG_SCALE;
	kirby_consume.SetScale().y = kirby_consume.imageSize.y / 3.0f * IMG_SCALE;
	kirby_consume.SetPivot() = OFFSET_B;
	kirby_consume.maxFrame.y = 3;
	kirby_consume.isVisible = false;

	kirby_ouch_L.LoadFile(L"kirby_ouch.png");
	kirby_ouch_L.SetScale().x = kirby_ouch_L.imageSize.x * IMG_SCALE * -1;
	kirby_ouch_L.SetScale().y = kirby_ouch_L.imageSize.y * IMG_SCALE;
	kirby_ouch_L.SetPivot() = OFFSET_B;
	kirby_ouch_L.isVisible = false;

	kirby_ouch_R.LoadFile(L"kirby_ouch.png");
	kirby_ouch_R.SetScale().x = kirby_ouch_R.imageSize.x * IMG_SCALE;
	kirby_ouch_R.SetScale().y = kirby_ouch_R.imageSize.y * IMG_SCALE;
	kirby_ouch_R.SetPivot() = OFFSET_B;
	kirby_ouch_R.isVisible = false;

	kirby_portal_L.LoadFile(L"kirby_portal.png");
	kirby_portal_L.SetScale().x = kirby_portal_L.imageSize.x / 5.0f * IMG_SCALE * -1;
	kirby_portal_L.SetScale().y = kirby_portal_L.imageSize.y * IMG_SCALE;
	kirby_portal_L.SetPivot() = OFFSET_B;
	kirby_portal_L.maxFrame.x = 5;
	kirby_portal_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 18);
	kirby_portal_L.isVisible = false;

	kirby_portal_R.LoadFile(L"kirby_portal.png");
	kirby_portal_R.SetScale().x = kirby_portal_R.imageSize.x / 5.0f * IMG_SCALE;
	kirby_portal_R.SetScale().y = kirby_portal_R.imageSize.y * IMG_SCALE;
	kirby_portal_R.SetPivot() = OFFSET_B;
	kirby_portal_R.maxFrame.x = 5;
	kirby_portal_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 18);
	kirby_portal_R.isVisible = false;

	Dash_L.comboMaps[0] = VK_LEFT;
	Dash_L.comboMaps[1] = VK_LEFT;
	Dash_L.comboLength = 2;

	Dash_R.comboMaps[0] = VK_RIGHT;
	Dash_R.comboMaps[1] = VK_RIGHT;
	Dash_R.comboLength = 2;

	Slide.comboMaps[0] = 'A';
	Slide.comboMaps[1] = VK_DOWN;
	Slide.comboLength = 2;
}

void Player::InitAnimState()
{
	isPortaling = false;
	fowardVector = 0;
	if (copyState == PLAYER_COPY_STATE::NORMAL)
	{
		ANIM_GROUP_NORMAL* temp = (ANIM_GROUP_NORMAL*)currentAnimGroup;
		*temp = ANIM_GROUP_NORMAL::IDLE;
	}
}

void Player::Release()
{
	for (size_t i = 0; i < inholeEnemyList.size(); i++)
	{
		delete inholeEnemyList[i];
	}
	inholeEnemyList.clear();
	for (size_t i = 0; i < starBulletList.size(); i++)
	{
		delete starBulletList[i];
	}
	starBulletList.clear();
}

void Player::Update()
{
	if (isPortaling)
	{
		if (hp <= 0)
		deathTime -= DELTA;
		if (deathTime <= 0)
		{
			UIManager::FadeScreen(false, L"empty.png", 0);
		}
	}
	else if (attackTime > 0)
	{
		attackUpVector += DELTA * 7.0f * IMG_SCALE;
		if (LANDING_AREA)
		{
			while (LANDING_AREA)
			{
				MoveWorldPos(UP);
				UPDATE_COLOR;
			}
			attackUpVector *= -1;
		}
		MoveWorldPos(DOWN * DELTA * 50.0f * attackUpVector * IMG_SCALE);
		MoveWorldPos(RIGHT * DELTA * 50.0f * attackFowardVector * IMG_SCALE);
		attackTime -= DELTA;
		jumpable = false;
		isJump = false;
		isHovering = false;
		upVector = 0;
		fowardVector = 0;
	}
	else
	{
		upVector += DELTA * (12.0f + 1.5f * IMG_SCALE);
		if (LANDING_AREA && upVector > 0)
		{
			isJump = false;
			jumpable = true;
			if (isHovering)
			{
				isHovering = false;
				SOUND->Stop("hoverend");
				SOUND->Play("hoverend");
				ShootBreath();
				spitoutTime = spitoutTimeInterval;
			}
			upVector = 0;
		}

		if (upVector > 0.4f * IMG_SCALE && isHovering) upVector = 0.4f * IMG_SCALE;
		else if (upVector > 1.75f * IMG_SCALE) upVector = 1.75f * IMG_SCALE;

		MoveWorldPos(DOWN * DELTA * 50.0f * upVector * IMG_SCALE);

		if (cmdTime > 0) cmdTime -= DELTA;	else { cmdTime = 0; MecanimManager::ComboClear(); }
		if (consumeTime > 0) consumeTime -= DELTA;
		if (spitoutTime > 0) spitoutTime -= DELTA;
		if (invisibleTime > 0) invisibleTime -= DELTA;
		if (slideTime > 0) { slideTime -= DELTA; }
		else if (slideTime < 0) { slideTime = 0; fowardVector = 0; }
		if (AIR_AREA) slideTime = 0;
		if (fowardVector > maxFowardVectorSlide) fowardVector = maxFowardVectorSlide;
		if (fowardVector < -maxFowardVectorSlide) fowardVector = -maxFowardVectorSlide;
		if (isDash)
		{
			if (fowardVector > maxFowardVectorDash) fowardVector = maxFowardVectorDash;
			if (fowardVector < -maxFowardVectorDash) fowardVector = -maxFowardVectorDash;
		}
		else if (isMove)
		{
			if (fowardVector > maxFowardVector) fowardVector = maxFowardVector;
			if (fowardVector < -maxFowardVector) fowardVector = -maxFowardVector;
		}
		if (!isMove && slideTime <= 0)
		{
			if (fowardVector > 0.03f)
				fowardVector -= DELTA * 2.5f * IMG_SCALE;
			else if (fowardVector < -0.03f)
				fowardVector += DELTA * 2.5f * IMG_SCALE;
			else
				fowardVector = 0;
		}
		MoveWorldPos(RIGHT * DELTA * 50.0f * fowardVector * IMG_SCALE);
		// arrow up key
		if (INPUT->KeyDown(VK_UP))
		{
			if (MAINSTAGE->PortalCollisionCheck(this))
			{
				isPortaling = true;
				kirby_portal_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 18);
				kirby_portal_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 18);
				if (copyState == PLAYER_COPY_STATE::NORMAL)
				{
					ANIM_GROUP_NORMAL* temp = (ANIM_GROUP_NORMAL*)currentAnimGroup;
					*temp = ANIM_GROUP_NORMAL::PORTAL;
				}
				return;
			}
			MecanimManager::ComboInput(VK_UP); cmdTime = btweenCmdTime;
		}

		// arrow down key
		if (INPUT->KeyDown(VK_DOWN)) {
			MecanimManager::ComboInput(VK_DOWN);
			cmdTime = btweenCmdTime;
			if (isInholeIt)
			{
				SOUND->Stop("swallow");
				SOUND->Play("swallow");
				isInholeIt = false;
				for (size_t i = 0; i < inholeEnemyList.size(); i++)
				{
					inholeEnemyList[i]->isStay = false;
				}
				inholeEnemyList.clear();
				consumeTime = consumeTimeInterval;
			}
		}
		if (INPUT->KeyPress(VK_DOWN))
		{
			MecanimManager::ComboInput(VK_DOWN);
			isCrouch = true;
		}
		else isCrouch = false;

		// arrow left key & right key
		if (INPUT->KeyDown(VK_LEFT))
		{
			lockInRight = false;
			if (isDash) isDash = false;
			MecanimManager::ComboInput(VK_LEFT);
			if (!isJump && btweenCmdTime > 0 && MecanimManager::ComboMatch(&Dash_L))
			{
				MecanimManager::ComboClear();
				isDash = true;
				SOUND->Stop("dash");
				SOUND->Play("dash");
			}
			cmdTime = btweenCmdTime;
		}
		if (INPUT->KeyDown(VK_RIGHT))
		{
			lockInLeft = false;
			if (isDash) isDash = false;
			MecanimManager::ComboInput(VK_RIGHT);
			if (!isJump && btweenCmdTime > 0 && MecanimManager::ComboMatch(&Dash_R))
			{
				MecanimManager::ComboClear();
				isDash = true;
				SOUND->Stop("dash");
				SOUND->Play("dash");
			}
			cmdTime = btweenCmdTime;
		}
		if (INPUT->KeyPress(VK_LEFT))
		{
			if (!lockInLeft && consumeTime <= 0 && spitoutTime <= 0 && slideTime <= 0 && !isCrouch && !isInhole)
			{
				isRight = false;
				isMove = true;
				if (isDash)
				{
					if (fowardVector >= -maxFowardVectorDash)
						fowardVector -= DELTA * 5 * IMG_SCALE;
				}
				else
				{
					if (fowardVector >= -maxFowardVector)
						fowardVector -= DELTA * 5 * IMG_SCALE;
				}
				//MoveWorldPos(LEFT * DELTA * 150.0f * (isDash / 2.0f + 1));
			}
			else
			{
				isDash = false;
				isMove = false;
			}
		}
		else if (INPUT->KeyPress(VK_RIGHT))
		{
			if (!lockInRight && consumeTime <= 0 && spitoutTime <= 0 && slideTime <= 0 && !isCrouch && !isInhole)
			{
				isRight = true;
				isMove = true;
				if (isDash)
				{
					if (fowardVector <= maxFowardVectorDash)
						fowardVector += DELTA * 5 * IMG_SCALE;
				}
				else
				{
					if (fowardVector <= maxFowardVector)
						fowardVector += DELTA * 5 * IMG_SCALE;
				}
			}
			else
			{
				isDash = false;
				isMove = false;
			}
		}
		else
		{
			isDash = false;
			isMove = false;
		}

		// A key
		if (INPUT->KeyDown('A'))
		{
			MecanimManager::ComboInput('A');
			if (btweenCmdTime > 0 &&
				!isMove &&
				!isJump &&
				slideTime <= 0 &&
				MecanimManager::ComboMatch(&Slide))
			{
				SOUND->Stop("slide");
				SOUND->Play("slide");
				MecanimManager::ComboClear();
				slideTime = slideTimeInterval;
				cmdTime = 0;
				if (isRight) fowardVector = slidePower;
				else fowardVector = -slidePower;
			}
			else if ((AIR_AREA || WALL_AREA_LEFT || WALL_AREA_RIGHT) && !isInholeIt && !isInhole)
			{
				isHovering = true;
				jumpable = false;
				isDash = false;
				SOUND->Stop("hover");
				SOUND->Play("hover");
			}
			else if (jumpable && slideTime <= 0) {
				SOUND->Stop("jump");
				SOUND->Play("jump");
				MoveWorldPos(UP);
				MoveWorldPos(UP);
				isJump = true;
				jumpable = false;
				upVector = -(5.0f + 0.25f * IMG_SCALE);
				kirby_jumpdown_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				kirby_jumpdown_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
			}
			if (isHovering)
			{
				SOUND->Stop("hover");
				SOUND->Play("hover");
				upVector = -(1.4f + 0.7f * IMG_SCALE);
				kirby_hover_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				kirby_hover_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
			}
		}
		if (AIR_AREA)
		{
			lockInLeft = false;
			lockInRight = false;
		}
		// B key

		if (INPUT->KeyDown('B'))
		{
			if (!isHovering &&
				!isInholeIt &&
				!isInhole &&
				slideTime <= 0 &&
				spitoutTime <= 0 &&
				consumeTime <= 0)
			{
				isInhole = true;
				SOUND->Stop("inhole");
				SOUND->Play("inhole");
			}
			else if (isInholeIt)
			{
				spitoutTime = spitoutTimeInterval;
				isInholeIt = false;
				for (size_t i = 0; i < inholeEnemyList.size(); i++)
				{
					inholeEnemyList[i]->isStay = false;
				}
				if (inholeEnemyList.size() >= 2)
				{
					for (size_t i = 0; i < maxObjectNum; i++)
					{
						if (!starBulletStrList[i]->isVisible)
						{
							starBulletStrList[i]->SetWorldPos(GetWorldPos() + Vector2(0, 10));
							starBulletStrList[i]->isVisible = true;
							starBulletStrList[i]->SetDirSpeed(isRight ? RIGHT : LEFT, 300.0f * IMG_SCALE);
							SOUND->Stop("spitout");
							SOUND->Play("spitout");
							break;
						}
					}
				}
				else
				{
					for (size_t i = 0; i < maxObjectNum; i++)
					{
						if (!starBulletList[i]->isVisible)
						{
							starBulletList[i]->SetWorldPos(GetWorldPos() + Vector2(0, 10));
							starBulletList[i]->isVisible = true;
							starBulletList[i]->SetDirSpeed(isRight ? RIGHT : LEFT, 250.0f * IMG_SCALE);
							SOUND->Stop("spitout");
							SOUND->Play("spitout");
							break;
						}
					}
				}
				inholeEnemyList.clear();

			}
			else if (isHovering)
			{
				SOUND->Stop("hoverend");
				SOUND->Play("hoverend");
				ShootBreath();
				spitoutTime = spitoutTimeInterval;
				isHovering = false;
			}
		}
		if (INPUT->KeyPress('B'))
		{

		}
		if (INPUT->KeyUp('B'))
		{
			if (isInhole)
			{
				if (!MAINSTAGE->EnemyInholingCheck()) // 빨아들이는 중인 적이 없을 때
				{
					isInhole = false;
					SOUND->Stop("inhole");
				}
			}
		}
		if (isInhole)
		{
			MAINSTAGE->EnemyCollisionCheck(&inholeArea, COLLISION_CHECK_TYPE::INHOLE);
			if (!MAINSTAGE->EnemyInholingCheck()) // 빨아들이는 중인 적이 없을 때
			{
				for (size_t i = 0; i < inholeEnemyList.size(); i++)
				{
					if (inholeEnemyList[i])
					{
						isInhole = false;
						isInholeIt = true;
						SOUND->Stop("inhole");
						SOUND->Stop("inholeit");
						SOUND->Play("inholeit");
						break;
					}
				}
			}
		}
	}
	MAINSTAGE->EnemyCollisionCheck(this, COLLISION_CHECK_TYPE::COLLISION_OBJECT);

	if (INTERPOL_AREA_RISE)
	{
		while (INTERPOL_AREA_RISE)
		{
			MoveWorldPos(UP);
			UPDATE_COLOR;
		}
	}
	if (INTERPOL_AREA_DESC_SLOPE && !isJump)
	{
		while (INTERPOL_AREA_DESC_SLOPE)
		{
			MoveWorldPos(DOWN);
			UPDATE_COLOR;
		}
	}
	if (INTERPOL_AREA_DESC)
	{
		while (INTERPOL_AREA_DESC)
		{
			MoveWorldPos(DOWN);
			UPDATE_COLOR;
		}
	}
	if (INTERPOL_AREA_PULL_LEFT)
	{
		lockInRight = true;
		fowardVector = 0;
		while (INTERPOL_AREA_PULL_LEFT)
		{
			MoveWorldPos(LEFT);
			UPDATE_COLOR;
		}
	}
	if (INTERPOL_AREA_PULL_RIGHT)
	{
		lockInLeft = true;
		fowardVector = 0;
		while (INTERPOL_AREA_PULL_RIGHT)
		{
			MoveWorldPos(RIGHT);
			UPDATE_COLOR;
		}
	}
	if (MAINSTAGE->mCamLock)
	{
		cout << app.maincam->GetWorldPos().x << "  " << app.maincam->GetWorldPos().y << endl;
		cout << GetWorldPos().x << "  " << GetWorldPos().y << endl;

		if (GetWorldPos().x < app.maincam->GetWorldPos().x - app.GetHalfWidth())
			SetWorldPosX(app.maincam->GetWorldPos().x - app.GetHalfWidth());
		//SetWorldPosX(-app.maincam->GetWorldPos().x);
		if (GetWorldPos().x > app.maincam->GetWorldPos().x + app.GetHalfWidth())
			SetWorldPosX(app.maincam->GetWorldPos().x + app.GetHalfWidth());
		//SetWorldPosX(app.maincam->GetWorldPos().x);
		if (GetWorldPos().y < app.maincam->GetWorldPos().y - app.GetHalfHeight())
			SetWorldPosY(app.maincam->GetWorldPos().y - app.GetHalfHeight());
		//SetWorldPosY(-app.maincam->GetWorldPos().y);
		if (GetWorldPos().y > app.maincam->GetWorldPos().y + app.GetHalfHeight())
			SetWorldPosY(app.maincam->GetWorldPos().y + app.GetHalfHeight());
		//SetWorldPosY(app.maincam->GetWorldPos().y);
	}
	UpdateSpritePos();
	for (size_t i = 0; i < maxObjectNum; i++)
	{
		if (starBulletStrList[i]->isVisible)
		{
			starBulletStrList[i]->Update();
			MAINSTAGE->EnemyCollisionCheck(starBulletStrList[i], COLLISION_CHECK_TYPE::ATTACK_BULLET_ASSAULT, 20);
		}
		if (starBulletList[i]->isVisible)
		{
			starBulletList[i]->Update();
			MAINSTAGE->EnemyCollisionCheck(starBulletList[i], COLLISION_CHECK_TYPE::ATTACK_BULLET_ONCE, 10);
		}
		if (breathList[i]->isVisible)
		{
			breathList[i]->Update();
			MAINSTAGE->EnemyCollisionCheck(breathList[i], COLLISION_CHECK_TYPE::ATTACK_BULLET_ONCE, 5, false);
		}
	}
}

void Player::LateUpdate()
{
	UPDATE_COLOR;
	UpdateAnimFSM();
	UpdateAnim();
}

void Player::Render()
{
	for (size_t i = 0; i < mSprites.size(); i++)
	{
		mSprites[i]->Render();
	}
	//inholeArea.Render();
	for (size_t i = 0; i < maxObjectNum; i++)
	{
		starBulletList[i]->DrawCall();
		starBulletStrList[i]->DrawCall();
		breathList[i]->DrawCall();
	}
}

void Player::Damage(int value)
{
	if (invisibleTime <= 0)
	{
		hp -= value;
		invisibleTime = invisibleTimeInterval;
		attackTime = attackTimeInterval;
		SOUND->Stop("ouch");
		SOUND->Play("ouch");
		invisibleTimeInterval = 0.65f;
		attackUpVector = -0.6f * IMG_SCALE;
		if (!isRight)
			attackFowardVector = 0.9f * IMG_SCALE;
		else
			attackFowardVector = -0.9f * IMG_SCALE;
		if (copyState == PLAYER_COPY_STATE::NORMAL)
		{
			ANIM_GROUP_NORMAL* temp = (ANIM_GROUP_NORMAL*)currentAnimGroup;
			if (isInholeIt)
				*temp = ANIM_GROUP_NORMAL::INHOLEIT_OUCH;
			else
				*temp = ANIM_GROUP_NORMAL::OUCH;
		}
		if (hp <= 0)
		{
			SOUND->Stop(MAINSTAGE->mBGMkey);
			SOUND->Play("healthover");
			isPortaling = true;
			deathTime = 3.0f;
		}
	}
}

void Player::UpdateSpritePos()
{
	for (size_t i = 0; i < mSprites.size(); i++)
	{
		mSprites[i]->SetWorldPos(GetWorldPos());
	}
	inholeArea.SetWorldPosX(GetWorldPos().x + (isRight ? 1 : -1) * 25 * IMG_SCALE);
	inholeArea.SetWorldPosY(GetWorldPos().y);
}

void Player::UpdatePointColor(Stage* stage)
{
	ObImage* stageInfo = stage->mCollider;
	wstring fileName = stage->mColFName;

	Vector2 PixelPos = GetWorldPos() - stageInfo->GetWorldPos();
	PixelPos /= IMG_SCALE;

	// boundary values [X (0 ~ imageSize.x), Y (0 ~ imageSize.y)]
	if (PixelPos.x < 0) PixelPos.x = 0;
	if (PixelPos.x > stageInfo->imageSize.x) PixelPos.x = stageInfo->imageSize.x;
	if (PixelPos.y > 0) PixelPos.y = 0;
	if (PixelPos.y < 0) PixelPos.y *= -1;
	if (PixelPos.y > stageInfo->imageSize.y) PixelPos.y = stageInfo->imageSize.y;

	// GetPixels() : it's 0,0 Pixels pointer. is uInt8(1byte)
	// PixelPos.x  : 1Pixel is 32bit(RGBA) but, layout info(BGRA)
	// PixelPos.y  : Access the next row ->	Add all pixels from the previous row
	pointColor.w = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4) + 3);
	pointColor.x = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4) + 2);
	pointColor.y = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4) + 1);
	pointColor.z = (UINT8) * ((TEXTURE->GetTextureData(fileName).GetPixels() + (int)PixelPos.x * 4 + (int)PixelPos.y * stageInfo->imageSize.x * 4));
}

void Player::SetAnimGroup(PLAYER_COPY_STATE copyState)
{
	if (currentAnimGroup)
		delete currentAnimGroup;
	switch (copyState)
	{
	case PLAYER_COPY_STATE::NORMAL:
		currentAnimGroup = new ANIM_GROUP_NORMAL();
		break;
	case PLAYER_COPY_STATE::BEAM:
		currentAnimGroup = new ANIM_GROUP_BEAM();
		break;
	case PLAYER_COPY_STATE::SWORD:
		currentAnimGroup = new ANIM_GROUP_SWORD();
		break;
	default:
		break;
	}
}

void Player::ChangeSprite(ObImage* sprite)
{
	for (size_t i = 0; i < mSprites.size(); i++)
	{
		if (mSprites[i] == sprite)
			mSprites[i]->isVisible = true;
		else
			mSprites[i]->isVisible = false;
	}
}

void Player::UpdateAnim()
{
	if (copyState == PLAYER_COPY_STATE::NORMAL)
	{
		ANIM_GROUP_NORMAL* tmpSTATE = static_cast<ANIM_GROUP_NORMAL*>(currentAnimGroup);
		switch (*tmpSTATE)
		{
		case ANIM_GROUP_NORMAL::IDLE:
			if (isRight) { ChangeSprite(&kirby_idle_R); kirby_idle_R.SetRotation().y = 0; }
			else { ChangeSprite(&kirby_idle_R); kirby_idle_R.SetRotation().y = 180 * ToRadian; };
			break;
		case ANIM_GROUP_NORMAL::MOVE:
			if (isRight) ChangeSprite(&kirby_move_R);
			else ChangeSprite(&kirby_move_L);
			break;
		case ANIM_GROUP_NORMAL::DASH:
			if (isRight) ChangeSprite(&kirby_dash_R);
			else ChangeSprite(&kirby_dash_L);
			break;
		case ANIM_GROUP_NORMAL::CROUCH:
			if (isRight) ChangeSprite(&kirby_crouch_R);
			else ChangeSprite(&kirby_crouch_L);
			break;
		case ANIM_GROUP_NORMAL::SLIDE:
			if (isRight) ChangeSprite(&kirby_slide_R);
			else ChangeSprite(&kirby_slide_L);
			break;
		case ANIM_GROUP_NORMAL::JUMP:
			if (isRight) ChangeSprite(&kirby_jump_R);
			else ChangeSprite(&kirby_jump_L);
			break;
		case ANIM_GROUP_NORMAL::JUMPDOWN:
			if (isRight) ChangeSprite(&kirby_jumpdown_R);
			else ChangeSprite(&kirby_jumpdown_L);
			break;
		case ANIM_GROUP_NORMAL::FALLDOWN:
			if (isRight) ChangeSprite(&kirby_falldown_R);
			else ChangeSprite(&kirby_falldown_L);
			break;
		case ANIM_GROUP_NORMAL::HOVER:
			if (isRight) ChangeSprite(&kirby_hover_R);
			else ChangeSprite(&kirby_hover_L);
			break;
		case ANIM_GROUP_NORMAL::INHOLE:
			if (isRight) ChangeSprite(&kirby_inhole_R);
			else ChangeSprite(&kirby_inhole_L);
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT:
			if (isRight) ChangeSprite(&kirby_inholeIt_R);
			else ChangeSprite(&kirby_inholeIt_L);
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT_MOVE:
			if (isRight) ChangeSprite(&kirby_inholeIt_move_R);
			else ChangeSprite(&kirby_inholeIt_move_L);
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT_DASH:
			if (isRight) ChangeSprite(&kirby_inholeIt_dash_R);
			else ChangeSprite(&kirby_inholeIt_dash_L);
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT_JUMP:
			if (isRight) ChangeSprite(&kirby_inholeIt_jump_R);
			else ChangeSprite(&kirby_inholeIt_jump_L);
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT_OUCH:
			if (isRight) ChangeSprite(&kirby_inholeIt_ouch_R);
			else ChangeSprite(&kirby_inholeIt_ouch_L);
			break;
		case ANIM_GROUP_NORMAL::CONSUME:
			ChangeSprite(&kirby_consume);
			break;
		case ANIM_GROUP_NORMAL::SPITOUT:
			if (isRight) ChangeSprite(&kirby_spitout_R);
			else ChangeSprite(&kirby_spitout_L);
			break;
		case ANIM_GROUP_NORMAL::OUCH:
			if (isRight) ChangeSprite(&kirby_ouch_R);
			else ChangeSprite(&kirby_ouch_L);
			break;
		case ANIM_GROUP_NORMAL::PORTAL:
			if (isRight) ChangeSprite(&kirby_portal_R);
			else ChangeSprite(&kirby_portal_L);
			break;
		case ANIM_GROUP_NORMAL::OVER:
			break;
		default:
			break;
		}
	}
}

void Player::UpdateAnimFSM()
{
	if (copyState == PLAYER_COPY_STATE::NORMAL)
	{
		ANIM_GROUP_NORMAL* tmpSTATE = static_cast<ANIM_GROUP_NORMAL*>(currentAnimGroup);
		switch (*tmpSTATE)
		{
		case ANIM_GROUP_NORMAL::IDLE:
			if (isInhole)
			{
				*tmpSTATE = ANIM_GROUP_NORMAL::INHOLE;
				kirby_inhole_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				kirby_inhole_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
			}
			else if (isInholeIt) *tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT;
			else if (isJump) *tmpSTATE = ANIM_GROUP_NORMAL::JUMP;
			else if (AIR_AREA) *tmpSTATE = ANIM_GROUP_NORMAL::FALLDOWN;
			else if (isDash) *tmpSTATE = ANIM_GROUP_NORMAL::DASH;
			else if (isMove) *tmpSTATE = ANIM_GROUP_NORMAL::MOVE;
			else if (isCrouch) *tmpSTATE = ANIM_GROUP_NORMAL::CROUCH;
			break;
		case ANIM_GROUP_NORMAL::MOVE:
			if (isJump) *tmpSTATE = ANIM_GROUP_NORMAL::JUMP;
			else if (AIR_AREA) *tmpSTATE = ANIM_GROUP_NORMAL::FALLDOWN;
			else if (!isMove) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			break;
		case ANIM_GROUP_NORMAL::DASH:
			if (isJump) *tmpSTATE = ANIM_GROUP_NORMAL::JUMP;
			else if (AIR_AREA) *tmpSTATE = ANIM_GROUP_NORMAL::FALLDOWN;
			else if (!isDash) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			break;
		case ANIM_GROUP_NORMAL::CROUCH:
			if (slideTime > 0) *tmpSTATE = ANIM_GROUP_NORMAL::SLIDE;
			else if (AIR_AREA) *tmpSTATE = ANIM_GROUP_NORMAL::FALLDOWN;
			else if (!isCrouch) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			break;
		case ANIM_GROUP_NORMAL::SLIDE:
			if (slideTime <= 0) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			break;
		case ANIM_GROUP_NORMAL::JUMP:
			if (isInhole) {
				*tmpSTATE = ANIM_GROUP_NORMAL::INHOLE;
				kirby_inhole_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				kirby_inhole_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
			}
			else if (isHovering) *tmpSTATE = ANIM_GROUP_NORMAL::HOVER;
			else if (upVector > -0.009f) *tmpSTATE = ANIM_GROUP_NORMAL::JUMPDOWN;
			else if (!isJump) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			break;
		case ANIM_GROUP_NORMAL::JUMPDOWN:
			if (isInhole) {
				*tmpSTATE = ANIM_GROUP_NORMAL::INHOLE;
				kirby_inhole_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				kirby_inhole_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
			}
			else if (isHovering) *tmpSTATE = ANIM_GROUP_NORMAL::HOVER;
			else if (!isJump) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			else if (upVector > 5.0f) *tmpSTATE = ANIM_GROUP_NORMAL::FALLDOWN;
			break;
		case ANIM_GROUP_NORMAL::FALLDOWN:
			if (isInhole) {
				*tmpSTATE = ANIM_GROUP_NORMAL::INHOLE;
				kirby_inhole_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				kirby_inhole_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
			}
			else if (isHovering) *tmpSTATE = ANIM_GROUP_NORMAL::HOVER;
			else if (!AIR_AREA) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			break;
		case ANIM_GROUP_NORMAL::OUCH:
			if (attackTime <= 0) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			break;
		case ANIM_GROUP_NORMAL::HOVER:
			if (!isHovering)
			{
				if (spitoutTime > 0)
				{
					*tmpSTATE = ANIM_GROUP_NORMAL::SPITOUT;
					kirby_spitout_L.ChangeAnim(ANIMSTATE::ONCE, 1 / 12.0f);
					kirby_spitout_R.ChangeAnim(ANIMSTATE::ONCE, 1 / 12.0f);
				}
				else
					*tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			}
			break;
		case ANIM_GROUP_NORMAL::HOVER_END:
			break;
		case ANIM_GROUP_NORMAL::HOVER_OUCH:
			break;
		case ANIM_GROUP_NORMAL::INHOLE:
			if (isInholeIt) *tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT;
			else if (!isInhole) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT:
			if (!isInholeIt)
			{
				if (consumeTime > 0) {
					*tmpSTATE = ANIM_GROUP_NORMAL::CONSUME;
					kirby_consume.ChangeAnim(ANIMSTATE::ONCE, 1 / 12.0f, false);
				}
				else {
					*tmpSTATE = ANIM_GROUP_NORMAL::SPITOUT;
					kirby_spitout_L.ChangeAnim(ANIMSTATE::ONCE, 1 / 12.0f);
					kirby_spitout_R.ChangeAnim(ANIMSTATE::ONCE, 1 / 12.0f);
				}
			}
			else if (isJump)	*tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT_JUMP;
			else if (isDash)	*tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT_DASH;
			else if (isMove)	*tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT_MOVE;
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT_MOVE:
			if (isJump) *tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT_JUMP;
			else if (!isMove) *tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT;
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT_DASH:
			if (isJump) *tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT_JUMP;
			else if (!isDash) *tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT;
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT_JUMP:
			if (spitoutTime > 0) {
				*tmpSTATE = ANIM_GROUP_NORMAL::SPITOUT;
				kirby_spitout_L.ChangeAnim(ANIMSTATE::ONCE, 1 / 12.0f);
				kirby_spitout_R.ChangeAnim(ANIMSTATE::ONCE, 1 / 12.0f);
			}
			else if (!isJump) *tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT;
			break;
		case ANIM_GROUP_NORMAL::INHOLEIT_OUCH:
			if (attackTime <= 0) *tmpSTATE = ANIM_GROUP_NORMAL::INHOLEIT;
			break;
		case ANIM_GROUP_NORMAL::CONSUME:
			if (consumeTime <= 0) *tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			break;
		case ANIM_GROUP_NORMAL::SPITOUT:
			if (spitoutTime <= 0)
			{
				if (AIR_AREA)
					*tmpSTATE = ANIM_GROUP_NORMAL::FALLDOWN;
				else
					*tmpSTATE = ANIM_GROUP_NORMAL::IDLE;
			}
			break;
		case ANIM_GROUP_NORMAL::COPY:
			break;
		case ANIM_GROUP_NORMAL::OVER:
			break;
		default:
			break;
		}
	}
}
