#pragma once
//Author:wh
//Date:20210914
//Description:负责接收文件的客户端

#include<iostream>
#include<fstream>

#include"muduo/net/TcpClient.h"


using namespace std;
using namespace muduo;
using namespace muduo::net;
class fileTransferClient
{
public:
	fileTransferClient(EventLoop* loop, const InetAddress& serverAddr, const string& fileName);

	~fileTransferClient();
	
	void connect() { client_.connect(); };
	
private:
	void onConnection(const TcpConnectionPtr& conn);

	void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime);
	
	
	ofstream outFile_;

	TcpClient client_;

	EventLoop * loop_;
};

