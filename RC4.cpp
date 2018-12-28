#include "RC4.h"

//шифруем по размеру поданного текста/ ну или дешифруем/ разницы никакой
char* RC4::Crypt(Key &key, char *data, int size)
{
    int n;
    for (n = 0; n<size; n++) data[n] ^= key.GetXor();

    return data;
}
