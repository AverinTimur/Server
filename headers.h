#pragma once


#include <sys/socket.h> // For sockets and inet
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream> // For files
#include <fstream>

#include <functional> // Other
#include <stdlib.h>
#include <csignal>
#include <string> 


#define DEFAULT_PORT 8000
#define DEFAULT_ADDRESS "127.0.0.1"