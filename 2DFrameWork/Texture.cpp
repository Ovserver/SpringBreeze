#include "framework.h"

Texture::~Texture()
{
    for (auto i = textureList.begin();
        i != textureList.end(); i++)
    {
        if (i->second.srv)
        {
            i->second.srv->Release();
        }
    }
    textureList.clear();
}

ID3D11ShaderResourceView* Texture::LoadTexture(wstring file)
{
    auto iter = textureList.find(file);

    //중복된게 없다.
    if (iter == textureList.end())
    {
        ID3D11ShaderResourceView* temp;
        wstring path = L"../Contents/Images/" + file;

        //ScratchImage image;
        LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, textureList[file].img);

        textureList[file].textureSize.x = textureList[file].img.GetMetadata().width;
        textureList[file].textureSize.y = textureList[file].img.GetMetadata().height;

        HRESULT hr = CreateShaderResourceView(D3D->GetDevice(), textureList[file].img.GetImages(), textureList[file].img.GetImageCount(),
            textureList[file].img.GetMetadata(), &temp);
        Check(hr);

        textureList[file].srv = temp;
        return temp;
    }
    //기존에 할당되있던 텍스쳐를 반환
    return iter->second.srv;
}

bool Texture::DeleteTexture(wstring file)
{
    auto iter = textureList.find(file);

    //중복된게 없다.
    if (iter == textureList.end())
    {
        return false;
    }
    //first가 키, second 밸류
    iter->second.srv->Release();

    //맵에서도 삭제
    textureList.erase(iter);

    return true;
}

Int2 Texture::GetTextureSize(wstring file)
{
    return textureList[file].textureSize;
}

ScratchImage& Texture::GetTextureData(wstring file)
{
    return textureList[file].img;
}
