#include "framework.h"

Camera::Camera()
{
    //ù ī�޶� ��ġ
    SetWorldPosX(0.0f);
    SetWorldPosY(0.0f);
    //����Ʈ
    viewport.width = app.GetWidth();
    viewport.height = app.GetHeight();
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
    scale.x = 1.0f;
    scale.y = 1.0f;
}

void Camera::UpdateMatrix()
{
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());

    if (update) return;
    GameObject::UpdateMatrix();
    //����� ���̵����
    V = Matrix::CreateTranslation(-GetWorldPos().x, -GetWorldPos().y, 0.0f);
    //����������� �������
    P = Matrix::CreateOrthographic(app.GetWidth()/ scale.x, app.GetHeight()/ scale.y, 0.0f, 10.0f);

    VP = V * P;
    update = true;

   
}

void Camera::ResizeScreen()
{
    //viewport.x = app.GetWidth() / 2.0f;
    //viewport.width = app.GetWidth()/2.0f;
    //viewport.height = app.GetHeight()/2.0f;
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}
