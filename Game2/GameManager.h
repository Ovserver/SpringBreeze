#pragma once
#define MAX_COMBO_HISTORY 5
#define MAINSTAGE GameManager::MainStage
#define MAINPLAYER GameManager::MainPlayer

class Enemy;
class Player;
struct Portal {
	ObRect	rect;
	wstring	destStageFname;
	UINT	initPosNum;
};
class Stage
{
public:
	vector<Vector2>		mPlayerInitPos;
	vector<ObImage*>	mBGImage;
	vector<Vector2>		mBGImagePos;
	vector<ObImage*>	mImage;
	vector<Vector2>		mImagePos;
	ObImage*			mCollider;
	wstring				mImageFName;
	wstring				mColFName;
	vector<Enemy*>		mEnemyList;
	vector<Portal>		mPortalList;
	
public:
	Stage(wstring _stageImgName, wstring _stageColName, wstring _stageBGImgName);
	void Init();
	void Update();
	void Render();
	void SetImagePos(float x, float y);
	void SetBGImagePos(float x, float y);
	void AddImage(wstring _stageImgName, Vector2 imagePos);
	void AddBGImage(wstring _stageImgName, Vector2 imagePos, int frame = 1, bool isVertical = false);
	void AddEnemy(Enemy* enemy);
	void AddPortal(ObRect* _rect, wstring _destStageName, int _initPosNum = 0);
	bool PortalCollisionCheck(GameObject* col);
	void EnemyCollisionCheck(GameObject* col);
	bool EnemyInholingCheck();
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
	static Player* MainPlayer;
	static vector<Stage*> StageList;
public:
	static bool IsColorMatch(Color& cl, float r, float g, float b);
	static bool ChangeMainStage(wstring _stageImgName, int posListNum = 0);
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

