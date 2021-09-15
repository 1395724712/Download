#include "fileTransferServer.h"
#include"muduo/base/Logging.h"
using namespace placeholders;
fileTransferServer::fileTransferServer(EventLoop * loop, const InetAddress & listenAddr, string fileName):
	server_(loop,listenAddr,"fileTransferServer")
{
	inFile.open(fileName, ios::in);
	assert(inFile);

	server_.setConnectionCallback(bind(&fileTransferServer::onConnection, this, _1));
	server_.setWriteCompleteCallback(bind(&fileTransferServer::onWriteComplete, this, _1));
}

fileTransferServer::~fileTransferServer()
{
	inFile.close();
}

void fileTransferServer::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << "Connection from" << conn->peerAddress().toIpPort() << " to " <<
		conn->localAddress().toIpPort() << " is " <<
		(conn->connected() ? " UP" : " DONW");

	if(conn->connected()&&!inFile.eof())
	{
		string msg;
		inFile >> msg;
		conn->send(msg);
	}
	else
	{
		conn->shutdown();
	}
}

void fileTransferServer::onWriteComplete(const TcpConnectionPtr& conn)
{
	string msg;
	if(getline(inFile,msg))
	{
		msg += "\n";
		conn->send(msg);
	}
	else
	{
		conn->shutdown();
	}
}
