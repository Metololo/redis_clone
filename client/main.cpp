#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

int main()
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        std::cerr << "failed to create client socket\n";
        return EXIT_FAILURE;
    }

    struct sockaddr_in client_addr{};
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);
    client_addr.sin_port = htons(6379);
    int rv = connect(client_fd, (const struct sockaddr *)&client_addr, sizeof(client_addr));
    if (rv)
    {
        std::cerr << "failed to connect to server\n";
        return EXIT_FAILURE;
    }

    std::string msg = "hello";
    send(client_fd, msg.c_str(), msg.size(), 0);
    char response[128]{};
    recv(client_fd, response, 127, 0);

    std::cout << response << '\n';
    close(client_fd);

    return EXIT_SUCCESS;
}