#include "Commands.hpp"

void	doCommand(const int & fd, const std::string & command, const std::vector<std::string> & params)
{
	if (command == "ping")
		ping(fd, params);
	else if (command == "pong")
		pong(fd, params);
}

void	ping(const int & fd,
const std::vector<std::string> & params){
	std::cout << "do command ping !" << std::endl;
}

void	pong(const int & fd,
const std::vector<std::string> & params){
	std::cout << "do command pong !" << std::endl;
}