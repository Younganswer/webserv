#include <Pattern/RedirectionProcessor.hpp>

// To do: implement RedirectionProcessor
RedirectionProcessor::RedirectionProcessor(void) {
}
RedirectionProcessor::~RedirectionProcessor(void) {
}

e_pattern_Process_result RedirectionProcessor::process(ft::shared_ptr
    <VirtualServerManager> virtualServerManager,
    ft::shared_ptr<Client> client,
    ft::shared_ptr<Channel> channel) {
        //Todo : implement
        (void)channel;
    try {   
        //basic Handle All RequireMent
        _commandBuildHeaderTo(
            ft::shared_ptr<HttpResponseBuilder>(new RedirectionResponseBuilder(client, virtualServerManager)),
            client
        );
        client->getResponse()->setResponseSize(NormalSize, HttpResponse::AccessKey());
    }
    catch (std::exception& e) {
        //log error
        throw ;
    }
    return SUCCESS;
}

//Todo: implement
e_pattern_Process_result RedirectionProcessor::querryCanSending(ft::shared_ptr
    <VirtualServerManager> virtualServerManager,
    ft::shared_ptr<Client> client) {
    (void)virtualServerManager;
    (void)client;
    return SUCCESS;
}