#include "stdafx.h"
#include "NeutralObj.h"
#include "GameManager.h"
#include "Player.h"
#include "Enemy.h"

void Player::Init()
{
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
	slidePower = 1.8f;
	upVector = 0;
	fowardVector = 0;
	cmdTime = 0;
	STATE = ANIM_GROUP_NORMAL::IDLE;
	hp = 100;

	collider = COLLIDER::RECT;
	SetPivot() = OFFSET_B;
	SetScale().x = 50 * IMG_SCALE;
	SetScale().y = 50 * IMG_SCALE;

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

	for (size_t i = 0; i < maxStarBullet; i++)
	{
		starBulletList.push_back(new NeutralObj(OBJECT_SERIAL_NAME::STAR_BULLET));
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
	kirby_move_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 10);
	kirby_move_L.isVisible = false;

	kirby_move_R.LoadFile(L"kirby_move_R.png");
	kirby_move_R.SetScale().x = kirby_move_R.imageSize.x / 6.0f * IMG_SCALE;
	kirby_move_R.SetScale().y = kirby_move_R.imageSize.y * IMG_SCALE;
	kirby_move_R.SetPivot() = OFFSET_B;
	kirby_move_R.maxFrame.x = 6;
	kirby_move_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 10);
	kirby_move_R.isVisible = false;

	kirby_dash_L.LoadFile(L"kirby_dash_test.png");
	kirby_dash_L.SetScale().x = kirby_dash_L.imageSize.x / 8.0f * IMG_SCALE * -1;
	kirby_dash_L.SetScale().y = kirby_dash_L.imageSize.y  * IMG_SCALE;
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

	kirby_ouch_L.LoadFile(L"riderkirby_attack.png");
	kirby_ouch_L.SetScale().x = kirby_ouch_L.imageSize.x / 4.0f * IMG_SCALE;
	kirby_ouch_L.SetScale().y = kirby_ouch_L.imageSize.y * IMG_SCALE;
	kirby_ouch_L.SetPivot() = OFFSET_B;
	kirby_ouch_L.maxFrame.x = 4;
	kirby_ouch_L.ChangeAnim(ANIMSTATE::LOOP, 1 / 24.0f);
	kirby_ouch_L.isVisible = false;

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
	//debug set
	if (GameManager::DebugMode)
	{
		if (INPUT->KeyPress(VK_UP))
			MoveWorldPos(UP * DELTA * 300.0f);
		if (INPUT->KeyPress(VK_DOWN))
			MoveWorldPos(DOWN * DELTA * 300.0f);
		if (INPUT->KeyPress(VK_LEFT))
			MoveWorldPos(LEFT * DELTA * 300.0f);
		if (INPUT->KeyPress(VK_RIGHT))
			MoveWorldPos(RIGHT * DELTA * 300.0f);
	}
	else
	{
		upVector += DELTA * 15.0f;

		if (LANDING_AREA && upVector > 0)
		{
			isJump = false;
			jumpable = true;
			isHovering = false;
			upVector = 0;
		}

		if (upVector > 0.5f && isHovering) upVector = 0.5f;
		else if (upVector > 3.5f) upVector = 3.5f;

		//if (AIR_AREA || INTERPOL_AREA_DESC_SLOPE || WALL_AREA_LEFT || WALL_AREA_RIGHT)
		{
			MoveWorldPos(DOWN * DELTA * 100.0f * upVector);
		}

		if (cmdTime > 0) cmdTime -= DELTA;	else { cmdTime = 0; MecanimManager::ComboClear(); }
		if (consumeTime > 0) consumeTime -= DELTA;
		if (spitoutTime > 0) spitoutTime -= DELTA;
		if (slideTime > 0) { slideTime -= DELTA; }
		else { fowardVector = 0; }

		MoveWorldPos(RIGHT * DELTA * 100.0f * fowardVector);
		// arrow up key
		if (INPUT->KeyDown(VK_UP))
		{
			if (MAINSTAGE->PortalCollisionCheck(this)) return;
			MecanimManager::ComboInput(VK_UP); cmdTime = btweenCmdTime;
		}

		// arrow down key
		if (INPUT->KeyDown(VK_DOWN)) {
			MecanimManager::ComboInput(VK_DOWN);
			cmdTime = btweenCmdTime;
			if (isInholeIt)
			{
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
				cmdTime = 0;
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
				cmdTime = 0;
			}
			cmdTime = btweenCmdTime;
		}
		if (INPUT->KeyPress(VK_LEFT))
		{
			if (!lockInLeft && consumeTime <= 0 && spitoutTime <= 0 && slideTime <= 0 && !isCrouch && !isInhole)
			{
				isRight = false;
				isMove = true;
				MoveWorldPos(LEFT * DELTA * 150.0f * (isDash / 2.0f + 1));
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
				MoveWorldPos(RIGHT * DELTA * 150.0f * (isDash / 2.0f + 1));
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
			}
			else if (jumpable && slideTime <= 0) {
				MoveWorldPos(UP);
				MoveWorldPos(UP);
				isJump = true;
				jumpable = false;
				upVector = -5.5f;
				kirby_jumpdown_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				kirby_jumpdown_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
			}
			if (isHovering)
			{
				upVector = -2.8f;
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
			}
			else if (isInholeIt)
			{
				spitoutTime = spitoutTimeInterval;
				isInholeIt = false;
				for (size_t i = 0; i < inholeEnemyList.size(); i++)
				{
					inholeEnemyList[i]->isStay = false;
				}
				inholeEnemyList.clear();
				for (size_t i = 0; i < maxStarBullet; i++)
				{
					if (!starBulletList[i]->isVisible)
					{
						starBulletList[i]->SetWorldPos(GetWorldPos() + Vector2(0, 10));
						starBulletList[i]->isVisible = true;
						starBulletList[i]->SetDirSpeed(isRight ? RIGHT : LEFT, 600.0f);
						break;
					}
				}

			}
			else if (isHovering)
			{
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
					isInhole = false;
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
						break;
					}
				}
			}
		}
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
			while (INTERPOL_AREA_PULL_LEFT)
			{
				MoveWorldPos(LEFT);
				UPDATE_COLOR;
			}
		}
		if (INTERPOL_AREA_PULL_RIGHT)
		{
			lockInLeft = true;
			while (INTERPOL_AREA_PULL_RIGHT)
			{
				MoveWorldPos(RIGHT);
				UPDATE_COLOR;
			}
		}
		UpdateSpritePos();
		for (size_t i = 0; i < maxStarBullet; i++)
		{
			if (starBulletList[i]->isVisible)
			{
				starBulletList[i]->Update();
				MAINSTAGE->EnemyCollisionCheck(starBulletList[i], COLLISION_CHECK_TYPE::ATTACK_BULLET_ONCE, 10);
			}
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
	inholeArea.Render();
	for (size_t i = 0; i < maxStarBullet; i++)
	{
		starBulletList[i]->Render();
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
	for (size_t i = 0; i < mSprites.size() - 1; i++)
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
		case ANIM_GROUP_NORMAL::CONSUME:
			ChangeSprite(&kirby_consume);
			break;
		case ANIM_GROUP_NORMAL::SPITOUT:
			if (isRight) ChangeSprite(&kirby_spitout_R);
			else ChangeSprite(&kirby_spitout_L);
			break;
		case ANIM_GROUP_NORMAL::OUCH:
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
