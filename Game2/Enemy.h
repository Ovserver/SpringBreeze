#pragma once

class Stage;

class Player;

enum class ENEMY_SERIAL_NAME
{
	WADDLE_DEE,
	WADDLE_DOO
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
	Color				pointColor;
	Vector2				initPos;
public:
	Enemy(Vector2 _initPos, int _maxHp, ENEMY_SERIAL_NAME _serialName) :
		hp(_maxHp), maxHp(_maxHp), isInhole(false), isStay(false), initPos(_initPos), serialName(_serialName)
	{
		collider = COLLIDER::RECT;
		upVector = 0;
		fowardVector = 1.0f;
		SetPivot() = OFFSET_B;
	}
	// ������ ȣ�� ���� serial name�� ���� �ڵ����� �̹����� �����ϰ� �ʱ�ȭ�մϴ�
	void Init();
	void Update();
	void Render();
	void Damage(int value);
	void UpdateSpritePos();
	void UpdatePointColor(Stage* stage);
	ENEMY_SERIAL_NAME GetSerialName() const { return serialName; }
private:
	float				accel;
	float				upVector;
	float				fowardVector;
	ObImage				enemy_Idle;
	ObImage				enemy_move;
	ObImage				enemy_ouch;
	ENEMY_SERIAL_NAME	serialName;
};