#include "headers.h"
#include "server.cpp"

Server server;

void end(int signum)
{
    server.Stop();
}
std::string request_handle(std::string request)
{
    std::ifstream file("Files/RESPONSE.txt");
    file.seekg(0, file.end);
    int size = file.tellg();
    file.seekg(0);

    std::string response(size, ' ');
    file.read(&response[0], size);
    file.close();
    return response;
}

int main(int argc, char *argv[])
{
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

    // Start server
    server.Start(host, port, request_handle);
    signal(SIGINT, end);

    return 0;
}