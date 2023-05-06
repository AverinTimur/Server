#include <sys/socket.h> // For sockets and inet
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream> // For files
#include <fstream>

#include <string> // Other


int main()
{
    // socket creating
    int descriptor = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[1000];

    // reading from file
    std::ifstream file("Files/RESPONSE.txt");
    file.seekg(0, file.end);
    int size = file.tellg();
    file.seekg(0);
    
    std::string header(size, ' ');
    file.read(&header[0], size);
    file.close();

    // address creating it's binding and listening start
    struct sockaddr_in address;
    int address_len = sizeof(address);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    bind(descriptor, (struct sockaddr*)&address, address_len);
    listen(descriptor, 3);

    // give responses
    while(true)
    {
        int new_socket = accept(descriptor, (struct sockaddr*)&address, (socklen_t*)&address_len);
        read(new_socket, buffer, sizeof(buffer));
        send(new_socket, &header[0], header.size(), 0);
    }
    
    shutdown(descriptor, SHUT_RDWR);
    return 0;
}