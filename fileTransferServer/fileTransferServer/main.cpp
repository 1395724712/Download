#include <cstdio>

#include<iostream>

#include"fileTransferServer.h"

#include"muduo/base/Logging.h"
using namespace std;
int main()
{
	LOG_INFO << "pid = " << getpid();
	EventLoop loop;
	string fileName = "/home/lucky7/sendFile/test.c";
	fileTransferServer server(&loop, InetAddress(2021), fileName);
	server.start();
	loop.loop();

	return 0;
}