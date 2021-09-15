#include "fileTransferClient.h"

#include<string>

#include"muduo/base/Logging.h"
using namespace std::placeholders;

fileTransferClient::fileTransferClient(EventLoop* loop, const InetAddress& serverAddr, const string& fileName):
	loop_(loop),
	client_(loop,serverAddr,"FileTransferClient")
{
	outFile_.open(fileName, ios::out|ios::trunc);
	assert(outFile_);

	client_.setConnectionCallback(bind(&fileTransferClient::onConnection, this, _1));
	client_.setMessageCallback(bind(&fileTransferClient::onMessage, this, _1, _2, _3));
}

fileTransferClient::~fileTransferClient()
{
	outFile_.close();
}

void fileTransferClient::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << conn->localAddress().toIpPort() << " to " <<
		conn->peerAddress().toIpPort() << " is " <<
		(conn->connected() ? "UP" : "DOWN");
	conn->disconnected();
}

void fileTransferClient::onMessage(const TcpConnectionPtr & conn, Buffer * buf, Timestamp receiveTime)
{
	string msg(buf->retrieveAllAsString());
	LOG_INFO << "receive " << msg.size() << " bytes data\n";
	LOG_INFO << "receive msg: " << msg;
	outFile_ << msg;
	//client_.stop();
}

