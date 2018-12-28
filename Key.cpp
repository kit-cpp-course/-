#include <algorithm>
#include "stdafx.h"
#include "Key.h"

//меняем местами
void Key::Swap(int, int)
{
    char t = S[i]; S[i] = S[j]; S[j] = t;
}

//работает как XOR операция ^ , но просто расписаная
char Key::GetXor()
{
    i = (i + 1) & 255; j = (j + S[i]) & 255; Swap(i, j);
    return S[(S[i] + S[j]) & 255];
}

//добавляется кусок ключа и заносится в рамки 255 битов
Key::Key(char *key, int len)
{
    if (!len) len = strlen((char*)key);
    for (i = 0; i<256; i++) S[i] = i;
    for (i = j = 0; i<256; i++) {
        j = (j + S[i] + key[i%len]) & 255;
        Swap(i, j);
    }
    i = j = 0;
}
