#include"server.h"

void toString(char*a, elf s)
{
    int count = 0;

    toChar(s.elfKind, a, count);

    toChar(s.level, a, count);

    toChar(s.exp, a, count);
}

void winRateStr(char*a, int k, int l, int e)
{
    int count = 0;

    toChar(k, a, count);

    toChar(l, a, count);

    toChar(e, a, count);
}

void toChar(int a, char*b, int& c)
{
    char x[10] = { '\0' };
    for (int i = 0; i < 10; i++)
    {
        x[i] = '\0';
    }
    itoa(a, x, 10);

    strncpy(b + c, x, strlen(x));
    c = c + strlen(x);

    b[c] = ',';
    c++;
}

void readInfo(char* info, int& kind, int& level, int& exp)
{
    int i;

    kind = atoi(info);
    for (i = 0; info[i] != ','; i++);
    i++;

    level = atoi(info + i);

    for (; info[i] != ','; i++);

    exp = atoi(info + i + 1);
}