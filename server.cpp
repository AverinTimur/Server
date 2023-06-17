#include "headers.h"

class Server
{
    int descriptor = socket(AF_INET, SOCK_STREAM, 0);

    public:
        void stop()
        {
            std::cout << "Server stoped" << std::endl;
            shutdown(descriptor, SHUT_RDWR);
            descriptor = -1;
        }
        void start(char* host, int port)
        {
            // socket creating
            std::string buffer;
    
            // reading from file
            std::ifstream file("Files/RESPONSE.txt");
            file.seekg(0, file.end);
            int size = file.tellg();
            file.seekg(0);
    
            std::string request(size, ' ');
            file.read(&request[0], size);
            file.close();
    
            // address creating it's binding and listening start
            sockaddr_in address;
            int address_len = sizeof(address);
            address.sin_family = AF_INET;
            address.sin_port = htons(port);
            address.sin_addr.s_addr = inet_addr(host);
    
            bind(descriptor, (struct sockaddr*)&address, address_len);
            listen(descriptor, 3);
            std::cout << "Server start at address " << host << " and port " << port << std::endl;
            std::cout << "Press CTRL+C to stop server" << std::endl;
    
            // give responses
            while(descriptor >= 0)
            {
                int new_socket = accept(descriptor, (struct sockaddr*)&address, (socklen_t*)&address_len);
                read(new_socket, buffer.data(), buffer.size());
                send(new_socket, &request[0], request.size(), 0);
            }
        }
};



