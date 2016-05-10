#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <assert.h>
#include <limits.h>
using namespace std;

// this is a student.
void reverseWord(char *s)
{
    char *pEnd = s + strlen(s) - 1;
    char *pStart = s;

    // reverse all string
    while (pStart < pEnd)
    {
        char c; 
        c = *pStart;
        *pStart++ = *pEnd;
        *pEnd-- = c;
    }

    // reverse per word
    pStart = pEnd = s; 

    while (*pEnd != '\0')
    {
        if (*pEnd == ' ') 
        {
            char *pEndTmp = pEnd - 1;
            char *pStartTmp = pStart;

            while (pStartTmp < pEndTmp) 
            {
                char c; 
                c = *pStartTmp;
                *pStartTmp++ = *pEndTmp;
                *pEndTmp-- = c;
            }

            while (*pEnd == ' ')
                pEnd++;

            pStart = pEnd;
        }
        else
            pEnd++;
    }
}

int atoi(const char *s)
{
    assert(s != NULL);

    const char *p = s;  
    int sign = 1;
    int intVal = 0;

    if (*p == '-') sign = -1;
    if (*p == '-' || *p == '+') p++;  

    while (*p != '\0')
    {
        if (*p <= '9' && *p >= '0')
        {
            intVal = intVal * 10 + (*p - '0');    
            p++;
        }
        else
        {
            cout << "invalid charactor: " << (char)*p << endl; 
            return 0;
        }
    }

    intVal = intVal * sign;
}

int main()
{
    char s[] = {"I am a student."};
    //_strrev(s);
    //cout << s << endl;
    reverseWord(s);
    cout << s << endl;

    int num = atoi("-22345");
    cout << num << endl;
    num = atoi("999999922345999999");
    cout << num << endl;

    return 0;
}
