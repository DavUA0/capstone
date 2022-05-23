#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int capstone(int client_fd)
{
  char buffer[500];
  int input;
  input = read(client_fd, buffer, 700);
  printf("got %d bytes\n", input);
  
	// echo input back to client
	//	write(client_fd, buffer, input + 1); // include null
  return 0;
}

int main (int argc, char **argv, char **envp)
{
	int server_fd, client_fd;
  	socklen_t cli_len;
	struct sockaddr_in server_addr, client_addr;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
 	if (server_fd < 0)
	{
		fprintf(stderr, "Unable to open socket\n");
		exit(EXIT_FAILURE);
	}
  
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(1234);

	if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	{
		fprintf(stderr, "Cannot bind(). Exiting...\n");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 20) != 0)
	{
		fprintf(stderr, "Cannot listen(). Exiting...\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		cli_len = sizeof(client_addr);
		client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &cli_len);
		if (client_fd < 0)
		fprintf(stderr, "Cannot accept().\n");

		capstone(client_fd);

		close(client_fd);
	}

	close(server_fd);

	return 0;
}
