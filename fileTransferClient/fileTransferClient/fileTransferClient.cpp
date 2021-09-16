#include "fileTransferClient.h"

#include<string>
#include"muduo/net/EventLoop.h"
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
}

void fileTransferClient::onMessage(const TcpConnectionPtr & conn, Buffer * buf, Timestamp receiveTime)
{
	string msg(buf->retrieveAllAsString());
	if (msg.size() >= 7 && string(msg.end() - 7, msg.end()) == "\n\nEOF\n\n")
	{
		loop_->quit();
		return;
	}
	LOG_INFO << "receive " << msg.size() << " bytes data\n";
	LOG_INFO << "receive msg: " << msg;
	outFile_ << msg;
}

