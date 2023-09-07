#pragma once

class Stage;

class Player;

enum class ENEMY_SERIAL_NAME
{
	WADDLE_DEE,
	WADDLE_DOO,
	BRONTO_BURT,
	GRIZZO,
	TWIZZY,
	WHISPY_WOOD,
	WHISPY_APPLE
};

class Enemy : public ObImage
{
public:
	int					hp;
	int					maxHp;
	bool				isInhole;
	bool				isDamage;
	bool				isStay;
	bool				isRight;
	bool				isMove;
	bool				isStasisType;
	float				invisibleTime;
	float				invisibleTimeInterval;
	float				deathAnimTime;
	Color				pointColor;
	Vector2				initPos;
public:
	Enemy() { hp = 10; maxHp = 10; isInhole = false; isDamage = false; isStay = false; isRight = false; isMove = false; }
	Enemy(Vector2 _initPos, int _maxHp, ENEMY_SERIAL_NAME _serialName) :
		hp(_maxHp), maxHp(_maxHp), isInhole(false), isStay(false), initPos(_initPos), serialName(_serialName)
	{
		if (serialName == ENEMY_SERIAL_NAME::WHISPY_APPLE)
			isVisible = false;
		collider = COLLIDER::RECT;
		upVector = 0;
		fowardVector = 1.0f;
		SetPivot() = OFFSET_B;
	}
	// 생성자 호출 시의 serial name에 따라 자동으로 이미지를 선택하고 초기화합니다
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Damage(int value);
	virtual void UpdateSpritePos();
	ENEMY_SERIAL_NAME GetSerialName() const { return serialName; }
protected:
	float				accel;
	float				upVector;
	float				fowardVector;
	float				attackUpVector;
	float				attackFowardVector;
	ObImage				enemy_Idle;
	ObImage				enemy_attack;
	ObImage				enemy_move;
	ObImage				enemy_ouch;
	ObImage				enemy_over;
	ENEMY_SERIAL_NAME	serialName;
};