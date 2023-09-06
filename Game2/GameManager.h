#pragma once
#define MAX_COMBO_HISTORY 5

#define AIR_AREA GameManager::IsColorMatch(pointColor, 255, 0, 255)					//Non-Render Color
#define WALL_AREA_LEFT GameManager::IsColorMatch(pointColor, 0, 255, 0)				//Green
#define WALL_AREA_RIGHT GameManager::IsColorMatch(pointColor, 0, 0, 255)			//Blue
#define LANDING_AREA GameManager::IsColorMatch(pointColor, 255, 0, 0)				//Red
#define INTERPOL_AREA_RISE GameManager::IsColorMatch(pointColor, 0, 0, 0)			//Black
#define INTERPOL_AREA_DESC_SLOPE GameManager::IsColorMatch(pointColor, 0, 255, 255)	//Sky
#define INTERPOL_AREA_DESC GameManager::IsColorMatch(pointColor, 128, 255, 255)		//Bright Sky
#define INTERPOL_AREA_PULL_LEFT GameManager::IsColorMatch(pointColor, 128, 255, 0)	//Grass
#define INTERPOL_AREA_PULL_RIGHT GameManager::IsColorMatch(pointColor, 128, 0, 255)	//Purple

#define UPDATE_COLOR pointColor = GameManager::GetPointColor(this);

#define MAINSTAGE GameManager::MainStage
#define MAINPLAYER GameManager::MainPlayer

class Enemy;
class Player;
enum class COLLISION_CHECK_TYPE
{
	INHOLE,
	ATTACK_BULLET_ONCE,
	ATTACK_BULLET_ASSAULT,
	ATTACK_AREA
};
enum class BG_TYPE
{
	ONCE, REPEAT
};
enum class CAM_LOCKIN_TYPE
{
	SINGLE, CONTINUOS
};
class Portal {
public:
	ObImage	effect1;
	ObImage	effect2;
	//포탈의 실제 인식범위
	ObRect	rect;
	//이동할 스테이지의 파일 이름
	wstring	destStageFname;
	//stage내 여러개의 포탈이 있을 경우 특정 포탈 지정 (기본값 0)
	UINT	initPosNum = 0;
	Portal(Vector2 pos) {
		rect.SetWorldPos(pos);
		rect.SetPivot() = OFFSET_B;
		rect.SetScale().x = 24 * IMG_SCALE;
		rect.SetScale().y = 30 * IMG_SCALE;
		rect.collider = COLLIDER::RECT;
		rect.isFilled = false;

		effect1.SetWorldPos(pos + UP * 20 * IMG_SCALE);
		effect1.LoadFile(L"object_starbullet.png");
		effect1.SetScale().x = effect1.imageSize.x / 4.0f * IMG_SCALE;
		effect1.SetScale().y = effect1.imageSize.y * IMG_SCALE;
		effect1.maxFrame.x = 4;
		effect1.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
		effect1.SetPivot() = OFFSET_B;

		effect2.SetWorldPos(pos);
		effect2.LoadFile(L"effect_portal_sub.png");
		effect2.SetScale().x = effect2.imageSize.x / 6.0f * IMG_SCALE;
		effect2.SetScale().y = effect2.imageSize.y * IMG_SCALE;
		effect2.maxFrame.x = 6;
		effect2.ChangeAnim(ANIMSTATE::LOOP, 1.0f / 12);
		effect2.SetPivot() = OFFSET_B;
	}
	void Render() { effect1.Render(); effect2.Render(); rect.Render(); }
};
class Stage
{
public:
	bool				mCamLock;
	Vector2				mCamLockPos;
	Vector2				mCamLockRangePosMin;
	Vector2				mCamLockRangePosMax;
	GameObject* mCamLockEventObject;
	CAM_LOCKIN_TYPE		mCamLockEventType;
	Vector2				mLimitCameraPosX;
	Vector2				mLimitCameraPosY;
	vector<Vector2>		mPlayerInitPos;
	vector<ObImage*>	mBGImage;
	vector<Vector2>		mBGImagePos;
	vector<ObImage*>	mImage;
	vector<Vector2>		mImagePos;
	ObImage* mCollider;
	wstring				mImageFName;
	wstring				mColFName;
	vector<Enemy*>		mEnemyList;
	vector<Portal>		mPortalList;
	BG_TYPE				mBGType;
public:
	Stage(wstring _stageImgName, wstring _stageColName, wstring _stageBGImgName);
	void Init();
	void Update();
	//player 좌표에 따라 main camera 위치와 배경을 조정합니다
	void LateUpdate();
	void Render();
	void SetImagePos(Vector2 pos);
	void SetBGImagePos(Vector2 pos);
	void AddImage(wstring _stageImgName, Vector2 imagePos);
	void AddBGImage(wstring _stageImgName, Vector2 imagePos, int frame = 1, bool isVertical = false);
	void AddEnemy(Enemy* enemy);
	void AddPortal(Vector2 pos, wstring _destStageName, int _initPosNum = 0);
	bool PortalCollisionCheck(GameObject* col);
	void EnemyCollisionCheck(GameObject* col, COLLISION_CHECK_TYPE checkType = COLLISION_CHECK_TYPE::INHOLE, int damage = 0);
	bool EnemyInholingCheck();
};

struct ComboMap
{
	int comboMaps[MAX_COMBO_HISTORY];
	int comboLength = 0;
};

class GameManager {
public:
	static int	Score;
	static bool DebugMode;
	static Stage* MainStage;
	static Player* MainPlayer;
	static vector<Stage*> StageList;
public:
	static bool IsColorMatch(Color& cl, float r, float g, float b, float a = 255);
	static bool ChangeMainStage(wstring _stageImgName, int posListNum = 0);
	static Color GetPointColor(GameObject* gameObject);
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

class UIManager {
public:
	static ObImage* UI_standard;
	static ObImage* UI_enemy;
	static ObRect* player_HpBar;
	static ObRect* enemy_HpBar;
	static ObRect* backfaceUI;
public:
	static void Init();
	static void Update();
	static void Render(Camera* camUI);
};