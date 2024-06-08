#include "Channel.hpp"
#include "Server.hpp"

void	createChannel(string av[2], Channel &ch, string username, int fd){
	if (av[0][0] != '#'){
		string toSend = string(ERR) + "Invalid channel name\n" + RESET;
		send(fd, toSend.c_str(), toSend.size(), 0);
	}
	else{
		av[0] = &av[0][1];
		cout << av[0] << "----\n";
		if (ch.hasChannel(av[0])){
			if (ch.getInviteOnly(av[0])){
				if (!ch.isInvited(av[0], username)){
					string toSend = string(ERR) + "You are not invited to this channel\n" + RESET;
					send(fd, toSend.c_str(), toSend.size(), 0);
				}
				else
					ch.addUser(av[0], username, fd);
			}
			else if (ch.getUserLimit(av[0]) != -1 && ch.getUserList(av[0]).size() >= ch.getUserLimit(av[0])){
				string toSend = string(ERR) + "Channel is full\n" + RESET;
				send(fd, toSend.c_str(), toSend.size(), 0);
			}
			else if (ch.isKeyRequired(av[0])){
				if (av[1] != ch.getChannelKey(av[0])){
					string toSend = string(ERR) + "Invalid channel key\n" + RESET;
					send(fd, toSend.c_str(), toSend.size(), 0);
				}
				else
					ch.addUser(av[0], username, fd);
			}
			else
				ch.addUser(av[0], username, fd);
		}
		else{
			if (!ch.addChannel(av[0], username, fd)){
				string toSend = string(ERR) + "Channel already exists\n" + RESET;
				send(fd, toSend.c_str(), toSend.size(), 0);
			}
			else{
				string toSend = string(GREEN) + "Channel created\n" + RESET;
				send(fd, toSend.c_str(), toSend.size(), 0);
			}
		}
	}
}

