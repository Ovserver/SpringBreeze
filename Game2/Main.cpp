#include "stdafx.h"
#include "GameManager.h"
#include "Text.h"
#include "Player.h"
#include "Main.h"

Main::Main()
{

}

Main::~Main()
{
}
void Main::Init()
{
	mainPlayer.Init();
	camUI.UpdateMatrix();

	UI_normal.LoadFile(L"UI_normal.png");
	bg1.LoadFile(L"bg_stage_1-1.png");
	bg1_sub.LoadFile(L"bg_sub_stage_1-1.png");
	stage_1_1.LoadFile(L"stage_1-1.png");

	UI_normal.SetScale().x = UI_normal.imageSize.x * IMG_SCALE;
	UI_normal.SetScale().y = UI_normal.imageSize.y * IMG_SCALE;
	UI_normal.SetPivot() = OFFSET_B;
	UI_normal.SetWorldPosY(app.GetHalfHeight() * -1);

	bg1.SetScale().x = bg1.imageSize.x * IMG_SCALE;
	bg1.SetScale().y = bg1.imageSize.y * IMG_SCALE;

	bg1_sub.SetScale().x = bg1_sub.imageSize.x * IMG_SCALE;
	bg1_sub.SetScale().y = bg1_sub.imageSize.y / 4 * IMG_SCALE;
	bg1_sub.SetLocalPosX(-96 * IMG_SCALE);
	bg1_sub.SetLocalPosY(-8 * IMG_SCALE);
	bg1_sub.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6, false);
	bg1_sub.maxFrame.y = 4;
	bg1_sub.SetParentT(bg1);

	stage_1_1.SetScale().x = stage_1_1.imageSize.x * IMG_SCALE;
	stage_1_1.SetScale().y = stage_1_1.imageSize.y * IMG_SCALE;

	for (size_t i = 0; i < STAGE_1_1_GROUND; i++)
	{
		stage_1_1_coll_ground[i].collider = COLLIDER::RECT;
		stage_1_1_coll_ground[i].isFilled = false;
	}
	for (size_t i = 0; i < STAGE_1_1_WALL_L; i++)
	{
		stage_1_1_coll_wall_L[i].collider = COLLIDER::RECT;
		stage_1_1_coll_wall_L[i].isFilled = false;
	}
	for (size_t i = 0; i < STAGE_1_1_WALL_R; i++)
	{
		stage_1_1_coll_wall_R[i].collider = COLLIDER::RECT;
		stage_1_1_coll_wall_R[i].isFilled = false;
	}
	for (size_t i = 0; i < STAGE_1_1_SLOPE; i++)
	{
		stage_1_1_coll_slope[i].collider = COLLIDER::RECT;
		stage_1_1_coll_slope[i].isFilled = false;
	}
}

void Main::Release()
{

}
float iv;
void Main::Update()
{
	mainPlayer.Update();
	if (INPUT->KeyDown('R'))
	{
		this->Init();
	}

}

void Main::LateUpdate()
{
	mainPlayer.LateUpdate();
}

void Main::Render()
{
	bg1.Render();
	bg1_sub.Render();
	stage_1_1.Render();
	mainPlayer.Render();
	UI_normal.Render(&camUI);
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(512.0f, 480.0f); // 248, 265
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}