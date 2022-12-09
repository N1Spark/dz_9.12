#include "Socket.h"

Socket::Socket()
{
	//���� ������������� ������� ������ ���������, ������� ��������� ��
	//������
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		cout << "WSAStartup error\n";
		system("pause");
		WSACleanup();
		exit(10);
	}

	//������� ��������� �����, �������� TCP
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//��� ���������� �������� ������ ������� ��������� �� ������
	if (_socket == INVALID_SOCKET)
	{
		cout << "Socket create error." << endl;
		system("pause");
		WSACleanup();
		exit(11);
	}


}

Socket::~Socket()
{
	WSACleanup();//������� �������
}

bool Socket::SendData(char *buffer)
{
	/*���������� ��������� �� ��������� �����*/
	send(_socket, buffer, strlen(buffer), 0);
	return true;
}

bool Socket::ReceiveData(char *buffer, int size)
{

	/*�������� ��������� � ��������� ��� � ������.
	����� �������� �����������!*/
	int i = recv(_socket, buffer, size, 0);
	buffer[i] = '\0';
	return true;
}

void Socket::CloseConnection()
{
	//��������� �����
	closesocket(_socket);
}

void Socket::SendDataMessage()
{
	//������ ��� ��������� ������������
	char type[MAXSTRLEN];
	char count[MAXSTRLEN];
	//��� ����� ������ �� ������ ����� ������ ���������
	//���� ������������, ��������� �����.
	cin >> type >> count;
	SendData(type);
	SendData(count);
}

void ServerSocket::Menu()
{
	TCHAR buf[] = { "1. Phone - 7000 grn\n2. Laptop - 24000 grn\n3. Tablet - 9000grn\nPlease choose tech and count" };
	SendData(buf);
}

void ServerSocket::Result(int sum)
{
	TCHAR buf[MAXSTRLEN];
	wsprintf(buf, TEXT("Price = %d grn"), sum);
	SendData(buf);
}

void ServerSocket::StartHosting(int port)
{
	Bind(port);
	Listen();
}

void ServerSocket::Listen()
{
	cout << "Waiting for client..." << endl;

	//��� ������ ��������� ������ � ������ �������������
	//������� ������
	if (listen(_socket, 1) == SOCKET_ERROR)
	{
		cout << "Listening error\n";
		system("pause");
		WSACleanup();
		exit(15);
	}
	/*
	����� �������� �����������. ������� ����������� �������.
	��� ������ ������ �����������, ������� accept ����������
	����� �����, ����� ������� ���������� ����� �������.
	*/
	acceptSocket = accept(_socket, NULL, NULL);
	while (acceptSocket == SOCKET_ERROR)
	{
		acceptSocket = accept(_socket, NULL, NULL);
	}
	_socket = acceptSocket;
}

void ServerSocket::Bind(int port)
{
	//��������� ��������� ������� IPv4
	addr.sin_family = AF_INET;
	/*����������� ����� "0.0.0.0"� ����������
	��������� �������� �������, ��������� ��������� � ���� sin_addr */
	inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
	//��������� ����. 
	//������� htons ��������� �������������� ����� �
	//������� ������� ����
	addr.sin_port = htons(port);

	cout << "Binding to port:  " << port << endl;
	//��� ��������� �������� � �����, ������� ��������� ��� ������
	if (bind(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cout << "Failed to bind to port\n";
		system("pause");
		WSACleanup();
		exit(14);
	}
}

bool ClientSocket::Cont()
{
	bool check = false;
	cin >> check;
	if (!check)
		return true;
	else
	{
		system("cls");
		return false;
	}
}

void ClientSocket::ConnectToServer(const char *ipAddress, int port)
{
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ipAddress, &addr.sin_addr);
	addr.sin_port = htons(port);
	//��� ��������� ����������� � ������� ������� ��������� ��� ������
	if (connect(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cout << "Failed to connect to server\n";
		system("pause");
		WSACleanup();
		exit(13);
	}
}