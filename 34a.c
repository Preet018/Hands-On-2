/*
============================================================================
Name : 34a.c
Author : Preet Chandrakar
Description : Write a program to create a concurrent server.
                a. Use fork

Date: 21st Sept, 2024.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PORT 8080
#define BUFF_SIZE 1024

void handle_client(int client_socket)
{
    char buff[BUFF_SIZE] = {0};
    const char *server_response = "Message received. Goodbye!";
    ssize_t bytes_read;

    // Read data from the client
    bytes_read = read(client_socket, buff, BUFF_SIZE - 1);
    if (bytes_read > 0)
    {
        buff[bytes_read] = '\0';
        printf("Received from client: %s\n", buff);
    }

    // Send a response back
    send(client_socket, server_response, strlen(server_response), 0);

    // Close the client-specific socket
    close(client_socket);
    exit(0); // Child process exits
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    pid_t child_pid;

    // Create server socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Concurrent server (using fork) listening on port %d...\n", PORT);

    while (1)
    {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0)
        {
            perror("accept failed");
            continue; // Go to next iteration
        }

        // Fork a new process to handle the client
        child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork failed");
            close(new_socket);
            continue;
        }

        if (child_pid == 0)
        {
            // This is the child process
            close(server_fd); // Child doesn't need the listening socket
            printf("Child process %d handling client...\n", getpid());
            handle_client(new_socket);
        }
        else
        {
            // This is the parent process
            close(new_socket); // Parent doesn't need the client socket
            printf("Parent process %d accepted new connection, forked child %d.\n", getpid(), child_pid);
            // Wait for any child process to prevent zombies
            waitpid(-1, NULL, WNOHANG);
        }
    }

    close(server_fd);
    return 0;
}

/*
iiitb@Preet:~/MyLinux/Hands_on_2$ ./a.out
Concurrent server (using fork) listening on port 8080...
Parent process 5727 accepted new connection, forked child 5799.
Child process 5799 handling client...
Received from client: Hello World!!

^C

iiitb@Preet:~/MyLinux/Hands_on_2$ telnet 127.0.0.1 8080
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
Hello World!!
Message received. Goodbye!Connection closed by foreign host.
*/