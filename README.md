# Counter Application with Login Interface

This is an Android application that includes a login interface, the username and password are sent to the server with a c++ client application, which verifies the user's credentials through a C++ server. After successful login, the user is directed to a counter interface where they can increment or decrement a value.

## Features
- **Login Screen**: Users enter their username and password, which are sent to a C++ server for verification.
- **Counter Screen**: Once logged in, users can increase or decrease the counter.

## Technologies Used
- **Android (Java/Kotlin)**: Main application code.
- **JNI (Java Native Interface)**: Integration between Java/Kotlin and C++.
- **C++**: Server-side code to handle login requests.
- **Sockets**: TCP socket communication between the Android app and the server.

## Setup Instructions

### Prerequisites
- **Android Studio**: To run the Android app.
- **C++ Development Environment**: To compile and run the C++ server. This could be on Windows or Linux.

### Steps to Run the App

1. **Clone the Repository**:
    ```bash
    git clone [https://github.com/yourusername/counter-login-app.git](https://github.com/AbdoAli003/ubiquitous-broccoli.git)
    ```

2. **Open the Project in Android Studio**:
    - Open Android Studio.
    - Click on "Open an existing Android project" and select the cloned project.

3. **Build and Run the Android App**:
    - Connect your Android device or start an emulator.
    - Click "Run" in Android Studio to build and install the app.

4. **Set Up the C++ Server** (Only for Windows):
    - Navigate to the `server` folder.
    - Compile the C++ code using a suitable C++ compiler (e.g., g++, clang, or MSVC).
    - Run the server by executing the compiled binary.

    Example:
    ```bash
    g++ server.cpp -o server -lws2_32
    ./server
    ```

5. **Login and Use the Counter**:
    - Open the app on your Android device.
    - Enter your username and password.
    - Upon successful login, you will be directed to the counter screen.

## Project Structure
- `android-app`: Contains the Android Studio project for the app.
- `server`: Contains the C++ code for the login server.

## Future Improvements
- Add user registration.
- Add password hashing for improved security.
- Implement a more sophisticated UI for the counter.

