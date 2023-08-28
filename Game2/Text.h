#pragma once
#define TEXTRECT_LEN 7
class Text : public ObRect
{
	ObRect	textRect[TEXTRECT_LEN];
	Color	tColor = Color(1, 1, 0);
public:
	int		value;
	float	scaler;
	void Init();
	void Render(class Camera* cam = app.maincam) override;
	void Update();
	void SetColor(Color color);
};