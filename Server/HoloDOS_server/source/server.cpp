/*
 * server.cpp
 *
 *  Created on: 23 февр. 2024 г.
 *      Author: c0nt1nyou
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int Socket(int domain, int type, int protocol){
	int res = socket(domain, type, protocol);
	if(res == -1){
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}
	return res;
}

void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen){
	int res = bind(sockfd, addr, addrlen);
	if(res == -1){
		perror("Binding failed");
		exit(EXIT_FAILURE);
	}
}

void Listen(int sockfd, int backlog){
	int res = listen(sockfd, backlog);
	if(res == -1){
		perror("Listening failed");
		exit(EXIT_FAILURE);
	}
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
	int res = accept(sockfd, addr, addrlen);
	if(res == -1){
		perror("Listening failed");
		exit(EXIT_FAILURE);
	}
	return res;
}

int main(){
	int server = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1488);
	Bind(server, (struct sockaddr*)&addr, sizeof addr);
	while(1){
		Listen(server, 5);
		socklen_t addrlen = sizeof addr;
		int fd = Accept(server, (struct sockaddr*)&addr, &addrlen);
		ssize_t nread;
		char buf[256];
		nread = read(fd, buf, 256);
		if(nread == -1){
			perror("Reading failed");
			exit(EXIT_FAILURE);
		}
		if(nread == 0){
			printf("EOF\n");
		}
		write(STDOUT_FILENO, buf, nread);
		write(fd, buf, nread);
		printf("\n");

		sleep(1);
		close(fd);
	}
	sleep(1);

	close(server);
	return 0;
}



