#include "stdafx.h"
#include "Enemy.h"
#include "GameManager.h"

int		MecanimManager::ComboHistory[MAX_COMBO_HISTORY] = { 0 };
bool	GameManager::DebugMode = false;
Stage* GameManager::MainStage = nullptr;
vector<Stage*> GameManager::StageList;

void MecanimManager::ComboInput(int keyCode)
{
	for (size_t i = MAX_COMBO_HISTORY - 1; i > 0; i--)
	{
		ComboHistory[i] = ComboHistory[i - 1];
	}
	ComboHistory[0] = keyCode;
}

void MecanimManager::ComboClear()
{
	for (size_t i = 0; i < MAX_COMBO_HISTORY; i++)
	{
		ComboHistory[i] = 0;
	}
}

bool MecanimManager::ComboMatch(ComboMap* comboMap)
{
	for (size_t i = 0; i < comboMap->comboLength; i++)
	{
		if (ComboHistory[i] != comboMap->comboMaps[i])
			return false;
	}
	return true;
}

bool GameManager::IsColorMatch(Color& cl, float r, float g, float b)
{
	if (cl.x == r && cl.y == g && cl.z == b)
		return true;
	else
		return false;
}

void GameManager::AddStage(wstring _stageImgName, wstring _stageColName)
{
	Stage* tmp = new Stage(_stageImgName, _stageColName);
	StageList.push_back(tmp);
}

void GameManager::Render()
{
	MainStage->image->Render();
	MainStage->collider->Render();
}

bool GameManager::ChangeMainStage(wstring _stageImgName)
{
	for (size_t i = 0; i < StageList.size(); i++)
	{
		if (StageList[i]->imageFName == _stageImgName)
		{
			MainStage = StageList[i];
			return true;
		}
	}
	return false;
}
