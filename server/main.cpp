#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

int main()
{

    int server_fd{socket(AF_INET, SOCK_STREAM, 0)};
    if (server_fd < 0)
    {
        std::cerr << "Failed to create server socket\n";
        return EXIT_FAILURE;
    }
    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        std::cerr << "failed to set options for server socket \n";
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(6379);

    if (bind(server_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
    {
        std::cerr << "Failed to bind to port 6379\n";
        return EXIT_FAILURE;
    }

    int connection_backlog = 5;

    if (listen(server_fd, connection_backlog) != 0)
    {
        std::cerr << "listen failed\n";
        return EXIT_FAILURE;
    }

    struct sockaddr_in client_addr{};
    int client_addr_len = sizeof(client_addr);

    std::cout << "Waiting for a client to connect...\n";

    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
    if (client_fd < 0)
    {
        std::cerr << "client connection failed\n";
        return EXIT_FAILURE;
    }

    std::cout << "client connected successfuly" << '\n';

    char msg[128]{};
    read(client_fd, msg, 128 - 1);

    std::cout << "client say : " << msg << '\n';

    std::string response = "world";
    send(client_fd, response.c_str(), response.size(), 0);

    std::cout
        << "fin\n";

    close(server_fd);

    return EXIT_SUCCESS;
}