#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(41317);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed!" << std::endl;
        return -1;
    }

    bool running = true;

    while (running) {
        char buffer[1024] = {0};
        recv(sock, buffer, sizeof(buffer), 0);

        if (strncmp(buffer, "SAY", 3) == 0) {
            char input[1024] = {0};
            std::cout << "Please enter your input~!" << std::endl;
            std::cin.getline(input, 1024);
            send(sock, input, strlen(input), 0);
        } else if (strncmp(buffer, "HELLO", 5) == 0) {
            std::cout << "Server has welcomed us!" << std::endl;
        } else if (strncmp(buffer, "COM ", 4) == 0) {
            char* trimmed = buffer + 4;
            std::cout << trimmed << std::endl;
        } else if (strncmp(buffer, "BYE", 3) == 0) {
            send(sock, "Bye!", 4, 0);
            running = false;
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
