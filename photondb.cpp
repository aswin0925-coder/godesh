#include<iostream>
#include<string>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

struct CommandResponse
{
    std::string text;
    bool close_connection;
};

std::string trim_copy(const std::string& text)
{
    std::size_t start_index = 0;

    while (start_index < text.size() && (text[start_index] == ' ' || text[start_index] == '\t' || text[start_index] == '\r' || text[start_index] == '\n')) {
        ++start_index;
    }

    std::size_t end_index = text.size();
    while (end_index > start_index && (text[end_index - 1] == ' ' || text[end_index - 1] == '\t' || text[end_index - 1] == '\r' || text[end_index - 1] == '\n')) {
        --end_index;
    }

    return text.substr(start_index, end_index - start_index);
}

bool send_all(int socket_fd, const std::string& text)
{
    std::size_t bytes_sent = 0;

    while (bytes_sent < text.size()) {
        ssize_t sent = send(socket_fd, text.data() + bytes_sent, text.size() - bytes_sent, 0);
        if (sent <= 0) {
            return false;
        }

        bytes_sent += static_cast<std::size_t>(sent);
    }

    return true;
}

CommandResponse handle_command(const std::string& raw_line)
{
    std::string line = trim_copy(raw_line);
    if (line.empty()) {
        return {"", false};
    }

    std::size_t command_separator = line.find(' ');
    std::string command = command_separator == std::string::npos ? line : line.substr(0, command_separator);
    std::string arguments = command_separator == std::string::npos ? "" : trim_copy(line.substr(command_separator + 1));

    if (command == "PING") {
        return {"PONG", false};
    }

    if (command == "ECHO") {
        if (arguments.empty()) {
            return {"ERR missing message", false};
        }

        return {arguments, false};
    }

    if (command == "QUIT") {
        return {"BYE", true};
    }

    if (command == "SET" || command == "GET" || command == "DEL") {
        return {"ERR storage layer not implemented yet", false};
    }

    if (command == "HELP") {
        return {"Commands: PING, ECHO <message>, SET <key> <value>, GET <key>, DEL <key>, QUIT", false};
    }

    return {"ERR unknown command", false};
}

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Failed to set socket options" << std::endl;
        close(server_fd);
        return 1;
    }

    sockaddr_in address;
    std::memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(6379);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        close(server_fd);
        return 1;
    }

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

        std::string pending_input;

        while (true) {
            ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);
            if (bytes_read == 0) {
                break;
            }

            if (bytes_read < 0) {
                std::cerr << "Failed to read from client" << std::endl;
                break;
            }

            pending_input.append(buffer, static_cast<std::size_t>(bytes_read));

            bool should_close_client = false;
            std::size_t newline_position = std::string::npos;

            while ((newline_position = pending_input.find('\n')) != std::string::npos) {
                std::string request_line = pending_input.substr(0, newline_position);
                pending_input.erase(0, newline_position + 1);

                CommandResponse response = handle_command(request_line);
                if (!response.text.empty()) {
                    if (!send_all(client_fd, response.text + "\n")) {
                        std::cerr << "Failed to send data to client" << std::endl;
                        should_close_client = true;
                        break;
                    }
                }

                if (response.close_connection) {
                    should_close_client = true;
                    break;
                }
            }

            if (should_close_client) {
                break;
            }
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}





