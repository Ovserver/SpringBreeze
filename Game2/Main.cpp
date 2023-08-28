#include "stdafx.h"
#include "MecanimManager.h"
#include "Text.h"
#include "Player.h"
#include "Main.h"

float maxInvisibleTime = 0.6f;
float invisibleTime = 0;
float maxBoostTime = 3.5f;
float boostTime = 0;
float playerSpeed = 1.0f;
float upVector = 0;
int	fallSafety = 0;
bool jumpable = true;
bool isSlide = false;
bool isGameover = false;
PlayerState STATE = PlayerState::NONE;
Main::Main()
{

}

Main::~Main()
{
}
void Main::Init()
{
	invisibleTime = 0;
	boostTime = 0;
	playerSpeed = 1.0f;
	upVector = 0;
	fallSafety = 0;
	jumpable = true;
	isSlide = false;
	isGameover = false;
	STATE = PlayerState::SLIDE;
	score = 0;
	hp = 100.0f;
	
	mainPlayer.Init();

	bg1.LoadFile(L"bg1.png"); // 992 * 212, 4frame // 1frame 248 * 212
	bg1.SetScale().x = bg1.imageSize.x / 4.0f * VALUE_SCALE_IMG;
	bg1.SetScale().y = bg1.imageSize.y * VALUE_SCALE_IMG;
	//bg1.SetPivot() = OFFSET_B;
	bg1.maxFrame.x = 4;
	bg1.SetWorldPosY(app.GetHalfHeight() * -1 - 50);
	bg1.ChangeAnim(ANIMSTATE::LOOP, 0.1f);

	for (size_t i = 0; i < NUM_PLANE; i++)
	{
		planeImg[i].LoadFile(L"block.png");
		planeImg[i].SetScale().x = planeImg[i].imageSize.x * VALUE_SCALE_IMG;
		planeImg[i].SetScale().y = planeImg[i].imageSize.y * VALUE_SCALE_IMG;
		planeImg[i].SetPivot() = OFFSET_LB;
		planeImg[i].SetWorldPosX(app.GetHalfWidth() * -1 + (planeImg[i].GetScale().x * i));
		planeImg[i].SetWorldPosY(app.GetHalfHeight() * -1);

		plane[i].SetScale().x = planeImg[i].GetScale().x;
		plane[i].SetScale().y = planeImg[i].GetScale().y - 10;
		plane[i].SetPivot() = OFFSET_LB;
		plane[i].SetWorldPosX(app.GetHalfWidth() * -1 + (plane[i].GetScale().x * 0.95f * i));
		plane[i].SetWorldPosY(app.GetHalfHeight() * -1);
		plane[i].collider = COLLIDER::RECT;
	}

	player.SetWorldPosX(app.GetHalfWidth() * -1 + 80.0f);
	player.SetWorldPosY(app.GetHalfHeight() * -1 + 160);
	player.SetPivot() = OFFSET_B;
	player.collider = COLLIDER::RECT;

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

	kirby_drive.LoadFile(L"riderkirby_drive.png");
	kirby_drive.SetScale().x = kirby_drive.imageSize.x / 4.0f * VALUE_SCALE_IMG;
	kirby_drive.SetScale().y = kirby_drive.imageSize.y * VALUE_SCALE_IMG;
	kirby_drive.SetPivot() = OFFSET_B;
	kirby_drive.maxFrame.x = 4;
	kirby_drive.ChangeAnim(ANIMSTATE::LOOP, 1 / 24.0f);
	kirby_drive.isVisible = false;

	kirby_slide.LoadFile(L"riderkirby_slide.png");
	kirby_slide.SetScale().x = kirby_slide.imageSize.x * VALUE_SCALE_IMG;
	kirby_slide.SetScale().y = kirby_slide.imageSize.y * VALUE_SCALE_IMG;
	kirby_slide.SetPivot() = OFFSET_B;
	kirby_slide.isVisible = false;

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

	kirby_ouch.LoadFile(L"riderkirby_attack.png");
	kirby_ouch.SetScale().x = kirby_ouch.imageSize.x / 4.0f * VALUE_SCALE_IMG;
	kirby_ouch.SetScale().y = kirby_ouch.imageSize.y * VALUE_SCALE_IMG;
	kirby_ouch.SetPivot() = OFFSET_B;
	kirby_ouch.maxFrame.x = 4;
	kirby_ouch.ChangeAnim(ANIMSTATE::LOOP, 1 / 24.0f);
	kirby_ouch.isVisible = false;

	drive_effect.LoadFile(L"drive_effect.png");
	drive_effect.SetScale().x = drive_effect.imageSize.x / 4.0f * VALUE_SCALE_IMG;
	drive_effect.SetScale().y = drive_effect.imageSize.y * VALUE_SCALE_IMG;
	drive_effect.SetPivot() = OFFSET_B;
	drive_effect.maxFrame.x = 4;
	drive_effect.ChangeAnim(ANIMSTATE::LOOP, 1 / 24.0f);
	drive_effect.isVisible = true;

	enemy.LoadFile(L"enemy.png"); // 294 * 48, 6 Frame
	enemy.SetScale().x = enemy.imageSize.x / 6.0f * 1.5f;
	enemy.SetScale().y = enemy.imageSize.y * 1.5f;
	enemy.SetPivot() = OFFSET_B;
	enemy.SetWorldPosX(300.0f);
	enemy.SetWorldPosY(-170.0f);
	enemy.maxFrame.x = 6;
	enemy.ChangeAnim(ANIMSTATE::LOOP, 1 / 12.0f);
	enemy.collider = COLLIDER::CIRCLE;

	food = new Item[NUM_FOOD_INSTANCE];
	for (size_t i = 0; i < NUM_FOOD_INSTANCE; i++)
	{
		food[i].image.LoadFile(L"food.png");
		food[i].image.SetScale().x = food[i].image.imageSize.x / (float)Item::FoodFrame * VALUE_SCALE_IMG;
		food[i].image.SetScale().y = food[i].image.imageSize.y * VALUE_SCALE_IMG;
		food[i].image.SetWorldPosX(app.GetHalfWidth() * -1 + (food[i].image.GetScale().x * i) * 1.2f);
		int rand = RANDOM->Int(-1, 1);
		food[i].image.SetWorldPosY(-90.0f + 30 * rand);
		food[i].image.SetPivot() = OFFSET_B;
		food[i].image.collider = COLLIDER::RECT;
		rand = RANDOM->Int(0, Item::FoodFrame - 1 - 3);
		food[i].image.uv.x = 1.0f / Item::FoodFrame * rand;
		food[i].image.uv.z = 1.0f / Item::FoodFrame * (rand + 1);
	}

	ui.LoadFile(L"ui.png");
	ui.SetScale().x = ui.imageSize.x * VALUE_SCALE_IMG;
	ui.SetScale().y = ui.imageSize.y * VALUE_SCALE_IMG;
	ui.SetPivot() = OFFSET_T;
	ui.SetWorldPosY(app.GetHalfHeight());

	hpBar.SetScale().x = 114;
	hpBar.SetScale().y = 24;
	hpBar.SetWorldPosX(app.GetHalfWidth() * -1 + 104);
	hpBar.SetWorldPosY(app.GetHalfHeight() - 45);
	hpBar.SetPivot() = OFFSET_L;
	hpBar.color = Color(1, 0, 0);

	boostBar.SetScale().x = 114;
	boostBar.SetScale().y = 24;
	boostBar.SetWorldPosX(app.GetHalfWidth() * -1 + 400);
	boostBar.SetWorldPosY(app.GetHalfHeight() - 45);
	boostBar.SetPivot() = OFFSET_R;
	boostBar.color = Color(0, 0, 1);

	for (size_t i = 0; i < NUM_SCORETEXT; i++)
	{
		scoreText[i].SetWorldPosX((app.GetHalfWidth() * -1 + 386) - (15 * i));
		scoreText[i].SetWorldPosY(app.GetHalfHeight() - 86);
		scoreText[i].SetScale().x = 1.0;
		scoreText[i].SetScale().y = 1.0;
		scoreText[i].value = i;
		scoreText[i].SetColor(Color(0, 0, 0));
		scoreText[i].Init();
		scoreText[i].scaler = 0.3f;
		scoreText[i].SetScale().x *= 1.2f;
		scoreText[i].SetScale().y *= 1.2f;
	}

	for (size_t i = 0; i < NUM_SAFETYTEXT; i++)
	{
		safetyText[i].SetWorldPosX((app.GetHalfWidth() * -1 + 160) - (15 * i));
		safetyText[i].SetWorldPosY(app.GetHalfHeight() - 86);
		safetyText[i].SetScale().x = 1.0;
		safetyText[i].SetScale().y = 1.0;
		safetyText[i].value = i;
		safetyText[i].SetColor(Color(0, 0, 0));
		safetyText[i].Init();
		safetyText[i].scaler = 0.3f;
		safetyText[i].SetScale().x *= 1.2f;
		safetyText[i].SetScale().y *= 1.2f;
	}
	gameoverUI.LoadFile(L"gameover.png");
	gameoverUI.SetScale().x = gameoverUI.imageSize.x * VALUE_SCALE_IMG;
	gameoverUI.SetScale().y = gameoverUI.imageSize.y * VALUE_SCALE_IMG;

}

