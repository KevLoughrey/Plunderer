// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : Used to send packets between computers
#ifndef _NET_H_
#define _NET_H_
#include <winsock2.h>
#include <sstream>
#include <string.h>
class Net
{
private:
	int sockfd; //socket file descriptor
	int new_fd; //used to create new socket for new connection 
	//string ourIP;
	sockaddr_in their_addr; //use to store remote address info

	sockaddr_in my_addr; //used to store my address info
	fd_set master;
	int fdmax;
	fd_set read_fds; // temp file descriptor list for select()	
	
	//for the log
	std::ostringstream s;

public:
	static const int BUFFER_SIZE=1000;
	///Sets up UDP connection
	/// \param[port] port to setup connection on
	void setupUDP(int port);
	///Sets up UDP connection
	/// \param[port] port to setup connection on
	/// \param[ip] our ip address
	void setupUDP(int port, char * ip);
	///Send data
	/// \param[ip] ip to send info to
	/// \param[port] port to send info to
	/// \param[message] message to send
	virtual void sendData(char* ip,int port,char* message);
	///Listen for messages
	/// \param[message] will be filled if a message is received
	/// \return wether a message was received
	int receiveData(char* message);
	///initialise the socked	
	void initialise();
	///close the socket
	void closeSocket();
	///close socket and do other cleanup stuff
	void cleanup();
	void Net::error(const char* error);
	///Get ip of whoever sent us message
	char* Net::getSenderIP();
	///Get port of whoever sent us message
	int Net::getSenderPort();
	///Return out port
	int Net::getOurPort();

	int portNum;
	///Return out ip
	char* Net::getOurIP();
	char* ourIP;
};

#endif  