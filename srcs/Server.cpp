#include "Server.hpp"

Server::Server(const int & port, const std::string & password)
:_port(port), _password(password) {
  std::cout << "Constructor Server" << std::endl;
  initSocket();
  std::cout << "socketFd : " << _socketFd << "\n";
  std::cout << "port : " << port << "\n";
  std::cout << "password : " << password << std::endl;#include "Server.hpp"

Server::Server(const int & port, const std::string & password)
:_port(port), _password(password) {
  std::cout << "Constructor Server" << std::endl;
  initSocket();
  std::cout << "socketFd : " << _socketFd << "\n";
  std::cout << "port : " << port << "\n";
  std::cout << "password : " << password << std::endl;
}
Server::~Server(){
  close(_socketFd);
  std::cout << "Destructor Server" << std::endl;
}

void  Server::initSocket(void) {
  this->_socketFd = socket(AF_INET, SOCK_STREAM, 0);
  
  if (this->_socketFd == -1)
    throw std::runtime_error("Error: socket");
  if (fcntl(this->_socketFd, F_SETFL, O_NONBLOCK) == -1)
    throw std::runtime_error("Error: fcntl");  
  std::cout << "Server's socketfd : " << this->_socketFd << std::endl;

  struct sockaddr_in  serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(this->_port);
  
  if (bind(this->_socketFd, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
    throw std::runtime_error("Error: bind");
  if (listen(this->_socketFd, 100) == -1)
    throw std::runtime_error("Error: listen");
}


void Server::service(void) {
    std::cout << "- service start -" << std::endl;
    
    struct pollfd pollFds[POLLFDS_CAPACITY];
    for (int i = 0; i < POLLFDS_CAPACITY; i++) {
        pollFds[i].fd = -1;
    }

    // 배열의 첫 번째에 서버 소켓 등록
    pollFds[0].fd = this->_socketFd;
    pollFds[0].events = POLLIN;
    int max_i = 0;

    while (1) {
        if (poll(pollFds, max_i + 1, 1000) == -1)
            continue;
        // when event occurs to server socket, accept!
        if (pollFds[0].revents & POLLIN) {
            struct sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientSocket = accept(this->_socketFd, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrLen);
            std::cout << "client addr len : " << clientAddrLen << std::endl;
            if (clientSocket == -1) {
                std::cerr << "client socket fail" << std::endl;
                continue;
            }

            std::cout << "new client: " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

            // add new client to array
            int flag = 0;
            for (int i = 1; i < POLLFDS_CAPACITY; i++) {
                if (pollFds[i].fd == -1) {
                    pollFds[i].fd = clientSocket;
                    pollFds[i].events = POLLIN;
                    if (i > max_i) {
                        max_i = i;
                    }
                    break;
                } else {
                  flag++;
                }
            }
            if (flag == POLLFDS_CAPACITY - 1) {
              std::cout << "over the capacity" << std::endl;
              continue;
            }
            pollFds[0].revents = 0;
        }
        // when event occurs to client socket, receive data
        for (int i = 1; i <= max_i; i++) {
            if (pollFds[i].revents & POLLIN) {
                char buffer[1024];
                ssize_t bytesRead = recv(pollFds[i].fd, buffer, sizeof(buffer), 0);
                // std::cout << "buffer : [" << std::string(buffer, bytesRead) << "]" << std::endl;
                std::cout << bytesRead << std::endl;
                if (bytesRead <= 0) {
                    std::cout << "client die: " << pollFds[i].fd << std::endl;
                    close(pollFds[i].fd);
                    pollFds[i].fd = -1;
                } else {
                    buffer[bytesRead] = '\0';
                    std::cout << "client msg(" << pollFds[i].fd << "): " << buffer << std::endl;
                }
                pollFds[i].revents = 0;
            }

        }
        // std::cout << "Loop end" << std::endl;
    }
}

void  Server::printInfo(void){
  std::cout << "Constructor Server" << std::endl;
  initSocket();
  std::cout << "socketFd : " << _socketFd << "\n";
  std::cout << "port : " << _port << "\n";
  std::cout << "password : " << _password << std::endl;
}

void  Server::sendToClient(const int & fd, const std::string &msg){
  
}
}
Server::~Server(){
  close(_socketFd);
  std::cout << "Destructor Server" << std::endl;
}

void  Server::initSocket(void) {
  this->_socketFd = socket(AF_INET, SOCK_STREAM, 0);
  
  if (this->_socketFd == -1)
    throw std::runtime_error("Error: socket");
  if (fcntl(this->_socketFd, F_SETFL, O_NONBLOCK) == -1)
    throw std::runtime_error("Error: fcntl");  
  std::cout << "Server's socketfd : " << this->_socketFd << std::endl;

  struct sockaddr_in  serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(this->_port);
  
  if (bind(this->_socketFd, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
    throw std::runtime_error("Error: bind");
  if (listen(this->_socketFd, 100) == -1)
    throw std::runtime_error("Error: listen");
}


void Server::service(void) {
    std::cout << "- service start -" << std::endl;
    
    struct pollfd pollFds[3];
    for (int i = 0; i < 3; i++) {
        pollFds[i].fd = -1;
    }

    // 배열의 첫 번째에 서버 소켓 등록
    pollFds[0].fd = this->_socketFd;
    pollFds[0].events = POLLIN;
    int max_i = 0;

    while (1) {
        if (poll(pollFds, max_i + 1, 1000) == -1)
            continue;
        // when event occurs to server socket, accept!
        if (pollFds[0].revents & POLLIN) {
            struct sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientSocket = accept(this->_socketFd, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrLen);
            std::cout << "client addr len : " << clientAddrLen << std::endl;
            if (clientSocket == -1) {
                std::cerr << "client socket fail" << std::endl;
                continue;
            }

            std::cout << "new clinet: " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

            // add new client to array
            for (int i = 1; i < 3; i++) {
                if (pollFds[i].fd == -1) {
                    pollFds[i].fd = clientSocket;
                    pollFds[i].events = POLLIN;
                    if (i > max_i) {
                        max_i = i;
                    }
                    break;
                } else {
                  std::cout << "over the capacity" << std::endl;
                }
                
            }
            pollFds[0].revents = 0;
        }
        // when event occurs to client socket, receive data
        for (int i = 1; i <= max_i; i++) {
            if (pollFds[i].revents & POLLIN) {
                char buffer[1024];
                ssize_t bytesRead = recv(pollFds[i].fd, buffer, sizeof(buffer), 0);
                // std::cout << "buffer : [" << std::string(buffer, bytesRead) << "]" << std::endl;
                if (bytesRead <= 0) {
                    std::cout << "client die: " << pollFds[i].fd << std::endl;
                    close(pollFds[i].fd);
                    pollFds[i].fd = -1;
                } else {
                    buffer[bytesRead] = '\0';
                    std::cout << "client msg(" << pollFds[i].fd << "): " << std::string(buffer, bytesRead) << std::endl;
                }
                pollFds[i].revents = 0;
            }

        }
        // std::cout << "Loop end" << std::endl;
    }
}

void  Server::printInfo(void){
  std::cout << "Constructor Server" << std::endl;
  initSocket();
  std::cout << "socketFd : " << _socketFd << "\n";
  std::cout << "port : " << _port << "\n";
  std::cout << "password : " << _password << std::endl;
}

void  Server::sendToClient(const int & fd, const std::string &msg){
  
}