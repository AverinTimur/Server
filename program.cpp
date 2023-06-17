#include "headers.h"
#include "server.cpp"

Server server;

void end(int signum)
{
    server.stop();
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
    server.start(host, port);
    signal(SIGINT, end);

    return 0;
}