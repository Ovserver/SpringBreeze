#pragma once
class Camera : public GameObject
{
private:
    Matrix              V, P, VP;     
public:
    //ī�޶���ġ
    Viewport            viewport;  
protected:
public:
    Camera();
    void          UpdateMatrix();
    void          ResizeScreen();
    const Matrix& GetVP() { return VP; };
};