/*
 * client.cpp
 *
 *  Created on: 23 февр. 2024 г.
 *      Author: c0nt1nyou
 */

#include "errproc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int fd = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1488);
	Inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	Connect(fd, (struct sockaddr*) &addr, sizeof(addr));
    //while(1){
		char buffer[256];
		printf("Enter the text: ");
		scanf("%[^\n]", buffer);
		write(fd, buffer, (int)strlen(buffer));
		char buf[256];
		ssize_t nread;
		nread = read(fd, buf, 256);
		if(nread == -1){
			perror("Reading failed");
			exit(EXIT_FAILURE);
		}
		if(nread == 0){
			printf("EOF\n");
		}

		printf("%s\n", buf);
        //printf("Hui");
        sleep(1);
		close(fd);
    //}
	return 0;
}
