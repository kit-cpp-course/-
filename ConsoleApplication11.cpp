#include "stdafx.h"
#include <iostream> // потоки ввода-вывода

#include <winsock2.h> // работа с сокетами
#include "RC4.h"

using namespace std;

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    WORD wVersionRequested;
    WSADATA wsaData;
    //подключили сокеты
    SOCKET s;
    sockaddr_in addr;

    int err;

    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);

    if (err != 0) return;

    //указали технологию подключения
    //ip
    //port
    //инициализировали подключение
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1280);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    s = socket(AF_INET, SOCK_STREAM, 0);

    //законектились
    connect(s, (sockaddr*)&addr, sizeof(addr));

    cout << "Введите строку" << endl;

    char b[256];
    cin.getline(b, sizeof(b), '\n');

    int cnt = 0;
    while (b[cnt] != '\0')
    {
        cnt++;
    }

    Encription &rc4 = RC4();
    Key key = Key((char*)"ключ", 0);
    char *cryptData = rc4.Crypt(key, b, cnt);
    //передали серверу шифр
    send(s, b, sizeof(b), 0);
    //слушаем ответ
    //если ответил, то читаем
    if (recv(s, b, sizeof(b), 0) != 0)
        cout << b << endl;

    system("pause");
    closesocket(s);
    WSACleanup();
}
