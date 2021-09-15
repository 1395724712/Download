#include<iostream>

#include<string>

#include"fileTransferClient.h"

#include"muduo/net/EventLoop.h"

using namespace std;
int main()
{
	cout << "pid = " << getpid();
	string fileName = "/home/wendell/receiveFile/test.txt";
	EventLoop loop;
	fileTransferClient client(&loop, InetAddress("192.168.123.202", 2021), fileName);
	client.connect();
	loop.loop();

	cout << "run finished" << endl;

	return 0;
}