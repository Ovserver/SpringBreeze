#include "stdafx.h"
#include "MecanimManager.h"
#include "Player.h"

void Player::Init()
{
	isRight = true;
	isCrouch = false;
	isJump = false;
	isMove = false;
	isDash = false;
	jumpable = true;
	slideTime = 0;
	upVector = 0;
	fowardVector = 0;
	cmdTime = 0;
	STATE = PlayerState::NONE;
	hp = 100;

	mSprites.push_back(&kirby_none_L);
	mSprites.push_back(&kirby_none_L);
	mSprites.push_back(&kirby_none_R);
	mSprites.push_back(&kirby_move_L);
	mSprites.push_back(&kirby_move_R);
	mSprites.push_back(&kirby_dash_L);
	mSprites.push_back(&kirby_dash_R);
	mSprites.push_back(&kirby_slide_L);
	mSprites.push_back(&kirby_slide_R);
	mSprites.push_back(&kirby_crouch_L);
	mSprites.push_back(&kirby_crouch_R);
	mSprites.push_back(&kirby_jump_L);
	mSprites.push_back(&kirby_jump_R);
	mSprites.push_back(&kirby_ouch_L);
	mSprites.push_back(&kirby_ouch_R);

	kirby_none_L.LoadFile(L"kirby_none_L.png");
	kirby_none_L.SetScale().x = kirby_none_L.imageSize.x / 3.0f * VALUE_SCALE_IMG;
	kirby_none_L.SetScale().y = kirby_none_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_none_L.SetPivot() = OFFSET_B;
	kirby_none_L.maxFrame.x = 3;
	kirby_none_L.ChangeAnim(ANIMSTATE::REVERSE_LOOP, 1.0f / 3);
	kirby_none_L.isVisible = false;

	kirby_none_R.LoadFile(L"kirby_none_R.png");
	kirby_none_R.SetScale().x = kirby_none_L.imageSize.x / 3.0f * VALUE_SCALE_IMG;
	kirby_none_R.SetScale().y = kirby_none_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_none_R.SetPivot() = OFFSET_B;
	kirby_none_R.maxFrame.x = 3;
	kirby_none_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 3);
	//kirby_none_R.isVisible = false;

	kirby_move_L.LoadFile(L"kirby_move_L.png");
	kirby_move_L.SetScale().x = kirby_move_L.imageSize.x / 6.0f * VALUE_SCALE_IMG;
	kirby_move_L.SetScale().y = kirby_move_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_move_L.SetPivot() = OFFSET_B;
	kirby_move_L.maxFrame.x = 6;
	kirby_move_L.ChangeAnim(ANIMSTATE::REVERSE_LOOP, 1.0f / 12);
	kirby_move_L.isVisible = false;

	kirby_move_R.LoadFile(L"kirby_move_R.png");
	kirby_move_R.SetScale().x = kirby_move_R.imageSize.x / 6.0f * VALUE_SCALE_IMG;
	kirby_move_R.SetScale().y = kirby_move_R.imageSize.y * VALUE_SCALE_IMG;
	kirby_move_R.SetPivot() = OFFSET_B;
	kirby_move_R.maxFrame.x = 6;
	kirby_move_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
	kirby_move_R.isVisible = false;

	kirby_dash_L.LoadFile(L"kirby_dash_L.png");
	kirby_dash_L.SetScale().x = kirby_dash_L.imageSize.x / 6.0f * VALUE_SCALE_IMG;
	kirby_dash_L.SetScale().y = kirby_dash_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_dash_L.SetPivot() = OFFSET_B;
	kirby_dash_L.maxFrame.x = 6;
	kirby_dash_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
	kirby_dash_L.isVisible = false;

	kirby_dash_R.LoadFile(L"kirby_dash_R.png");
	kirby_dash_R.SetScale().x = kirby_dash_R.imageSize.x / 6.0f * VALUE_SCALE_IMG;
	kirby_dash_R.SetScale().y = kirby_dash_R.imageSize.y * VALUE_SCALE_IMG;
	kirby_dash_R.SetPivot() = OFFSET_B;
	kirby_dash_R.maxFrame.x = 6;
	kirby_dash_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
	kirby_dash_R.isVisible = false;

	kirby_slide_L.LoadFile(L"kirby_slide_L.png");
	kirby_slide_L.SetScale().x = kirby_slide_L.imageSize.x * VALUE_SCALE_IMG;
	kirby_slide_L.SetScale().y = kirby_slide_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_slide_L.SetPivot() = OFFSET_B;
	kirby_slide_L.isVisible = false;

	kirby_slide_R.LoadFile(L"kirby_slide_R.png");
	kirby_slide_R.SetScale().x = kirby_slide_R.imageSize.x * VALUE_SCALE_IMG;
	kirby_slide_R.SetScale().y = kirby_slide_R.imageSize.y * VALUE_SCALE_IMG;
	kirby_slide_R.SetPivot() = OFFSET_B;
	kirby_slide_R.isVisible = false;

	kirby_crouch_L.LoadFile(L"kirby_crouch_L.png");
	kirby_crouch_L.SetScale().x = kirby_crouch_L.imageSize.x * VALUE_SCALE_IMG;
	kirby_crouch_L.SetScale().y = kirby_crouch_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_crouch_L.SetPivot() = OFFSET_B;
	kirby_crouch_L.isVisible = false;

	kirby_crouch_R.LoadFile(L"kirby_crouch_R.png");
	kirby_crouch_R.SetScale().x = kirby_crouch_R.imageSize.x * VALUE_SCALE_IMG;
	kirby_crouch_R.SetScale().y = kirby_crouch_R.imageSize.y * VALUE_SCALE_IMG;
	kirby_crouch_R.SetPivot() = OFFSET_B;
	kirby_crouch_R.isVisible = false;

	kirby_jump_L.LoadFile(L"kirby_jump_L.png");
	kirby_jump_L.SetScale().x = kirby_jump_L.imageSize.x / 5.0f * VALUE_SCALE_IMG;
	kirby_jump_L.SetScale().y = kirby_jump_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_jump_L.SetPivot() = OFFSET_B;
	kirby_jump_L.maxFrame.x = 5;
	kirby_jump_L.ChangeAnim(ANIMSTATE::REVERSE_ONCE, 1.0f / 12);
	kirby_jump_L.isVisible = false;

	kirby_jump_R.LoadFile(L"kirby_jump_R.png");
	kirby_jump_R.SetScale().x = kirby_jump_R.imageSize.x / 5.0f * VALUE_SCALE_IMG;
	kirby_jump_R.SetScale().y = kirby_jump_R.imageSize.y * VALUE_SCALE_IMG;
	kirby_jump_R.SetPivot() = OFFSET_B;
	kirby_jump_R.maxFrame.x = 5;
	kirby_jump_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
	kirby_jump_R.isVisible = false;

	//kirby_hover_L.LoadFile(L"kirby_jump_R.png");
	//kirby_hover_L.SetScale().x = kirby_hover_L.imageSize.x / 5.0f * VALUE_SCALE_IMG;
	//kirby_hover_L.SetScale().y = kirby_hover_L.imageSize.y * VALUE_SCALE_IMG;
	//kirby_hover_L.SetPivot() = OFFSET_B;
	//kirby_hover_L.maxFrame.x = 5;
	//kirby_hover_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
	//kirby_hover_L.isVisible = false;

	//kirby_hover_R.LoadFile(L"kirby_jump_R.png");
	//kirby_hover_R.SetScale().x = kirby_hover_R.imageSize.x / 5.0f * VALUE_SCALE_IMG;
	//kirby_hover_R.SetScale().y = kirby_hover_R.imageSize.y * VALUE_SCALE_IMG;
	//kirby_hover_R.SetPivot() = OFFSET_B;
	//kirby_hover_R.maxFrame.x = 5;
	//kirby_hover_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
	//kirby_hover_R.isVisible = false;

	//kirby_inhole_L.LoadFile(L"kirby_jump_R.png");
	//kirby_inhole_L.SetScale().x = kirby_inhole_L.imageSize.x / 5.0f * VALUE_SCALE_IMG;
	//kirby_inhole_L.SetScale().y = kirby_inhole_L.imageSize.y * VALUE_SCALE_IMG;
	//kirby_inhole_L.SetPivot() = OFFSET_B;
	//kirby_inhole_L.maxFrame.x = 5;
	//kirby_inhole_L.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
	//kirby_inhole_L.isVisible = false;

	//kirby_inhole_R.LoadFile(L"kirby_jump_R.png");
	//kirby_inhole_R.SetScale().x = kirby_inhole_R.imageSize.x / 5.0f * VALUE_SCALE_IMG;
	//kirby_inhole_R.SetScale().y = kirby_inhole_R.imageSize.y * VALUE_SCALE_IMG;
	//kirby_inhole_R.SetPivot() = OFFSET_B;
	//kirby_inhole_R.maxFrame.x = 5;
	//kirby_inhole_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
	//kirby_inhole_R.isVisible = false;

	kirby_ouch_L.LoadFile(L"riderkirby_attack.png");
	kirby_ouch_L.SetScale().x = kirby_ouch_L.imageSize.x / 4.0f * VALUE_SCALE_IMG;
	kirby_ouch_L.SetScale().y = kirby_ouch_L.imageSize.y * VALUE_SCALE_IMG;
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

