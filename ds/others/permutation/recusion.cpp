#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/*
��C++дһ������, �� Foo(const char *str), ��ӡ�� str ��ȫ����,
�� abc ��ȫ����: abc, acb, bca, dac, cab, cba
*/

/// ȫ���еĵݹ�ʵ�� (ȫ������f(n)=n!(����0!=1) => 3! = 3*2*1 = 6)

/*
Ϊ�����������123��ʾ���¡�123��ȫ������123��132��213��231��312��321�����֡�
���ȿ���213��321�����������εó��ġ���Ȼ���������123�е�1��������������õ��ġ�
Ȼ����Խ�123�ĵڶ�������ÿ�����������õ�132��ͬ����Ը���213��321����231��312��
��˿���֪������ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�������������ֽ�����

��ȫ������ȥ���ظ��Ĺ��򡪡�ȥ�ص�ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�����������ظ����ֵ����ֽ�����
�ñ�̵Ļ��������ǵ�i�������j��������ʱ��Ҫ��[i,j)��û�����j������ȵ�����
*/

void Swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

// ������arr�У�[l, r)���Ƿ����������±�Ϊr���������
bool IsSwap(char *arr, int l, int r)
{
    for (int i = l; i < r; ++i)
        if (arr[i] == arr[r])
            return false;
    return true;
}

#define DEBUG_LOG

#ifdef DEBUG_LOG
int x = 0;
std::string space("");
#endif

//k��ʾ��ǰѡȡ���ڼ�����,m��ʾ���ж�����.
void AllRange(char *arr, int k, int m)
{
#ifdef DEBUG_LOG
    ++x;
    space.clear();
    for (int j = 1; j < x; ++j)
        space += "\t";
    cout << space.c_str() << "#" << x << ": IN, k=" << k << endl;
#endif

    if (k == m)
    {
        static int line = 1;

#ifdef DEBUG_LOG
        cout << space.c_str() << "#" << x << ": ��" << line++ << "�����У�" << "<<< " << arr << " >>>" << endl;
#else
        cout << "\t��" << line++ << "�����У�" << arr << endl;
#endif
    }
    else
    {
        /// ��i�����ֱ�������������ֽ������ܵõ��µ�����
        for (int i = k; i <= m; ++i)
        {
            if (IsSwap(arr, k, i))
            {
#ifdef DEBUG_LOG
                cout << space.c_str() << "#" << x << ": LOOP : k=" << k << ", i=" << i << endl;
                std::string old = arr;
#endif

                Swap(arr+k, arr+i);

#ifdef DEBUG_LOG
                cout << space.c_str() << "#" << x << ": SWAP 1: " << old.c_str() << " => " << arr << ", DOWN >>" << endl;
#endif

                AllRange(arr, k+1, m);

#ifdef DEBUG_LOG
                old.clear(); old = arr;
#endif

                Swap(arr+k, arr+i);

#ifdef DEBUG_LOG
                cout << space.c_str() << "#" << x << ": SWAP 2: " << old.c_str() << " => " << arr << endl;
#endif
            }
        }
    }

#ifdef DEBUG_LOG
    cout << space.c_str() << "#" << x-- << ": OUR OF AR ! UP <<" << endl;
    space.clear();
    for (int j = 1; j < x; ++j)
        space += "\t";
#endif
}

void Foo(char *str)
{
    AllRange(str, 0, strlen(str)-1);
}

int main()
{
    cout << "ȥ��ȫ���еĵݹ�ʵ��" << endl;
    char str[] = "123";
    cout << "string(" << str << ")��ȫ�������£�" << endl;
    Foo(str);

    return 0;
}
