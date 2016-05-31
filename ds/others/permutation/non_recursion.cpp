#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/// ȫ���еķǵݹ�ʵ��

/*

Ҫ����ȫ���еķǵݹ�ʵ�֣�����������μ����ַ�������һ�����С���"1234"����һ�����о���"1243"��
ֻҪ���ַ������������һ�����У�ȫ���е�Ҳ��ӭ�ж����ˡ�

��μ����ַ�������һ�������ˣ�
��μ����ַ�������һ�������ˣ�������"926520"����ַ��������ǴӺ���ǰ�ҵ�һ˫���ڵĵ������֣�
"20"��"52"���Ƿǵ����ģ�"26 "������Ҫ�󣬳�ǰһ������2Ϊ�滻�����滻�����±��Ϊ�滻�㣬
�ٴӺ�����һ�����滻�������С�����������Ȼ���ڣ���0��2�����У�5���ԣ���5��2�����õ�"956220"��
Ȼ���ٽ��滻�����ַ���"6220"�ߵ����õ�"950226"��

������"4321"�����Ѿ�����󡱵����У�����STL�еĴ����������ַ��������ߵ��õ��С��������"1234"������false��

������ֻҪһ��ѭ���ټ��ϼ����ַ�����һ�����еĺ����Ϳ������ɵ�ʵ�ַǵݹ��ȫ�����㷨��
������˼·���ο�STL�е�ʵ��Դ�룬����д��һ�������ϸߵĴ��롣

*/

void Swap(char *a, char *b)
{
    if (*a != *b)
    {
        char c = *a;
        *a = *b;
        *b = c;
    }
}

// ��ת����
void Reverse(char *a, char *b)
{
    while (a < b)
    {
        Swap(a++, b--);
    }
}

// ��һ������
bool Nex_permutation(char *arr)
{
    char *pEnd = arr + strlen(arr);
    if (arr == pEnd)
        return false;

    char *p, *q, *pFind;
    pEnd--; // ָ�����һ��Ԫ��
    p = pEnd;

    // �Ӻ���ǰ������һ˫���ڵĵ�������
    while (p != arr)
    {
        q = p;
        --p;
        if (*p < *q) //�ҽ��������2��,ǰһ�������滻��
        {
             //�Ӻ���ǰ�ұ��滻���ĵ�һ����
            pFind = pEnd;
            while (*pFind <= *p)
                --pFind;

            // �滻
            Swap(pFind, p);
            // �滻������ȫ����ת
            Reverse(q, pEnd);
            return true;
        }
    }
    Reverse(p, pEnd); // ���û����һ������,ȫ����ת�󷵻�false
    return false;
}

int QsortCmp(const void *pa, const void *pb)
{
    return *(char *)pa - *(char *)pb;
}

int main()
{
    cout << "ȫ���еķǵݹ�ʵ�֣�" << endl;
    char str[] = "abc";
    cout << str << "��ȫ��������: " << endl;
    // ��������
    qsort(str, strlen(str), sizeof(str[0]), QsortCmp);

    int i = 1;
    do
    {
        cout << "��" << i++ << "������: " << str << endl;
    } while (Nex_permutation(str));

    return 0;
}
