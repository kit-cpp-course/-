#pragma once
class Key
{
    private:
        char S[256];
        unsigned int i, j;
        inline void Swap(int, int);
    public:
        Key(char *key, int len);

        //само шифрование
        char GetXor();
};

