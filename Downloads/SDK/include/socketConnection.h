#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define BUF_SIZE 128
#define IP "localhost"
#define PORT 5000

struct sockaddr_in server_addr, client_addr;
int server_fd, client_fd, len, msg_size, option, optlen;
char temp[20], test[20], buffer[BUF_SIZE];

void open_server()
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1){
        printf("server : can not open socket!\n");
        exit(0);
    }

    optlen = sizeof(option);
    option = TRUE;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    memset(&server_addr, 0x00, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Server : can not bind local address\n");
        exit(0);
    }

    if(listen(server_fd, 5) < 0){
        printf("server : can not listen connect.\n");
        exit(0);
    }

    memset(buffer, 0x00, sizeof(buffer));
    len = sizeof(client_addr);
    printf("====[PORT]==== : %d ====\n", PORT);
}

char* connectionAndGetData()
{
    printf("server is waiting client connection reqeust...\n");	
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
    if(client_fd < 0){
        printf("server : accept failed!\n");
        exit(0);
    }
    
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));
    printf("Server : %s client connect.\n", temp);

    recv(client_fd, (char *)buffer, 5/*BUF_SIZE*/, 0);

    printf("get message : %s\n", buffer);
    printf("message size : %d\n", sizeof(buffer));

    close(client_fd);

    printf("server : %s client closed.\n", temp);

    return buffer;
}

void close_server()
{
    close(server_fd);
    printf("====== server socket is closed. ======\n");
}
