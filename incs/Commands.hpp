#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <string>
# include <vector>

class Server;
class Client;

void	doCommand(const int & fd, const std::string & command, const std::vector<std::string> & params);
void	ping(const int & fd,
const std::vector<std::string> & params);
void	pong(const int & fd,
const std::vector<std::string> & params);



#endif