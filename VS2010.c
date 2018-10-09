#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "wsock32.lib")


int main(){
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		printf("Initial Winsock Fail.\n");
	}

	struct sockaddr_in localAddr, dstAddr;
	int addrlen, rv, reuse = 1;
	struct ip_mreq mreq, mreq2;

	//Create Socket
	gUdpSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (gUdpSock < 0) {
		printf("Create Socket, WSAGetLastError = %d\n", WSAGetLastError());
		return;
	}
	
	//Set Sock Opt
	if(setsockopt(gUdpSock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0){
		printf("Setting SO_REUSEADDR, WSAGetLastError = %d\n", WSAGetLastError());
		return;
	}

	//Bind ip and port
	SetAddrin(&localAddr, AF_INET, inet_addr(gLocalIP1), gMultiGroupPort_Quote1);
	addrlen = sizeof(localAddr);
	if (bind(gUdpSock, (struct sockaddr*) &localAddr, sizeof(localAddr)) < 0) {        
		printf("Bind, WSAGetLastError = %d\n", WSAGetLastError());
		return;
	}

	//Join multicast group
	mreq.imr_multiaddr.s_addr = inet_addr(gMultiGroupIP_Quote1);         
	mreq.imr_interface.s_addr = inet_addr(gLocalIP1);

	if (setsockopt(gUdpSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) < 0) {
		printf("Setsockopt Mreq, WSAGetLastError = %d\n", WSAGetLastError());
		return;
	}
  return 0;
}
