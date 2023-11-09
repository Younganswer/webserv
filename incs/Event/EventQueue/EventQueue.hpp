#ifndef EVENTQUEUE_HPP
# define EVENTQUEUE_HPP

# include <exception>
# include <sys/event.h>
# include "../EventBase/Event.hpp"
# include <vector>



class EventQueue {
	public:
		enum EventSetIndex {
		READ_SET,
		WRITE_SET
	};
	private:
		static const int	MAX_EVENTS = 1024;
		static EventQueue	*_instance;

	private:
		int				_fd;
		struct kevent	_ev_set;
		struct kevent	_ev_list[MAX_EVENTS];

	private:
		EventQueue(void);

	public:
		~EventQueue(void);

	public:
		static EventQueue	&getInstance(void);
		void deleteInstance(void);

	public:
		int		pullEvents(void);
		bool	pushEvent(Event *event);
		bool	popEvent(Event *event);

	public:
		int				getEventFd(int idx) const;
		int				getEventQueueFd(void) const;
		Event			*getEventData(int idx) const;
		struct kevent	*getEventList(void);
		struct kevent 	*getEventSet(void);
		struct kevent	*getEventSetElementPtr();

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