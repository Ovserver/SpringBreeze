#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"

void Player::Init()
{
	isRight = true;
	isCrouch = false;
	isJump = true;
	isMove = false;
	isDash = false;
	jumpable = true;
	slideTime = 0;
	slidePower = 1.8f;
	upVector = 0;
	fowardVector = 0;
	cmdTime = 0;
	STATE = PlayerState::IDLE;
	hp = 100;

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
	mSprites.push_back(&kirby_jump_L);
	mSprites.push_back(&kirby_jump_R);
	mSprites.push_back(&kirby_jumpdown_L);
	mSprites.push_back(&kirby_jumpdown_R);
	mSprites.push_back(&kirby_ouch_L);
	mSprites.push_back(&kirby_ouch_R);

	/*
	kirby_idle_L.SetParentT(*this);
	kirby_idle_R.SetParentT(*this);
	kirby_move_L.SetParentT(*this);
	kirby_move_R.SetParentT(*this);
	kirby_dash_L.SetParentT(*this);
	kirby_dash_R.SetParentT(*this);
	kirby_crouch_L.SetParentT(*this);
	kirby_crouch_R.SetParentT(*this);
	kirby_slide_L.SetParentT(*this);
	kirby_slide_R.SetParentT(*this);
	kirby_jump_L.SetParentT(*this);
	kirby_jump_R.SetParentT(*this);
	kirby_jumpdown_L.SetParentT(*this);
	kirby_jumpdown_R.SetParentT(*this);
	kirby_hover_L.SetParentT(*this);
	kirby_hover_R.SetParentT(*this);
	*/

	inholeArea.SetScale().x = 50 * IMG_SCALE;
	inholeArea.SetScale().y = 25 * IMG_SCALE;
	inholeArea.SetPivot() = OFFSET_B;
	inholeArea.collider = COLLIDER::RECT;
	inholeArea.isFilled = false;

	kirby_idle_L.LoadFile(L"kirby_none_L.png");
	kirby_idle_L.SetScale().x = kirby_idle_L.imageSize.x / 3.0f * IMG_SCALE;
	kirby_idle_L.SetScale().y = kirby_idle_L.imageSize.y * IMG_SCALE;
	kirby_idle_L.SetPivot() = OFFSET_B;
	kirby_idle_L.maxFrame.x = 3;
	kirby_idle_L.ChangeAnim(ANIMSTATE::REVERSE_LOOP, 1.0f / 3);
	kirby_idle_L.isVisible = false;

	kirby_idle_R.LoadFile(L"kirby_none_R.png");
	kirby_idle_R.SetScale().x = kirby_idle_L.imageSize.x / 3.0f * IMG_SCALE;
	kirby_idle_R.SetScale().y = kirby_idle_L.imageSize.y * IMG_SCALE;
	kirby_idle_R.SetPivot() = OFFSET_B;
	kirby_idle_R.maxFrame.x = 3;
	kirby_idle_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 3);
	//kirby_none_R.isVisible = false;

	kirby_move_L.LoadFile(L"kirby_move_L.png");
	kirby_move_L.SetScale().x = kirby_move_L.imageSize.x / 6.0f * IMG_SCALE;
	kirby_move_L.SetScale().y = kirby_move_L.imageSize.y * IMG_SCALE;
	kirby_move_L.SetPivot() = OFFSET_B;
	kirby_move_L.maxFrame.x = 6;
	kirby_move_L.ChangeAnim(ANIMSTATE::REVERSE_LOOP, 1.0f / 10);
	kirby_move_L.isVisible = false;

	kirby_move_R.LoadFile(L"kirby_move_R.png");
	kirby_move_R.SetScale().x = kirby_move_R.imageSize.x / 6.0f * IMG_SCALE;
	kirby_move_R.SetScale().y = kirby_move_R.imageSize.y * IMG_SCALE;
	kirby_move_R.SetPivot() = OFFSET_B;
	kirby_move_R.maxFrame.x = 6;
	kirby_move_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 10);
	kirby_move_R.isVisible = false;

	kirby_dash_L.LoadFile(L"kirby_dash_L.png");
	kirby_dash_L.SetScale().x = kirby_dash_L.imageSize.x / 6.0f * IMG_SCALE;
	kirby_dash_L.SetScale().y = kirby_dash_L.imageSize.y * IMG_SCALE;
	kirby_dash_L.SetPivot() = OFFSET_B;
	kirby_dash_L.maxFrame.x = 6;
	kirby_dash_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 18);
	kirby_dash_L.isVisible = false;

	kirby_dash_R.LoadFile(L"kirby_dash_R.png");
	kirby_dash_R.SetScale().x = kirby_dash_R.imageSize.x / 6.0f * IMG_SCALE;
	kirby_dash_R.SetScale().y = kirby_dash_R.imageSize.y * IMG_SCALE;
	kirby_dash_R.SetPivot() = OFFSET_B;
	kirby_dash_R.maxFrame.x = 6;
	kirby_dash_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 18);
	kirby_dash_R.isVisible = false;

	kirby_slide_L.LoadFile(L"kirby_slide_L.png");
	kirby_slide_L.SetScale().x = kirby_slide_L.imageSize.x * IMG_SCALE;
	kirby_slide_L.SetScale().y = kirby_slide_L.imageSize.y * IMG_SCALE;
	kirby_slide_L.SetPivot() = OFFSET_B;
	kirby_slide_L.isVisible = false;

	kirby_slide_R.LoadFile(L"kirby_slide_R.png");
	kirby_slide_R.SetScale().x = kirby_slide_R.imageSize.x * IMG_SCALE;
	kirby_slide_R.SetScale().y = kirby_slide_R.imageSize.y * IMG_SCALE;
	kirby_slide_R.SetPivot() = OFFSET_B;
	kirby_slide_R.isVisible = false;

	kirby_crouch_L.LoadFile(L"kirby_crouch_L.png");
	kirby_crouch_L.SetScale().x = kirby_crouch_L.imageSize.x * IMG_SCALE;
	kirby_crouch_L.SetScale().y = kirby_crouch_L.imageSize.y * IMG_SCALE;
	kirby_crouch_L.SetPivot() = OFFSET_B;
	kirby_crouch_L.isVisible = false;

	kirby_crouch_R.LoadFile(L"kirby_crouch_R.png");
	kirby_crouch_R.SetScale().x = kirby_crouch_R.imageSize.x * IMG_SCALE;
	kirby_crouch_R.SetScale().y = kirby_crouch_R.imageSize.y * IMG_SCALE;
	kirby_crouch_R.SetPivot() = OFFSET_B;
	kirby_crouch_R.isVisible = false;

	kirby_jump_L.LoadFile(L"kirby_jump_L.png");
	kirby_jump_L.SetScale().x = kirby_jump_L.imageSize.x / 5.0f * IMG_SCALE;
	kirby_jump_L.SetScale().y = kirby_jump_L.imageSize.y * IMG_SCALE;
	kirby_jump_L.SetPivot() = OFFSET_B;
	kirby_jump_L.uv.x = 1.0f / 5 * 4;
	kirby_jump_L.uv.z = 1;
	kirby_jump_L.isVisible = false;

	kirby_jump_R.LoadFile(L"kirby_jump_R.png");
	kirby_jump_R.SetScale().x = kirby_jump_R.imageSize.x / 5.0f * IMG_SCALE;
	kirby_jump_R.SetScale().y = kirby_jump_R.imageSize.y * IMG_SCALE;
	kirby_jump_R.SetPivot() = OFFSET_B;
	kirby_jump_R.uv.x = 0;
	kirby_jump_R.uv.z = 1.0f / 5;
	kirby_jump_R.isVisible = false;

	kirby_jumpdown_L.LoadFile(L"kirby_jump_L.png");
	kirby_jumpdown_L.SetScale().x = kirby_jumpdown_L.imageSize.x / 5.0f * IMG_SCALE;
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

	kirby_hover_L.LoadFile(L"kirby_hover_L.png");
	kirby_hover_L.SetScale().x = kirby_hover_L.imageSize.x / 2.0f * IMG_SCALE;
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

	kirby_inhole_L.LoadFile(L"kirby_inhole_L.png");
	kirby_inhole_L.SetScale().x = kirby_inhole_L.imageSize.x / 2.0f * IMG_SCALE;
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

	UpdatePointColor(GameManager::MainStage);
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
		upVector += DELTA * 10.0f;

		if (LANDING_AREA)
		{
			isJump = false;
			jumpable = true;
			isHovering = false;
			upVector = 0;
		}

		if (upVector > 0.5f && isHovering) upVector = 0.5f;

		if (AIR_AREA || DESCENT_INTERPOL_AREA)
		{
			MoveWorldPos(DOWN * DELTA * 100.0f * upVector);
		}

		if (cmdTime > 0)
			cmdTime -= DELTA;
		else
		{
			cmdTime = 0;
			MecanimManager::ComboClear();
		}
		if (slideTime > 0)
		{
			slideTime -= DELTA;
			//fowardVector *= slideTime / maxSlideTime;
		}
		else
			fowardVector = 0;

		MoveWorldPos(RIGHT * DELTA * 100.0f * fowardVector);
		// arrow up key
		if (INPUT->KeyDown(VK_UP)) { MecanimManager::ComboInput(VK_UP); cmdTime = btweenCmdTime; }

		// arrow down key
		if (INPUT->KeyDown(VK_DOWN)) { MecanimManager::ComboInput(VK_DOWN);	cmdTime = btweenCmdTime; }
		if (INPUT->KeyPress(VK_DOWN))
		{
			MecanimManager::ComboInput(VK_DOWN);
			isCrouch = true;
		}
		else isCrouch = false;

		// arrow left key & right key
		if (INPUT->KeyDown(VK_LEFT))
		{
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
		if (INPUT->KeyPress(VK_LEFT) && slideTime <= 0 && !isCrouch && !isInhole)
		{
			isRight = false;
			isMove = true;
			MoveWorldPos(LEFT * DELTA * 150.0f * (isDash / 2.0f + 1));

		}
		else if (INPUT->KeyPress(VK_RIGHT) && slideTime <= 0 && !isCrouch && !isInhole)
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
		while (GameManager::IsColorMatch(pointColor, 0, 255, 0))
		{
			MoveWorldPos(LEFT);
			UpdatePointColor(GameManager::MainStage);
		}
		while (GameManager::IsColorMatch(pointColor, 0, 0, 255))
		{
			MoveWorldPos(RIGHT);
			UpdatePointColor(GameManager::MainStage);
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
				slideTime = maxSlideTime;
				cmdTime = 0;
				if (isRight) fowardVector = slidePower;
				else fowardVector = -slidePower;
			}
			else if (AIR_AREA)
			{
				isHovering = true;
				jumpable = false;
				isJump = false;
				isDash = false;
			}
			else if (jumpable && slideTime <= 0) {
				MoveWorldPos(UP);
				MoveWorldPos(UP);
				isJump = true;
				jumpable = false;
				upVector = -4.6f;
				kirby_jumpdown_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				kirby_jumpdown_L.ChangeAnim(ANIMSTATE::REVERSE_ONCE, 1.0f / 12);
			}
			if (isHovering)
			{
				upVector = -2.0f;
				kirby_hover_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				kirby_hover_R.ChangeAnim(ANIMSTATE::REVERSE_ONCE, 1.0f / 12);
			}
		}
		// B key
		if (INPUT->KeyDown('B'))
		{
			if (isHovering)
			{
				isHovering = false;
			}
		}
		if (INPUT->KeyPress('B'))
		{
			if (!isHovering &&
				slideTime <= 0)
			{
				if (!isInhole)
				{
					kirby_inhole_L.ChangeAnim(ANIMSTATE::REVERSE_ONCE, 1.0f / 12);
					kirby_inhole_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
				}
				isInhole = true;
			}
		}
		else
		{
			if (isInhole)
			{
				if (!MAINSTAGE->InholeCheck())
					isInhole = false;
			}
		}
		if (isInhole) { MAINSTAGE->EnemyCollisionCheck(&inholeArea); }
		if (RISE_INTERPOL_AREA)
		{
			while (RISE_INTERPOL_AREA)
			{
				MoveWorldPos(UP);
				UpdatePointColor(MAINSTAGE);
			}
		}
		if (DESCENT_INTERPOL_AREA && !isJump)
		{
			while (DESCENT_INTERPOL_AREA)
			{
				MoveWorldPos(DOWN);
				UpdatePointColor(MAINSTAGE);
			}
		}		
		UpdateSpritePos();
	}
}

