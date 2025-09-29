/*
============================================================================
Name : 34b.c
Author : Preet Chandrakar
Description : Write a program to create a concurrent server.
              b. use pthread_create

Date: 22nd Sept, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080 // 8080 is TCP port number
#define BUFFER_SIZE 1024

void *handle_client(void *arg)
{
    int client_socket = *(int *)arg;
    free(arg);

    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0'; // Null terminate
        printf("Client: %s\n", buffer);

        write(client_socket, buffer, strlen(buffer)); // return Echo msg to client
    }

    printf("Client disconnected.\n");
    close(client_socket);
    pthread_exit(NULL);
}

int main()
{
    int server_fd, *new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create TCP  socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) // Parameter: IPv4, TCP, Default protocol(TCP)
    {
        perror("Socket Creation Failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to IP/Port which configure server address
    server_addr.sin_family = AF_INET;         // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // localhost+network
    server_addr.sin_port = htons(PORT);       // convert port number to network byte order

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind failed: port is already in use");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1)
    {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket == -1)
        {
            perror("Accept failed");
            continue;
        }

        printf("New client connected.\n");

        pthread_t tid;
        new_sock = malloc(sizeof(int));
        *new_sock = client_socket;

        if (pthread_create(&tid, NULL, handle_client, (void *)new_sock) != 0)
        {
            perror("pthread_create failed");
            free(new_sock);
        }

        pthread_detach(tid); // Auto-reclaim resources when thread finishes
    }

    close(server_fd);
    return 0;
}

/*
Terminal 1:
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Server listening on port 8080...

Terminal 2:
iiitb@Preet:~/MyLinux/Hands_on_2$ telnet 127.0.0.1 8080
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
Hello World!!

Terminal 1:
New client connected.
Client: Hello World!!

Terminal 2:
Hello World!!
^]

telnet> quit
Connection closed.

Terminal 1:
Client disconnected.
^C
*/