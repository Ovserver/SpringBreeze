#include "stdafx.h"
#include "Enemy.h"
#include "GameManager.h"
#include "Text.h"
#include "Player.h"
#include "Main.h"

wstring WSstage_1_1_col = L"stage_1-1_collider.png";
Main::Main()
{

}

Main::~Main()
{
}
void Main::Init()
{
	camUI.UpdateMatrix();

	GameManager::StageList.push_back(new Stage(L"stage_1-1.png", L"stage_1-1_collider.png", L"bg_stage_1-1.png"));
	GameManager::ChangeMainStage(L"stage_1-1.png");
	MAINSTAGE->AddBGImage(L"bg_sub_stage_1-1.png", Vector2(-96, -8) * IMG_SCALE, 4, true);
	MAINSTAGE->mBGImage[1]->ChangeAnim(ANIMSTATE::LOOP, 1.0f / 6, false);
	MAINSTAGE->SetImagePos(-100, 100);
	MAINSTAGE->AddEnemy(new Enemy(Vector2(150, -150), 10, L"waddleDoo_ouch.png"));
	MAINSTAGE->AddEnemy(new Enemy(Vector2(280, -130), 10, L"waddleDoo_ouch.png"));

	MAINPLAYER = &mainPlayer;

	UI_normal.LoadFile(L"UI_normal.png");
	UI_normal.SetScale().x = UI_normal.imageSize.x * IMG_SCALE;
	UI_normal.SetScale().y = UI_normal.imageSize.y * IMG_SCALE;
	UI_normal.SetPivot() = OFFSET_B;
	UI_normal.SetWorldPosY(app.GetHalfHeight() * -1);

	MAINSTAGE->Init();
	MAINPLAYER->Init();
}

void Main::Release()
{

}
int posX = 0;
int posY = 0;
void Main::Update()
{
	ImGui::SliderInt("POS_X", &posX, 0, 808);
	ImGui::SliderInt("POS_Y", &posY, 0, 192);

	if (ImGui::Button("Debug Mode"))
	{
		GameManager::DebugMode = !GameManager::DebugMode;
	}
	if (GameManager::DebugMode)
		cout << "pPos : " << MAINPLAYER->GetWorldPos().x << "   " << MAINPLAYER->GetWorldPos().y << endl;
	//cout << "TextureDataR" <<(unsigned int)*(TEXTURE->GetTextureData(L"stage_1-1_collider_test.png").GetPixels() + posX * 4 + posY * 808 * 4 + 2) << endl;
	//cout << "TextureDataG" <<(unsigned int)*(TEXTURE->GetTextureData(L"stage_1-1_collider_test.png").GetPixels() + posX * 4 + posY * 808 * 4 + 1) << endl;
	//cout << "TextureDataB" <<(unsigned int)*(TEXTURE->GetTextureData(L"stage_1-1_collider_test.png").GetPixels() + posX * 4 + posY * 808 * 4) << endl;

	MAINPLAYER->Update();
	MAINSTAGE->Update();
	if (INPUT->KeyDown('R'))
	{
		this->Init();
	}
	app.maincam->SetWorldPos(MAINPLAYER->GetWorldPos());
}

void Main::LateUpdate()
{
	app.maincam->SetWorldPosY(-140);
	if (app.maincam->GetWorldPos().x < 80 * IMG_SCALE)
		app.maincam->SetWorldPosX(80 * IMG_SCALE);
	if (app.maincam->GetWorldPos().x > 700 * IMG_SCALE)
		app.maincam->SetWorldPosX(700 * IMG_SCALE);

	MAINSTAGE->SetBGImagePos(app.maincam->GetWorldPos().x, app.maincam->GetWorldPos().y);
	MAINPLAYER->LateUpdate();
}

void Main::Render()
{
	MAINSTAGE->Render();
	MAINPLAYER->Render();
	UI_normal.Render(&camUI);
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(512.0f, 450.0f); // 248, 265
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}