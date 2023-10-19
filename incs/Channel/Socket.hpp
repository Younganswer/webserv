#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <netinet/in.h>
# include <iostream>
# include <string>
# include "Channel.hpp"

class Socket : public Channel {
	public:
		static const int	MAX_SIZE = 20;

	private:
		int					_enable;
		struct sockaddr_in	_addr;
	
	public:
		Socket(void);
		//fix daeguleee
		Socket(int fd);
		virtual ~Socket(void);
	private:
		Socket(const Socket &ref);
		Socket	&operator=(const Socket &rhs);
	private:
		virtual void	inJectChannelFd(int fd);
	public:
		bool	build(const int port, const std::string &ip);
		bool	run(void);
	
	private:
		static uint32_t	stringToNetworkByteOrder(const std::string &ip);

	public:
		class FailToCreateException: public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class FailToBindException: public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class FailToListenException: public std::exception {
			public:
				virtual const char *what() const throw();
		};

	friend std::ostream	&operator<<(std::ostream &os, const Socket &socket);
};

#endif