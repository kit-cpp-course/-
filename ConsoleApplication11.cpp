#include "stdafx.h"
#include <iostream> // ������ �����-������

#include <winsock2.h> // ������ � ��������
#include "RC4.h"

using namespace std;

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    WORD wVersionRequested;
    WSADATA wsaData;
    //���������� ������
    SOCKET s;
    sockaddr_in addr;

    int err;

    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);

    if (err != 0) return;

    //������� ���������� �����������
    //ip
    //port
    //���������������� �����������
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1280);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    s = socket(AF_INET, SOCK_STREAM, 0);

    //�������������
    connect(s, (sockaddr*)&addr, sizeof(addr));

    cout << "������� ������" << endl;

    char b[256];
    cin.getline(b, sizeof(b), '\n');

    int cnt = 0;
    while (b[cnt] != '\0')
    {
        cnt++;
    }

    Encription &rc4 = RC4();
    Key key = Key((char*)"����", 0);
    char *cryptData = rc4.Crypt(key, b, cnt);
    //�������� ������� ����
    send(s, b, sizeof(b), 0);
    //������� �����
    //���� �������, �� ������
    if (recv(s, b, sizeof(b), 0) != 0)
        cout << b << endl;

    system("pause");
    closesocket(s);
    WSACleanup();
}
