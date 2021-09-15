#pragma once
//Author:wh
//Date:20210914
//Description:文件传输服务器

#include<iostream>
#include<fstream>
#include<string>

#include"muduo/net/TcpServer.h"
#include"muduo/net/EventLoop.h"
#include"muduo/net/InetAddress.h"

using namespace std;
using namespace muduo;
using namespace muduo::net;
class fileTransferServer
{
public:
	fileTransferServer(EventLoop *loop, const InetAddress& listenAddr, string fileName);
	~fileTransferServer();

	void start()
	{
		server_.start();
	}
	
private:
	void onConnection(const TcpConnectionPtr& conn);

	void onWriteComplete(const TcpConnectionPtr& conn);
	
	TcpServer server_;
	ifstream inFile;
};

