#include "stdafx.h"
#include "MecanimManager.h"
#include "Player.h"

void Player::Init()
{
	isRight = true;
	isJump = false;
	isMove = false;
	jumpable = false;
	comboCount = 0;
	slideTime = 0;
	upVector = 0;
	STATE = PlayerState::NONE;
	hp = 100;

	mSprites = new ObImage*[12];

	mSprites[0] = &kirby_none_L;
	mSprites[1] = &kirby_none_R;
	mSprites[2] = &kirby_move_L;
	mSprites[3] = &kirby_move_R;
	mSprites[4] = &kirby_dash_L;
	mSprites[5] = &kirby_dash_R;
	mSprites[6] = &kirby_slide_L;
	mSprites[7] = &kirby_slide_R;
	mSprites[8] = &kirby_jump_L;
	mSprites[9] = &kirby_jump_R;
	mSprites[10] = &kirby_ouch_L;
	mSprites[11] = &kirby_ouch_R;

	kirby_none_L.LoadFile(L"kirby_none_L.png");
	kirby_none_L.SetScale().x = kirby_none_L.imageSize.x / 3.0f * VALUE_SCALE_IMG;
	kirby_none_L.SetScale().y = kirby_none_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_none_L.SetPivot() = OFFSET_B;
	kirby_none_L.maxFrame.x = 3;
	kirby_none_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 3);
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
	kirby_move_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
	kirby_move_L.isVisible = false;

	kirby_move_R.LoadFile(L"kirby_move_R.png");
	kirby_move_R.SetScale().x = kirby_move_R.imageSize.x / 6.0f * VALUE_SCALE_IMG;
	kirby_move_R.SetScale().y = kirby_move_R.imageSize.y * VALUE_SCALE_IMG;
	kirby_move_R.SetPivot() = OFFSET_B;
	kirby_move_R.maxFrame.x = 6;
	kirby_move_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
	kirby_move_R.isVisible = false;

	kirby_slide_L.LoadFile(L"riderkirby_slide.png");
	kirby_slide_L.SetScale().x = kirby_slide_L.imageSize.x * VALUE_SCALE_IMG;
	kirby_slide_L.SetScale().y = kirby_slide_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_slide_L.SetPivot() = OFFSET_B;
	kirby_slide_L.isVisible = false;

	kirby_jump_L.LoadFile(L"kirby_jump_R.png");
	kirby_jump_L.SetScale().x = kirby_jump_L.imageSize.x / 5.0f * VALUE_SCALE_IMG;
	kirby_jump_L.SetScale().y = kirby_jump_L.imageSize.y * VALUE_SCALE_IMG;
	kirby_jump_L.SetPivot() = OFFSET_B;
	kirby_jump_L.maxFrame.x = 5;
	kirby_jump_L.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
	kirby_jump_L.isVisible = false;

	kirby_jump_R.LoadFile(L"kirby_jump_R.png");
	kirby_jump_R.SetScale().x = kirby_jump_R.imageSize.x / 5.0f * VALUE_SCALE_IMG;
	kirby_jump_R.SetScale().y = kirby_jump_R.imageSize.y * VALUE_SCALE_IMG;
	kirby_jump_R.SetPivot() = OFFSET_B;
	kirby_jump_R.maxFrame.x = 5;
	kirby_jump_R.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
	kirby_jump_R.isVisible = false;

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

	Slide_L.comboMaps[0] = 'A';
	Slide_L.comboMaps[1] = VK_DOWN;
	Slide_L.comboLength = 2;
	Slide_R.comboMaps[0] = 'A';
	Slide_R.comboMaps[1] = VK_DOWN;
	Slide_R.comboLength = 2;
}

void Player::Update()
{
	upVector += DELTA * 0.2f;
	if (!isJump) upVector = 0;
	MoveWorldPos(DOWN * 2.0f * upVector);

	if (comboCount > 0)
		comboCount -= DELTA;
	if (slideTime > 0)
		slideTime -= DELTA;
	if (INPUT->KeyPress(VK_UP))
	{
		MoveWorldPos(UP * DELTA * 100.0f);
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		//player.MoveWorldPos(DOWN * DELTA * 100.0f);
	}
	if (INPUT->KeyPress(VK_LEFT))
	{
		MoveWorldPos(LEFT * DELTA * 300.0f);
		isRight = false;
		isMove = true;
	}
	else if (INPUT->KeyPress(VK_RIGHT))
	{
		MoveWorldPos(RIGHT * DELTA * 300.0f);
		isRight = true;
		isMove = true;
	}
	else {
		isMove = false;
	}
	if (INPUT->KeyDown('A'))
	{
		MecanimManager::ComboInput('A');
		if (comboCount > 0 && MecanimManager::ComboMatch(&Slide_L))
		{
			slideTime = 0.6f;
			MecanimManager::ComboClear();
			comboCount = 0;
		}
	}
	if (INPUT->KeyDown(VK_DOWN))
	{
		MecanimManager::ComboInput(VK_DOWN);
		comboCount = 0.2f;
	}
	if (INPUT->KeyDown(VK_LEFT))
	{
		MecanimManager::ComboInput(VK_LEFT);
		if (comboCount > 0 && MecanimManager::ComboMatch(&Dash_L))
		{
			MecanimManager::ComboClear();
			comboCount = 0;
		}
		comboCount = 0.2f;
	}
	if (INPUT->KeyDown(VK_RIGHT))
	{
		MecanimManager::ComboInput(VK_RIGHT);
		if (comboCount > 0 && MecanimManager::ComboMatch(&Dash_R))
		{
			MecanimManager::ComboClear();
			comboCount = 0;
		}
		comboCount = 0.2f;
	}
	if (INPUT->KeyDown(VK_SPACE))
	{
		isJump = true;
		upVector = -0.2f;
	}
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
	kirby_jump_L.Render();
	kirby_jump_R.Render();
	kirby_ouch_L.Render();
	kirby_ouch_R.Render();
}

void Player::SpritePosUpdate()
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
	kirby_jump_L.SetWorldPos(GetWorldPos());
	kirby_jump_R.SetWorldPos(GetWorldPos());
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

void Player::UpdateMove()
{
}
