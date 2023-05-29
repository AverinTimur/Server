#include "headers.h"

#define DEFAULT_PORT 8080
#define DEFAULT_ADDRESS "127.0.0.1"

int descriptor = socket(AF_INET, SOCK_STREAM, 0);

void end(int signum)
{
    std::cout << "Server stoped" << std::endl;
    shutdown(descriptor, SHUT_RDWR);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    // socket creating
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
    address.sin_family = AF_INET;

    // parse address and port data from command line
    bool is_port_set = false;
    bool is_address_set = false;
    int port;
    char *host;
    for(int i = 1; i < argc-1; i++)
    {
        if(argv[i] == std::string("--port"))
        {
            port = std::atoi(argv[i+1]);
            is_port_set = true;
        }
        else if(argv[i] == std::string("--address"))
        {
            host = argv[i+1];
            is_address_set = true;
        }
    }
    if(!is_port_set)
    {
        port = DEFAULT_PORT;
    }
    if(!is_address_set)
    {
        host = DEFAULT_ADDRESS;
    }
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(host);


    bind(descriptor, (struct sockaddr*)&address, address_len);
    listen(descriptor, 3);
    std::cout << "Server start at address " << host << " and port " << port << std::endl;
    std::cout << "Press CTRL+C to stop server" << std::endl;
    signal(SIGINT, end);

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

