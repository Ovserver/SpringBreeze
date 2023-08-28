#pragma once
class Main : public Scene
{
private:
	ObImage meta;
	ObImage sliceMeta[3][3];
	Int2    ºóÄ­;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //ÇØÁ¦
	virtual void Update() override;
	virtual void LateUpdate() override;//°»½Å
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
