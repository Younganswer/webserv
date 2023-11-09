#include "../../../incs/Event/ReadEvent/ReadEventFromClient.hpp"

ReadEventFromClient::ReadEventFromClient(ft::shared_ptr<Channel> channel, 
	ft::shared_ptr<VirtualServerManager> virtualServerManager):
	ReadEvent(new ReadEventFromClientHandler()),
	SingleStreamable(channel),
	_virtualServerManager(virtualServerManager),
	_client(new Client(Read))
	{}
ReadEventFromClient::~ReadEventFromClient(void) {}
void	ReadEventFromClient::callEventHandler(void) { 

	this->_event_handler->handleEvent(*this); 
	}
void	ReadEventFromClient::onboardQueue() {
	int			fd = this->getFd();
	Event		*event = this;
	

	try {
		this->getChannel()->setNonBlocking();
		this->_onboardRead(event, fd);
	} catch (KqueueError &e) {
		throw (KqueueError());
	}
	catch (std::exception &e) {
		throw ;
	}
}
void	ReadEventFromClient::offboardQueue() {

	try {
		this->_client->removeClientEventQueueState(Read);
		this->_offboardRead(this, this->getFd());
		//To do: check this
	} catch (KqueueError &e) {
		throw (KqueueError());
	}
	catch (std::exception &e) {
		throw ;
	}

}
bool ReadEventFromClient::canRead(void) const {
	if (_client->isQueueMax())
		return (false);
	return (true);
}
const ft::shared_ptr<VirtualServerManager>	&ReadEventFromClient::getVirtualServerManger(void) const { return (this->_virtualServerManager); }

void	ReadEventFromClient::addRequest(ft::shared_ptr<HttpRequest> request) {
	this->_client->addRequest(request);
}

e_client_event_queue_state ReadEventFromClient::queryClientEventQueueState(void) {
	return (this->_client->queryClientEventQueueState());
}

bool ReadEventFromClient::isRequestEmpty(void) {
	return (this->_client->isRequestEmpty());
}

bool ReadEventFromClient::isEventQueueTurnOn(e_client_event_queue_state state) {
	return (this->_client->isEventQueueStateTurnOn(state));
}

ft::shared_ptr<Client> ReadEventFromClient::getClient(void) {
	return (this->_client);
}

bool ReadEventFromClient::isClientDie(void) {
	return (this->_client->isClientDie());
}