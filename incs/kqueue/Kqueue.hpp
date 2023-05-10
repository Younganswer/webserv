#ifndef KQUEUE_HPP
# define KQUEUE_HPP

# include <exception>
# include <sys/event.h>

class Kqueue {
	private:
		static const int	MAX_EVENTS = 16;

	private:
		int				_fd;
		struct kevent	_ev_set[2];
		struct kevent	_ev_list[MAX_EVENTS];

	// Constructor & Destructor
	public:
		Kqueue(void);
		Kqueue(const Kqueue &ref);
		~Kqueue(void);
		Kqueue	&operator=(const Kqueue &rhs);

	// Util
	public:
		int		length(void);
		int		getEventFd(int idx) const;
		void	*getEventData(int idx) const;
		bool	addEvent(int fd, void *udata);
		bool	deleteEvent(int fd, void *udata);
	
	// Exception
	public:
		class FailToCreateException: public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class FailToControlException: public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class FailToGetEventException: public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class TimeoutException: public std::exception {
			public:
				virtual const char *what() const throw();
		};
};

#endif