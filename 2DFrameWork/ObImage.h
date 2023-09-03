#pragma once

enum class ANIMSTATE
{
    STOP,           //����
    LOOP,           //�ݺ����
    ONCE,           //�ѹ��� ���
    REVERSE_LOOP,   //������ �ݺ����
    REVERSE_ONCE
};

class ObImage : public GameObject
{
private:
    static ID3D11Buffer*        vertexBuffer;
    static ID3D11Buffer*        uvBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();

private:
    ID3D11ShaderResourceView*   SRV;
    ID3D11SamplerState*         sampler;
    D3D11_SAMPLER_DESC	        samplerDesc;
private:
    bool                        animXAxis; //�������
    float                       animTime;
    float                       animInterval;
public:
    ANIMSTATE                   animState;//�ִϸ��̼� ����
    Vector4                     uv;
    Int2                        imageSize;
    wstring                     file;
    Int2                        maxFrame;
    Int2                        frame;
private:
    void PlayAnim();
public:
    ObImage();
    ~ObImage();
    void LoadFile(wstring file);
    void Render(class Camera* cam = app.maincam)override;
    ID3D11ShaderResourceView* GetSRV(){ return SRV; }
    void ChangeSampler(D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_POINT,
        D3D11_TEXTURE_ADDRESS_MODE addressU = D3D11_TEXTURE_ADDRESS_WRAP,
        D3D11_TEXTURE_ADDRESS_MODE addressV = D3D11_TEXTURE_ADDRESS_WRAP);
    void ChangeAnim(ANIMSTATE anim, float interval, bool xAxis = true);
};

