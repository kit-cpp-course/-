#pragma once
class Encription
{
    public:
        virtual char* Crypt(Key &key, char *data, int size) = 0;
};
