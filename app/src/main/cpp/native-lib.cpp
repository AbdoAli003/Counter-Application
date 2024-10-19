#include <jni.h>
#include <string>
#include <unistd.h> // For close()
#include <arpa/inet.h> // For socket functions
#include <iostream>

using namespace std;

const char* SERVER_IP = "10.0.2.2"; // Change this to the actual server IP if needed
const int PORT = 8080;

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_diy_LoginPage_loginToServer(JNIEnv *env, jobject thiz, jstring jUsername,
                                             jstring jPassword) {
    const char *username = env->GetStringUTFChars(jUsername, nullptr);
    const char *password = env->GetStringUTFChars(jPassword, nullptr);

    int client_socket;
    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4
    if (client_socket < 0) {
        cerr << "Error creating client socket" << endl;
        return JNI_FALSE; // Return false on error
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr); // Convert IP address from text format to binary format

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Error connecting to server" << endl;
        close(client_socket); // Clean up
        return JNI_FALSE; // Return false on error
    }

    // Prepare the login credentials
    std::string login_request = "username=" + std::string(username) + "&password=" + std::string(password);

    // Send login credentials to the server
    if (send(client_socket, login_request.c_str(), login_request.length(), 0) < 0) {
        cerr << "Error sending login data" << endl;
        close(client_socket); // Clean up
        return JNI_FALSE; // Return false on error
    }

    // Receive response from the server
    char buffer[1024] = {0};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        cerr << "Error receiving response from server" << endl;
        close(client_socket); // Clean up
        return JNI_FALSE; // Return false on error
    }

    std::string response(buffer, bytes_received);
    close(client_socket); // Clean up

    // Release string resources
    env->ReleaseStringUTFChars(jUsername, username);
    env->ReleaseStringUTFChars(jPassword, password);

    // Check response for login status
    if (response.find("Login Successful") != std::string::npos) {
        return JNI_TRUE; // Return true on success
    } else {
        return JNI_FALSE; // Return false on failure
    }
}