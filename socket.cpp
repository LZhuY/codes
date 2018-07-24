#include <iostream>

/*
struct sockaddr_in {
   sa_family_t    sin_family; // address family: AF_INET 
   in_port_t      sin_port;   // port in network byte order 
   struct in_addr sin_addr;   // internet address 
};

// Internet address
struct in_addr {
   uint32_t       s_addr;     // address in network byte order
};
*/

//server
int main(int argc, char** argv)
{
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9998);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	listen(fd, 10);
	int cfd = accept(fd, struct sockaddr*(NULL), NULL);
	char buff[1024];
	int n = recv(cfd, buff, 1024, 0);
	send(cfd, buff, strlen(buff), 0);
}

//client
int main(int argc, char** argv){
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[2]);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	connect(fd, (struct sockaddr*)&serveraddr, sizoef(serveraddr));
	char buff[1024];
	fgets(buff, 1024, stdin);
	send(fd, buff, strlen(buff), 0);
	recv(fd, buff, 1024, 0);
}