void Player::LateUpdate()
{
	UpdatePointColor(MAINSTAGE);
	UpdateAnimFSM();
	UpdateAnim();
}

void Player::Render()
{
	kirby_idle_L.Render();
	kirby_idle_R.Render();
	kirby_move_L.Render();
	kirby_move_R.Render();
	kirby_dash_L.Render();
	kirby_dash_R.Render();
	kirby_slide_L.Render();
	kirby_slide_R.Render();
	kirby_hover_L.Render();
	kirby_hover_R.Render();
	kirby_inhole_L.Render();
	kirby_inhole_R.Render();
	kirby_crouch_L.Render();
	kirby_crouch_R.Render();
	kirby_jump_L.Render();
	kirby_jump_R.Render();
	kirby_jumpdown_L.Render();
	kirby_jumpdown_R.Render();
	kirby_hover_L.Render();
	kirby_hover_R.Render();
	kirby_inhole_L.Render();
	kirby_inhole_R.Render();
	kirby_ouch_L.Render();
	kirby_ouch_R.Render();
	inholeArea.Render();
}

void Player::UpdateSpritePos()
{
	//UpdateMatrix();
	kirby_idle_L.SetWorldPos(GetWorldPos());
	kirby_idle_R.SetWorldPos(GetWorldPos());
	kirby_move_L.SetWorldPos(GetWorldPos());
	kirby_move_R.SetWorldPos(GetWorldPos());
	kirby_dash_L.SetWorldPos(GetWorldPos());
	kirby_dash_R.SetWorldPos(GetWorldPos());
	kirby_slide_L.SetWorldPos(GetWorldPos());
	kirby_slide_R.SetWorldPos(GetWorldPos());
	kirby_hover_L.SetWorldPos(GetWorldPos());
	kirby_hover_R.SetWorldPos(GetWorldPos());
	kirby_inhole_L.SetWorldPos(GetWorldPos());
	kirby_inhole_R.SetWorldPos(GetWorldPos());
	kirby_crouch_L.SetWorldPos(GetWorldPos());
	kirby_crouch_R.SetWorldPos(GetWorldPos());
	kirby_jump_L.SetWorldPos(GetWorldPos());
	kirby_jump_R.SetWorldPos(GetWorldPos());
	kirby_jumpdown_L.SetWorldPos(GetWorldPos());
	kirby_jumpdown_R.SetWorldPos(GetWorldPos());
	kirby_hover_L.SetWorldPos(GetWorldPos());
	kirby_hover_R.SetWorldPos(GetWorldPos());
	kirby_inhole_L.SetWorldPos(GetWorldPos());
	kirby_inhole_R.SetWorldPos(GetWorldPos());
	kirby_ouch_L.SetWorldPos(GetWorldPos());
	kirby_ouch_R.SetWorldPos(GetWorldPos());
	inholeArea.SetWorldPosX(GetWorldPos().x + 25 * IMG_SCALE);
	inholeArea.SetWorldPosY(GetWorldPos().y);
}

