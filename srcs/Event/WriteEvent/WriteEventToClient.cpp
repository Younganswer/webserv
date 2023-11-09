#include "../../../incs/Event/WriteEvent/WriteEventToClient.hpp"


WriteEventToClient::WriteEventToClient(ft::shared_ptr<Channel> channel,
ft::shared_ptr<VirtualServerManager> virtualServerManager,
ft::shared_ptr<Client> client):
WriteEvent(new WriteEventToClientHandler()), SingleStreamable(channel),
_virtualServerManager(virtualServerManager), _client(client) {
	client->addClientEventQueueState(Write);
}


WriteEventToClient::~WriteEventToClient(void) {}
void	WriteEventToClient::callEventHandler(void) {
	this->_event_handler->handleEvent(*this);
}
void	WriteEventToClient::onboardQueue(void){
	Event *event = this;

	try {
		this->getChannel().get()->setNonBlocking();
		this->_onboardWrite(event, this->getFd());
	}
	catch (KqueueError &e) {
		throw (KqueueError());
	}
	catch (std::exception &e) {
		throw ;
	}
}

void	WriteEventToClient::offboardQueue(void){

	try {
		this->_client->removeClientEventQueueState(Write);
		this->_offboardWrite(this, this->getFd());
		//Todo: check this
	}
	catch (...) {
		Logger::getInstance().error("Fail to offboard Write Event");
		throw ;
	}	
}

const ft::shared_ptr<VirtualServerManager>	
&WriteEventToClient::getVirtualServerManger(void) const { return (this->_virtualServerManager); }

e_client_event_queue_state WriteEventToClient::queryClientEventQueueState(void) {
	return (this->_client->queryClientEventQueueState());
}

ft::shared_ptr<Client> WriteEventToClient::getClient(void)  {
	return (this->_client);
}