void Main::Release()
{

}
float	comboCount = 0;
float	slideTime = 0;
bool	isRight = true;
bool	isMove = false;
void Main::Update()
{
	mainPlayer.Update();
	mainPlayer.SpritePosUpdate();
	//reset
	if (INPUT->KeyDown('R'))
	{
		delete[] food;
		this->Init();
	}
	if (INPUT->KeyDown('D'))
	{
		isGameover = true;
	}
	if (isGameover)
		return;
	if (INPUT->KeyDown('B'))
	{
		boostTime = maxBoostTime;
	}
	//switching player sprite
	switch (STATE)
	{
	case PlayerState::NONE:
		if (isRight)
		{
			player.SetScale().x = kirby_none_R.GetScale().x;
			player.SetScale().y = kirby_none_R.GetScale().y;
			kirby_none_L.isVisible = false;
			kirby_none_R.isVisible = true;
		}
		else
		{
			player.SetScale().x = kirby_move_L.GetScale().x;
			player.SetScale().y = kirby_move_L.GetScale().y;
			kirby_none_L.isVisible = true;
			kirby_none_R.isVisible = false;
		}
		kirby_move_L.isVisible = false;
		kirby_move_R.isVisible = false;
		kirby_drive.isVisible = false;
		kirby_slide.isVisible = false;
		kirby_ouch.isVisible = false;
		break;
	case PlayerState::MOVE:
		if (isRight)
		{
			player.SetScale().x = kirby_move_R.GetScale().x;
			player.SetScale().y = kirby_move_R.GetScale().y;
			kirby_move_L.isVisible = false;
			kirby_move_R.isVisible = true;
		}
		else
		{
			player.SetScale().x = kirby_move_L.GetScale().x;
			player.SetScale().y = kirby_move_L.GetScale().y;
			kirby_move_L.isVisible = true;
			kirby_move_R.isVisible = false;
		}
		kirby_none_L.isVisible = false;
		kirby_none_R.isVisible = false;
		kirby_drive.isVisible = false;
		kirby_slide.isVisible = false;
		kirby_ouch.isVisible = false;
		break;
	case PlayerState::DASH:
		player.SetScale().x = kirby_drive.GetScale().x;
		player.SetScale().y = kirby_drive.GetScale().y;
		kirby_move_R.isVisible = false;
		kirby_drive.isVisible = true;
		kirby_slide.isVisible = false;
		kirby_ouch.isVisible = false;
		break;
	case PlayerState::SLIDE:
		player.SetScale().x = kirby_slide.GetScale().x;
		player.SetScale().y = kirby_slide.GetScale().y;
		kirby_move_R.isVisible = false;
		kirby_drive.isVisible = false;
		kirby_slide.isVisible = true;
		kirby_ouch.isVisible = false;
		break;
	case PlayerState::JUMP:
		if (isRight)
		{
			player.SetScale().x = kirby_jump_R.GetScale().x;
			player.SetScale().y = kirby_jump_R.GetScale().y;
			kirby_jump_R.isVisible = true;
			kirby_jump_L.isVisible = false;
		}
		else
		{
			player.SetScale().x = kirby_jump_L.GetScale().x;
			player.SetScale().y = kirby_jump_L.GetScale().y;
			kirby_jump_L.isVisible = true;
			kirby_jump_R.isVisible = false;
		}
		kirby_none_L.isVisible = false;
		kirby_none_R.isVisible = false;
		kirby_move_L.isVisible = false;
		kirby_move_R.isVisible = false;
		kirby_drive.isVisible = false;
		kirby_slide.isVisible = false;
		kirby_ouch.isVisible = false;
		break;
	case PlayerState::OUCH:
		player.SetScale().x = kirby_ouch.GetScale().x;
		player.SetScale().y = kirby_ouch.GetScale().y;
		kirby_move_R.isVisible = false;
		kirby_drive.isVisible = false;
		kirby_slide.isVisible = false;
		kirby_ouch.isVisible = true;
		break;
	case PlayerState::OVER:
		player.SetScale().x = kirby_move_R.GetScale().x;
		player.SetScale().y = kirby_move_R.GetScale().y;
		break;
	default:
		break;
	}
	//state control
	{
		if (boostTime > 0)
		{
			playerSpeed = 3.0f;
			boostTime -= DELTA;
			STATE = PlayerState::DASH;
		}
		else
		{
			playerSpeed = 1.0f;
			STATE = PlayerState::NONE;
		}
		if (isMove)
		{
			STATE = PlayerState::MOVE;
		}
		else
		{
			STATE = PlayerState::NONE;
		}
		if (invisibleTime > 0)
		{
			invisibleTime -= DELTA;

			STATE = PlayerState::OUCH;
		}
		if (slideTime > 0)
		{
			STATE = PlayerState::SLIDE;
		}		
	}
	//hp control
	{
		if (hp > 0)	hp -= DELTA * 2.0f;
		else { isGameover = true;	return; }
	}

	if (upVector == 0 && boostTime > 0) drive_effect.isVisible = true; else drive_effect.isVisible = false;
	//enemy event & movement
	{
		enemy.MoveWorldPos(LEFT * DELTA * playerSpeed * 300.0f);
		if (enemy.Intersect(&player) && invisibleTime <= 0 && boostTime <= 0)
		{
			invisibleTime = maxInvisibleTime;
			hp -= 5;
		}
		if (enemy.GetWorldPos().x < -(400 + enemy.imageSize.x))
		{
			enemy.SetWorldPosX(400);
			enemy.SetWorldPosY(-170.0f + RANDOM->Int(0, 2) * 90);
		}
	}
	//plane movement
	for (size_t i = 0; i < NUM_PLANE; i++)
	{
		//plane[i].MoveWorldPos(LEFT * DELTA * playerSpeed * 300.0f);
		//if (plane[i].GetWorldPos().x < app.GetHalfWidth() * -1 - plane[i].GetScale().x)
		//	plane[i].SetWorldPosX(app.GetHalfWidth() * -1 + plane[i].GetScale().x * NUM_PLANE);
	}
	//food control & movement
	for (size_t i = 0; i < NUM_FOOD_INSTANCE; i++)
	{
		if (food[i].image.Intersect(&player) && food[i].active)
		{
			switch (food[i].type)
			{
			case FoodType::NONE:
				break;
			case FoodType::HP:
				hp += 10;
				if (hp > maxHp)
					hp = maxHp;
				break;
			case FoodType::SAFETYUP:
				++fallSafety;
				break;
			case FoodType::DRIVE:
				boostTime = maxBoostTime;
				break;
			default:
				break;
			}
			++score;
			food[i].active = false;
		}
		food[i].image.MoveWorldPos(LEFT * DELTA * playerSpeed * 300.0f);
		if (food[i].image.GetWorldPos().x < app.GetHalfWidth() * -1 - food[i].image.imageSize.x)
		{
			int rand = RANDOM->Int(0, 99);
			if (rand == 77) // candy
			{
				food[i].image.uv.x = 1.0f / Item::FoodFrame * 15;
				food[i].image.uv.z = 1.0f / Item::FoodFrame * (15 + 1);
				food[i].type = FoodType::DRIVE;
			}
			else if (rand == 11) // 1up
			{
				food[i].image.uv.x = 1.0f / Item::FoodFrame * 16;
				food[i].image.uv.z = 1.0f / Item::FoodFrame * (16 + 1);
				food[i].type = FoodType::SAFETYUP;
			}
			else if (rand % 10 == 0) // mxtomato
			{
				food[i].image.uv.x = 1.0f / Item::FoodFrame * 14;
				food[i].image.uv.z = 1.0f / Item::FoodFrame * (14 + 1);
				food[i].type = FoodType::HP;
			}
			else // food
			{
				rand = RANDOM->Int(0, Item::FoodFrame - 1 - 3);
				food[i].image.uv.x = 1.0f / Item::FoodFrame * rand;
				food[i].image.uv.z = 1.0f / Item::FoodFrame * (rand + 1);
				food[i].type = FoodType::NONE;
			}
			food[i].active = true;
			//food[i].image.SetWorldPosX(400);
			food[i].image.SetWorldPosX(app.GetHalfWidth() * -1 + (food[i].image.GetScale().x * 13) * 1.2f);

			rand = RANDOM->Int(-1, 1);
			food[i].image.SetWorldPosY(-90.0f + 30 * rand);
		}
	}
	//score text value mapping
	{
		int tempS;
		tempS = score;
		for (size_t i = 0; i < NUM_SCORETEXT; i++)
		{
			scoreText[i].value = tempS % 10;
			tempS = tempS / 10;
			scoreText[i].Update();
		}
	}
	//safety text value mapping
	{
		int tempS;
		tempS = fallSafety;
		for (size_t i = 0; i < NUM_SAFETYTEXT; i++)
		{
			safetyText[i].value = tempS % 10;
			tempS = tempS / 10;
			safetyText[i].Update();
		}
	}
	app.maincam->SetWorldPosX(player.GetWorldPos().x);
	app.maincam->SetWorldPosY(player.GetWorldPos().y);
	bg1.SetWorldPosX(player.GetWorldPos().x);
	bg1.SetWorldPosY(player.GetWorldPos().y);
}

