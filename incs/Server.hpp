#ifndef SERVER_HPP
# define SERVER_HPP

#include "Irc.hpp"

class Server{
  private:
    int _socketFd;
    int _pollFd;
    
    int _port;
    int _max;
    std::string _name;
    std::string _password;
    std::string _msg;
    std::vector<std::string> _cmd
    pollfd  _pollfds[3];

    void  initSocket(void);
  
  public:
    Server(const int & port, const std::string & password);
    ~Server();
    void  service(void);
    void  printInfo(void);
    void  sendToClient(const int & fd, const std::string &msg);
    //Client
    //CHhannel
};


#endif