void Player::Active(PlayerState state)
{
	if (state == PlayerState::JUMP)
	{
		jumpable = false;
		upVector = -0.1f;
	}
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

	//if (GameManager::DebugMode)
		//cout << PixelPos.x << "  " << PixelPos.y << endl;
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
	switch (STATE)
	{
	case PlayerState::IDLE:
		if (isRight) ChangeSprite(&kirby_idle_R);
		else ChangeSprite(&kirby_idle_L);
		break;
	case PlayerState::MOVE:
		if (isRight) ChangeSprite(&kirby_move_R);
		else ChangeSprite(&kirby_move_L);
		break;
	case PlayerState::DASH:
		if (isRight) ChangeSprite(&kirby_dash_R);
		else ChangeSprite(&kirby_dash_L);
		break;
	case PlayerState::CROUCH:
		if (isRight) ChangeSprite(&kirby_crouch_R);
		else ChangeSprite(&kirby_crouch_L);
		break;
	case PlayerState::SLIDE:
		if (isRight) ChangeSprite(&kirby_slide_R);
		else ChangeSprite(&kirby_slide_L);
		break;
	case PlayerState::JUMP:
		if (isRight) ChangeSprite(&kirby_jump_R);
		else ChangeSprite(&kirby_jump_L);
		break;
	case PlayerState::JUMPDOWN:
		if (isRight) ChangeSprite(&kirby_jumpdown_R);
		else ChangeSprite(&kirby_jumpdown_L);
		break;
	case PlayerState::HOVER:
		if (isRight) ChangeSprite(&kirby_hover_R);
		else ChangeSprite(&kirby_hover_L);
		break;
	case PlayerState::INHOLE:
		if (isRight) ChangeSprite(&kirby_inhole_R);
		else ChangeSprite(&kirby_inhole_L);
		break;
	case PlayerState::OUCH:
		break;
	case PlayerState::OVER:
		break;
	default:
		break;
	}
}

void Player::UpdateAnimFSM()
{
	if (isInhole)
	{
		STATE = PlayerState::INHOLE;
	}
	else if (isJump)
	{
		if (upVector < -0.009)
			STATE = PlayerState::JUMP;
		else
			STATE = PlayerState::JUMPDOWN;
	}
	else if (isHovering)
	{
		STATE = PlayerState::HOVER;
	}
	else if (slideTime > 0)
	{
		STATE = PlayerState::SLIDE;
	}
	else if (isCrouch)
	{
		STATE = PlayerState::CROUCH;
	}
	else if (GameManager::IsColorMatch(pointColor, 255, 0, 255) || GameManager::IsColorMatch(pointColor, 0, 255, 0))
	{
		STATE = PlayerState::JUMPDOWN;
	}
	else if (isDash)
	{
		STATE = PlayerState::DASH;
	}
	else if (isMove)
	{
		STATE = PlayerState::MOVE;
	}
	else
	{
		STATE = PlayerState::IDLE;
	}
}
