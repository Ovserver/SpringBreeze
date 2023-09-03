#include "stdafx.h"
#include "Bullet.h"
#include "Main.h"

Main::Main()
{
	

}

Main::~Main()
{

}

void Main::Init()
{
	meta.LoadFile(L"meta.png");
	meta.SetScale().x = 900.0f;
	meta.SetScale().y = 900.0f;
	meta.SetWorldPosY(450.0f);
	meta.SetPivot() = OFFSET_LT;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sliceMeta[i][j].LoadFile(L"meta.png");
			sliceMeta[i][j].SetScale().x = 300.0f;
			sliceMeta[i][j].SetScale().y = 300.0f;
			sliceMeta[i][j].SetPivot() = OFFSET_LT;
			sliceMeta[i][j].SetWorldPosX(-900.0f + j * 300.0f);
			sliceMeta[i][j].SetWorldPosY(450.0f - i * 300.0f);

			sliceMeta[i][j].uv.x = (0.0f + j) / 3.0f;
			sliceMeta[i][j].uv.y = (0.0f + i) / 3.0f;

			sliceMeta[i][j].uv.z = (1.0f + j) / 3.0f;
			sliceMeta[i][j].uv.w = (1.0f + i) / 3.0f;
		}
	}

	后沫.x = 0;
	后沫.y = 0;

	for(int i=0; i<1000; i++)
	{
		int rand = RANDOM->Int(0, 3);

		if (rand == 0 and 后沫.x > 0)
		{
			Utility::Swap(sliceMeta[后沫.y][后沫.x].uv,
				sliceMeta[后沫.y][后沫.x - 1].uv);

			后沫.x--;
		}
		if (rand == 1 and 后沫.x < 2)
		{
			Utility::Swap(sliceMeta[后沫.y][后沫.x].uv,
				sliceMeta[后沫.y][后沫.x + 1].uv);

			后沫.x++;
		}
		if (rand == 2 and 后沫.y > 0)
		{
			Utility::Swap(sliceMeta[后沫.y][后沫.x].uv,
				sliceMeta[后沫.y - 1][后沫.x].uv);

			后沫.y--;
		}
		if (rand == 3 and 后沫.y < 2)
		{
			Utility::Swap(sliceMeta[后沫.y][后沫.x].uv,
				sliceMeta[后沫.y + 1][后沫.x].uv);

			后沫.y++;
		}
	}

}

void Main::Release()
{
   
}

void Main::Update()
{
	if (INPUT->KeyDown('1'))
	{
		meta.ChangeSampler(D3D11_FILTER_MIN_MAG_MIP_POINT);
	}
	if (INPUT->KeyDown('2'))
	{
		meta.ChangeSampler(D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	}

	if (INPUT->KeyDown(VK_LEFT)and 后沫.x > 0)
	{
		Utility::Swap(sliceMeta[后沫.y][后沫.x].uv,
		sliceMeta[后沫.y][后沫.x - 1].uv);

		后沫.x--;
	}
	if (INPUT->KeyDown(VK_RIGHT) and 后沫.x < 2)
	{
		Utility::Swap(sliceMeta[后沫.y][后沫.x].uv,
			sliceMeta[后沫.y][后沫.x + 1].uv);

		后沫.x++;
	}
	if (INPUT->KeyDown(VK_UP) and 后沫.y > 0)
	{
		Utility::Swap(sliceMeta[后沫.y][后沫.x].uv,
			sliceMeta[后沫.y-1][后沫.x].uv);

		后沫.y--;
	}
	if (INPUT->KeyDown(VK_DOWN) and 后沫.y < 2)
	{
		Utility::Swap(sliceMeta[后沫.y][后沫.x].uv,
			sliceMeta[后沫.y + 1][后沫.x].uv);

		后沫.y++;
	}
	//ImGui::SliderFloat4("Uv", (float*)&bono.uv, 0, 1);

}

void Main::LateUpdate()
{

	
}

void Main::Render()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 后沫.y and j == 后沫.x) continue;

			sliceMeta[i][j].Render();
		}
	}
	meta.Render();
}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    //芒,橇肺弊伐 捞抚
	app.SetAppName(L"Game12");
	//殿废等 牢胶畔胶
    app.SetInstance(instance);
	//芒 农扁
	app.InitWidthHeight(1800.0f,900.0f);
	//硅版祸
    app.background = Color(0.3, 0.3, 0.3);
	WIN->Create();
	Main* main = new Main();
	//Loop
	int wParam = (int)WIN->Run(main);
	//Loop End
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}