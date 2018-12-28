#pragma once
#include "Encription.h"
#include "Key.h"

class RC4 : public Encription
{
    public:

        //шифрование (для всех байтов)
        char* Crypt(Key &key, char *data, int size) override;
};
