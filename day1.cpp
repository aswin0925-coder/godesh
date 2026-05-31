#include<iostream>
#include<string>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>



int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    /*this is the socket calling i mean the socket is being
    initialized here 
    
    socket() this is a place where the data is sent and 
    recieved over the network 
    
    server_fd this is the value that is a ticket or handle
    that represents the socket
    
    AF_INET this is the family of ipv4 ip addresses
    
    SOCK_STREAM this is the type of socket (TCP)
    
    0 this is the protocol (0 means default)
    */

    if (server_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }
    //the above code is checking if the socket was created successfully. If the socket() function returns -1, it means that there was an error in creating the socket, and the program will print an error message and exit with a non-zero status.

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Failed to set socket options" << std::endl;
        close(server_fd);
        return 1;
    }
    //setsockopt() is a function used to set options on a socket. In this case, it is being used to set the SO_REUSEADDR option on the server socket. This option allows the socket to be bound to an address that is already in use, which can be useful for quickly restarting a server without waiting for the previous socket to time out.

    sockaddr_in address;
    std::memset(&address, 0, sizeof(address));
    //sockaddr_in is a structure that holds an internet address. It is used to specify the address and port number for the server socket.

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(6379);
    
    
    /*the above code initializes the address structure 
    with the IP address and port number for the server 
    socket*/


    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        close(server_fd);
        return 1;
    }
    //the above code binds the server socket to the specified address and port. If the bind() function returns -1, it means that there was an error in binding the socket, and the

    if (listen(server_fd, 5) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(server_fd);
        return 1;
    }

    char buffer[1024];

    while (true) {
        sockaddr_in client_address;
        socklen_t client_length = sizeof(client_address);

        int client_fd = accept(server_fd, (sockaddr*)&client_address, &client_length);
        if (client_fd < 0) {
            std::cerr << "Failed to accept client connection" << std::endl;
            break;
        }

        while (true) {
            ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);
            if (bytes_read == 0) {
                break;
            }
            if (bytes_read < 0) {
                std::cerr << "Failed to read from client" << std::endl;
                break;
            }

            ssize_t bytes_sent = 0;
            while (bytes_sent < bytes_read) {
                ssize_t sent = send(client_fd, buffer + bytes_sent, bytes_read - bytes_sent, 0);
                if (sent < 0) {
                    std::cerr << "Failed to send data to client" << std::endl;
                    bytes_sent = -1;
                    break;
                }
                bytes_sent += sent;
            }

            if (bytes_sent < 0) {
                break;
            }
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}