
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include <iostream>

int main()
{
	Poco::Net::HTTPClientSession cs("jjuiddong.iptime.org", 4001);
	Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET
		, "/?encoding=text", Poco::Net::HTTPMessage::HTTP_1_1);
	request.set("origin", "http://www.websocket.org");
	Poco::Net::HTTPResponse response;

	try {

		Poco::Net::WebSocket* m_psock = new Poco::Net::WebSocket(cs, request, response);
		char const *testStr = "Hello echo websocket!";
		char receiveBuff[256];

		int len = m_psock->sendFrame(testStr, strlen(testStr), Poco::Net::WebSocket::FRAME_TEXT);
		std::cout << "Sent bytes " << len << std::endl;
		int flags = 0;

		int rlen = m_psock->receiveFrame(receiveBuff, 256, flags);
		std::cout << "Received bytes " << rlen << std::endl;
		receiveBuff[rlen] = NULL;
		std::cout << receiveBuff << std::endl;

		m_psock->close();

	}
	catch (std::exception &e) {
		std::cout << "Exception " << e.what();
	}
}
