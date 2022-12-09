//Main.cpp
#include <string>
#include <iostream>
#include "Socket.h"

using namespace std;

int main()
{
	int nChoice;
	int sum = 0;
	int port = 24242; //выбираем порт
	string ipAddress; //Адрес сервера
	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];
	cout << "1) Start server" << endl;
	cout << "2) Connect to server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
	if (nChoice == 1)
	{
		ServerSocket server;
		cout << "Starting server..." << endl;
		//Запускаем сервер
		server.StartHosting(port);
		while (true)
		{
			server.Menu();
			//Получаем данные от клиента
			//и сохраняем в переменной receiveMessage
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			sum = atoi(receiveMessage);
			if (sum == 1)
				sum = 14000;
			else if (sum == 2)
				sum = 32000;
			else if (sum == 3)
				sum == 9000;
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			sum *= atoi(receiveMessage);
			server.Result(sum);
			//Отправляем данные клиенту
			//Если есть сообщение "end", завершаем работу
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
	}
	else if (nChoice == 2)
	{
		cout << "Enter an IP address: " << endl;
		//Запрашиваем IP сервера
		cin >> ipAddress;
		ClientSocket client;
		//подключаемся к серверу
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received:\n" << receiveMessage << endl;
			//отправляем сообщение
			client.SendDataMessage();
			//получаем ответ
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received:\n" << receiveMessage << endl;
			cout << "\n\nContinue?\n1 - yes, 0 - no\n";
			bool check = client.Cont();
			if (check)
				break;
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
		//Закрываем соединение
		client.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}










