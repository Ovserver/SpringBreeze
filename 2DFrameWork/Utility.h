#pragma once

namespace Utility
{
    //�浹Ÿ��
    struct RECT
    {
        Vector2 min;
        Vector2 max;
        RECT(Vector2 pivot, Vector2 scale);
        RECT(GameObject* ob);
    };
    struct CIRCLE
    {
        Vector2 pivot;
        float   radius;
        CIRCLE(Vector2 pivot, Vector2 scale);
        CIRCLE(GameObject* ob);
    };

    //�簢�� �� �� ��ǥ
    bool IntersectRectCoord(RECT & rc, Vector2 coord);
    bool IntersectCircleCoord(CIRCLE & cc, Vector2 coord);

    //�׸� �׸�
    bool IntersectRectRect(RECT & rc1, RECT & rc2);
    //OBB
    bool IntersectRectRect(GameObject * ob1, GameObject * ob2);

    //�� ��
    bool IntersectCircleCircle(CIRCLE & cc1, CIRCLE & cc2);
    //�׸� ��
    bool IntersectRectCircle(RECT & rc, CIRCLE & cc);

    bool IntersectRectCircle(RECT& rc, CIRCLE& cc,int& result);

    float DirToRadian(Vector2 Dir);

    Vector2 WorldToScreen(Vector2 wol);

    //���ø� �Լ��� ����,���� �и� �Ұ�
    template<typename T>
    T Saturate(T src, T min = 0, T max = 1)
    {
        if (src < min)
        {
            return min;
        }
        else if (src > max)
        {
            return max;
        }
        return src;
    }

    template<typename T>
    void Swap(T & a, T & b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    void Replace(string* str, string comp, string rep);

    template<typename T>
    T Lerp(T& a, T& b , float w)
    {
        return a + (b - a) * w;
    }

};
