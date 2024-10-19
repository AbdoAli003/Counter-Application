#include <iostream>
#include <string>
#include <winsock2.h> // For Windows socket programming
#include <ws2tcpip.h> // For sockaddr_in
#include <thread> // For sleep_for
#include <chrono>

#pragma comment(lib, "ws2_32.lib") // Link with Ws2_32.lib

const int PORT = 8080; // listening on port 8080
const std::string VALID_USERNAME = "Abbas";
const std::string VALID_PASSWORD = "timer555";

void handle_request(SOCKET client_socket) { // handle request from the client
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        std::string request(buffer, bytes_received);

        // Extract username and password from the request
        std::string username = request.substr(request.find("username=") + 9, request.find("&") - 9);
        std::string password = request.substr(request.find("password=") + 9);
        std::cout << "Received request for username: " << username << std::endl; // show the username of the client on the server
        std::string response;
        if (username == VALID_USERNAME && password == VALID_PASSWORD) {
            response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Login Successful</h1></body></html>";
        } else {
            response = "HTTP/1.1 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Login Failed</h1></body></html>";
        }
         // sending back the response to the client
        send(client_socket, response.c_str(), response.length(), 0);
    }

    closesocket(client_socket);
}

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr; // storing address information
    int client_len = sizeof(client_addr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error initializing Winsock: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Error binding socket: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        std::cerr << "Error listening on socket: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << "..." << std::endl;

    while (true) {
        // Accept incoming connections
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "Error accepting connection: " << WSAGetLastError() << std::endl;
            continue;
        }

        // Handle the request
        handle_request(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