void Player::Update()
{
	if (GetWorldPos().y >= 0) { upVector += DELTA * 0.2f; }
	else { SetWorldPosY(0); isJump = false; jumpable = true; }

	if (!isJump) upVector = 0;
	MoveWorldPos(DOWN * 1.0f * upVector);

	if (cmdTime > 0)
		cmdTime -= DELTA;
	if (slideTime > 0)
	{
		MoveWorldPos(RIGHT * 1.0f * fowardVector);
		fowardVector *= 1-DELTA * 2.5f;
		slideTime -= DELTA;
	}
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
		if (btweenCmdTime > 0 && MecanimManager::ComboMatch(&Dash_L))
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
		if (btweenCmdTime > 0 && MecanimManager::ComboMatch(&Dash_R))
		{
			MecanimManager::ComboClear();
			isDash = true;
			cmdTime = 0;
		}
		cmdTime = btweenCmdTime;
	}
	if (INPUT->KeyPress(VK_LEFT) && slideTime <= 0)
	{
		MoveWorldPos(LEFT * DELTA * 300.0f * (isDash / 2.0f + 1));
		isRight = false;
		isMove = true;
	}
	else if (INPUT->KeyPress(VK_RIGHT) && slideTime <= 0)
	{
		MoveWorldPos(RIGHT * DELTA * 300.0f * (isDash / 2.0f + 1));
		isRight = true;
		isMove = true;
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
			slideTime = 0.6f;
			cmdTime = 0;
			if (isRight) fowardVector = 0.04f;
			else fowardVector = -0.04f;
		}
		else if (jumpable && slideTime <= 0){
			isJump = true;
			jumpable = false;
			upVector = -0.08f;
			kirby_jump_R.ChangeAnim(ANIMSTATE::ONCE, 1.0f / 12);
			kirby_jump_L.ChangeAnim(ANIMSTATE::REVERSE_ONCE, 1.0f / 12);
		}
	}
	UpdateSpritePos();
}

