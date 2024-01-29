#include "Irc.hpp"


// ./ircserv <port> <password>

int main(int ac, char **av){
  int port;
  char *password, *endptr;

  // std::cout << "process start" << std::endl;
  if (ac != 3){
    errmsg("ac");
  }
  port = strtol(av[1], &endptr, 10);
  if (*endptr || (port < 0 || port > 65535)) {
    errmsg("invalid port");
  }
  // How to set password rule?
  password = av[2];
  try{
    Server  server(port, password);
    server.service();
  } catch (const std::exception & e){
    std::cerr << e.what() << std::endl;
  }
  std::cout << "process end" << std::endl;
  return 0; 
}
