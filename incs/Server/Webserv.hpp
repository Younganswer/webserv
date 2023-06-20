#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "../Config/Config.hpp"
# include "PhysicalServerManager.hpp"
# include <iostream>

class Webserv {

	private:
		static const int	MAX_SERVERS = 8;

	private:
		PhysicalServerManager	_physical_server_manager;

	public:
		Webserv(void);
		~Webserv(void);
		Webserv	&operator=(const Webserv &rhs);

	private:
		bool	_build(const Config &config) throw(std::exception);

	public:
		bool	run(const Config &config) throw(std::exception);

	public:
		class TooManyServersException: public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class FailToBuildException: public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class FailToRunException: public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

// Todo:
// std::ostream	&operator<<(std::ostream &os, const Webserv &webserv);

#endif