#include "stdafx.h"
#include <iostream>

#include <winsock2.h>

using namespace std;

class RC4{
	char S[256];
	unsigned int i,j;
	inline void Swap(int,int);
public:
	char GetXor();
	void Init(char *key,int len);
	char* Crypt(char *data,int size);
};

void RC4::Init(char *key,int len)
{
	if(!len) len=strlen((char*)key);
	for(i=0; i<256; i++) S[i]=i;
	for(i=j=0; i<256; i++) {
		j=(j+S[i]+key[i%len])&255;
		Swap(i,j);
	}
	i=j=0;
}


char RC4::GetXor()
{
	i=(i+1)&255; j=(j+S[i])&255; Swap(i,j);
	return S[(S[i]+S[j])&255];
}


void RC4::Swap(int i,int j)
{
	char t=S[i]; S[i]=S[j]; S[j]=t;
}


char* RC4::Crypt(char *data,int size)
{
	int n;
	for(n=0; n<size; n++) data[n]^=GetXor();

	return data;
}


//функция для ожидания клиентов
//это поток
DWORD WINAPI thread_func(LPVOID ps)
{

int i, j, l;
char ch, b[200];

SOCKET s = *((SOCKET *) ps);
//слушаем пользователей
//если подлючился, то дешифруем//или шифруем/не важно
while(recv(s, b, sizeof(b), 0) != 0)
{

RC4 rc4;
cin.getline(b, sizeof(b), '\n');

int cnt = 0;
while(b[cnt] != '\0')
{
	cnt++;
}
rc4.Init((char*)"ключ",0);
char *cryptData = rc4.Crypt(b,cnt);
//отправляем
send(s, b, sizeof(b), 0);
}

closesocket(s);

return 0;

}

int cl_num = 0;

void main()
{
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
WORD wVersionRequested;
WSADATA wsaData;
SOCKET s1, s2;
sockaddr_in addr1, addr2;

int err, size;

SetConsoleOutputCP(1251);
wVersionRequested = MAKEWORD(2, 2);
err = WSAStartup(wVersionRequested, &wsaData);

if (err != 0) return;

addr1.sin_family = AF_INET;
addr1.sin_port = htons(1280);
addr1.sin_addr.s_addr = inet_addr("127.0.0.1");
s1 = socket(AF_INET, SOCK_STREAM, 0);
bind(s1, (sockaddr*) &addr1, sizeof(addr1));
listen(s1, 5);

cout << "Сервер готов к приёму клиентов." << endl;

//вот здесь прослушка пользователей
//то есть может не только один подклчится, а многие
while (true)
{
	size = sizeof(addr2);
	s2 = accept(s1, (sockaddr*)&addr2, &size);
	cout << "Присоединился клиент #" << ++cl_num << endl;
	CreateThread(NULL, NULL, thread_func, &s2, NULL, 0);
}

WSACleanup();

}