void Main::LateUpdate()
{
	if (isGameover)
		return;
	//sprite position update
	{
		kirby_none_L.SetWorldPosX(player.GetWorldPos().x);
		kirby_none_L.SetWorldPosY(player.GetWorldPos().y);

		kirby_none_R.SetWorldPosX(player.GetWorldPos().x);
		kirby_none_R.SetWorldPosY(player.GetWorldPos().y);

		kirby_move_L.SetWorldPosX(player.GetWorldPos().x);
		kirby_move_L.SetWorldPosY(player.GetWorldPos().y);

		kirby_move_R.SetWorldPosX(player.GetWorldPos().x);
		kirby_move_R.SetWorldPosY(player.GetWorldPos().y);

		kirby_drive.SetWorldPosX(player.GetWorldPos().x);
		kirby_drive.SetWorldPosY(player.GetWorldPos().y - 2);

		kirby_slide.SetWorldPosX(player.GetWorldPos().x);
		kirby_slide.SetWorldPosY(player.GetWorldPos().y);

		kirby_jump_L.SetWorldPosX(player.GetWorldPos().x);
		kirby_jump_L.SetWorldPosY(player.GetWorldPos().y);

		kirby_ouch.SetWorldPosX(player.GetWorldPos().x);
		kirby_ouch.SetWorldPosY(player.GetWorldPos().y);

		drive_effect.SetWorldPosX(player.GetWorldPos().x - 50);
		drive_effect.SetWorldPosY(player.GetWorldPos().y);
		for (size_t i = 0; i < NUM_PLANE; i++)
		{
			planeImg[i].SetWorldPosX(plane[i].GetWorldPos().x);
			planeImg[i].SetWorldPosY(plane[i].GetWorldPos().y);
		}
	}
	hpBar.SetScale().x = 114 * hp / maxHp;
	boostBar.SetScale().x = 114 * boostTime / maxBoostTime;
}

void Main::Render()
{
	bg1.Render();
	for (size_t i = 0; i < NUM_FOOD_INSTANCE; i++)
	{
		if (food[i].active)
			food[i].image.Render();
	}
	for (size_t i = 0; i < NUM_PLANE; i++)
	{
		if (i < 46)
		{
			plane[i].Render();
			planeImg[i].Render();
		}
	}
	enemy.Render();
	player.Render();
	mainPlayer.Render();
	kirby_none_L.Render();
	kirby_none_R.Render();
	kirby_move_L.Render();
	kirby_move_R.Render();
	kirby_drive.Render();
	kirby_slide.Render();
	kirby_jump_L.Render();
	kirby_jump_R.Render();
	kirby_ouch.Render();
	drive_effect.Render();
	hpBar.Render();
	boostBar.Render();
	ui.Render();
	for (size_t i = 0; i < NUM_SCORETEXT; i++)
	{
		scoreText[i].Render();
	}
	for (size_t i = 0; i < NUM_SAFETYTEXT; i++)
	{
		safetyText[i].Render();
	}
	if (isGameover)
		gameoverUI.Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(496.0f, 530.0f); // 248, 265
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}