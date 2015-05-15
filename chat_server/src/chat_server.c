/*
 ============================================================================
 Name        : Chat.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 ============================================================================
 Name        : Chat.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define MYPORT 3490
#define BACKLOG 10 //conexiones en cola
#define MAXDATASIZE 100

int main(void) {
	int sockfd, new_fd, numBytes;
	struct sockaddr_in my_addr;
	struct sockaddr_in client_addr;
	char bufer[MAXDATASIZE];
	int mjsEnviado = 1;
	int msjRecibido = 1;
	int yes=1;
	int sin_size;
	char *chat_dialogo;
	chat_dialogo = (char *) malloc(100);
	int long_chat_dialogo;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	if((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1)
	{
		perror("setsockopt");
		exit(1);
	}

	my_addr.sin_family = AF_INET; // ordenacion de byte de la maquina
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero), '\0', 8);
	if((bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))) == -1)
	{
		perror("bind");
		exit(1);
	}
	if((listen(sockfd, BACKLOG)) == -1 )
	{
		perror("listen");
		exit(1);
	}
	sin_size = sizeof(struct sockaddr_in);
			if((new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size)) == -1 )
			{
				perror("accept");
			}
			printf("Conexion establecida\n");

	while(1)
	{
			fflush(stdout);
			__fpurge(stdin);

			//Mensaje servidor
			printf("Servidor: ");
			scanf("%[^\n]s", chat_dialogo);
			long_chat_dialogo = strlen(chat_dialogo);
			do
			{
			if((send(new_fd, chat_dialogo, long_chat_dialogo, 0)) == -1 )
				perror("send");
			else
				mjsEnviado = 0;
			}while(mjsEnviado);

			if((strcmp(chat_dialogo, "desconectar")) == 0 )
				break;

			//Mensaje Cliente
			if((numBytes=recv(new_fd, bufer, MAXDATASIZE-1, 0)) == -1)
							perror("recv");


			bufer[numBytes] = '\0';
			if((strcmp(bufer, "desconectar")) == 0 )
				break;
			printf("Cliente: %s\n", bufer);
			continue;
		}

	close(sockfd);
	close(new_fd);
	return 0;
}