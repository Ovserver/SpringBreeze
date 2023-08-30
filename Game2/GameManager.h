#pragma once
#define MAX_COMBO_HISTORY 5
struct Stage 
{
	ObImage*	stageImage;
	ObImage*	stageCollider;
	wstring		stageImgName;
	wstring		stageColName;

	Stage(wstring _stageImgName, wstring _stageColName)
	{
		stageImage = new ObImage();
		stageCollider = new ObImage();
		stageImgName = _stageImgName;
		stageColName = _stageColName;
		stageImage->LoadFile(stageImgName);
		stageCollider->LoadFile(stageColName);

		stageImage->SetScale().x = stageImage->imageSize.x * IMG_SCALE;
		stageImage->SetScale().y = stageImage->imageSize.y * IMG_SCALE;
		stageImage->SetPivot() = OFFSET_LT;

		stageCollider->SetScale().x = stageImage->imageSize.x * IMG_SCALE;
		stageCollider->SetScale().y = stageImage->imageSize.y * IMG_SCALE;
		stageCollider->SetPivot() = OFFSET_LT;
	}
	void SetImagePos(float x, float y)
	{
		stageImage->SetWorldPosX(x);
		stageImage->SetWorldPosY(y);
		stageCollider->SetWorldPosX(x);
		stageCollider->SetWorldPosY(y);
	}
};
struct ComboMap
{
	int comboMaps[MAX_COMBO_HISTORY];
	int comboLength = 0;
};
class GameManager {
public:
	static bool DebugMode;
	static Stage* MainStage;
	static vector<Stage*> StageList;
public:
	static bool IsColorMatch(Color& cl, float r, float g, float b);
	static void AddStage(wstring stageImgName, wstring stageColName);
	static bool ChangeMainStage(wstring stageFname);
	static void Render();
};
class MecanimManager
{
public:
	static int ComboHistory[MAX_COMBO_HISTORY];
public:
	static void ComboInput(int keyCode);
	static void ComboClear();
	static bool ComboMatch(ComboMap* comboMap);
};

