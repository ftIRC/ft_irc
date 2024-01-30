#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <vector>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <string>
# include <unistd.h>
# include <exception>
# include <poll.h>
# include <fcntl.h>
# include "Server.hpp"
# define POLLFDS_CAPACITY 3

void  errmsg(std::string msg);

#endif