void Player::LateUpdate()
{
	UpdateAnimFSM();
	UpdateAnim();
}

void Player::Render()
{
	kirby_none_L.Render();
	kirby_none_R.Render();
	kirby_move_L.Render();
	kirby_move_R.Render();
	kirby_dash_L.Render();
	kirby_dash_R.Render();
	kirby_slide_L.Render();
	kirby_slide_R.Render();
	kirby_crouch_L.Render();
	kirby_crouch_R.Render();
	kirby_jump_L.Render();
	kirby_jump_R.Render();
	kirby_hover_L.Render();
	kirby_hover_R.Render();
	kirby_inhole_L.Render();
	kirby_inhole_R.Render();
	kirby_ouch_L.Render();
	kirby_ouch_R.Render();
}

void Player::UpdateSpritePos()
{
	UpdateMatrix();
	kirby_none_L.SetWorldPos(GetWorldPos());
	kirby_none_R.SetWorldPos(GetWorldPos());
	kirby_move_L.SetWorldPos(GetWorldPos());
	kirby_move_R.SetWorldPos(GetWorldPos());
	kirby_dash_L.SetWorldPos(GetWorldPos());
	kirby_dash_R.SetWorldPos(GetWorldPos());
	kirby_slide_L.SetWorldPos(GetWorldPos());
	kirby_slide_R.SetWorldPos(GetWorldPos());
	kirby_crouch_L.SetWorldPos(GetWorldPos());
	kirby_crouch_R.SetWorldPos(GetWorldPos());
	kirby_jump_L.SetWorldPos(GetWorldPos());
	kirby_jump_R.SetWorldPos(GetWorldPos());
	kirby_hover_L.SetWorldPos(GetWorldPos());
	kirby_hover_R.SetWorldPos(GetWorldPos());
	kirby_inhole_L.SetWorldPos(GetWorldPos());
	kirby_inhole_R.SetWorldPos(GetWorldPos());
	kirby_ouch_L.SetWorldPos(GetWorldPos());
	kirby_ouch_R.SetWorldPos(GetWorldPos());
}

void Player::Active(PlayerState state)
{
	if (state == PlayerState::JUMP)
	{
		jumpable = false;
		upVector = -0.1f;
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
	switch (STATE)
	{
	case PlayerState::NONE:
		if (isRight) ChangeSprite(&kirby_none_R);
		else ChangeSprite(&kirby_none_L);
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
	if (isJump)
	{
		STATE = PlayerState::JUMP;
	}
	else if (isDash)
	{
		STATE = PlayerState::DASH;
	}
	else if (isMove)
	{
		STATE = PlayerState::MOVE;
	}
	else if (slideTime > 0)
	{
		STATE = PlayerState::SLIDE;
	}
	else if (isCrouch)
	{
		STATE = PlayerState::CROUCH;
	}
	else
	{
		STATE = PlayerState::NONE;
	}
}
