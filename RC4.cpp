#include "RC4.h"

//������� �� ������� ��������� ������/ �� ��� ���������/ ������� �������
char* RC4::Crypt(Key &key, char *data, int size)
{
    int n;
    for (n = 0; n<size; n++) data[n] ^= key.GetXor();

    return data;
}
