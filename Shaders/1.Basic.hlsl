//hlsl ������ ��� X
struct VertexInput
{
    float4 position : POSITION0; //�ø�ƽ �뵵
    float4 color : COLOR0;
};
// PI
struct PixelInput
{
    float4 position : SV_POSITION; //ȭ����ǥ�� ������
    float4 color : COLOR0;
};

//�������: ���̴����� ���� ����� ������ �����Ë� ���ε��ϴ� ����

//������Ʈ�� ũ�� ȸ�� �̵�
cbuffer VS_WVP : register(b0) //register(b0)
{
    matrix WVP;
}
//��� ����
cbuffer VS_COLOR : register(b1)
{
    //4 ���� 4����Ʈ
    float4 color;
}


PixelInput VS(VertexInput input)
{
    //������ȯ�� ���� ������ ��
    PixelInput output;
    //ī�޶�,���� ���� ����� ������ȯ
    output.position = mul(input.position, WVP);
    //                             -1~ 1
    output.color = input.color + (color * 2.0f - 1.0f);
	
    //0~1
    saturate(output.color);
    
    return output;
}
//->pixel  PS   ->color
//�ȼ����̴� ���� �Լ�
float4 PS(PixelInput input) : SV_TARGET 
{
	//if (input.position.y > 200.0f)
	//{
	//	return float4(1, 0, 0, 1);
	//}
    
	float4 outputColor;
	outputColor = saturate(input.color);
    
	
    
	return outputColor;
}