#include <Http/Response/RedirectionResponseBuilder.hpp>
#include <FileManager/FileManager/FileManager.hpp>

RedirectionResponseBuilder::RedirectionResponseBuilder(ft::shared_ptr<Client> client, ft::shared_ptr<VirtualServerManager> vsm) :
HttpResponseBuilder(client), _vsm(vsm) {}

RedirectionResponseBuilder::~RedirectionResponseBuilder(void) {}

void RedirectionResponseBuilder::buildResponseHeader(std::vector<char> &buffer) {
    std::string uri = this->getClient()->getRequest()->getUri();
    std::string locationHeader;

    //To do: 일단 똄질로 해결 
    if (uri[uri.size() - 1] != '/') {
        _setStatusCode(MOVED_PERMANENTLY);
        locationHeader = "Location: " + this->getClient()->getRequest()->getUri() + "/";
    }
    else {
        ft::shared_ptr<ReturnElement> returnElement = RouterUtils::findRedirectUri(this->_vsm, this->getClient()->getRequest());
        if (returnElement.get() == NULL) {
            throw NotFoundException();
        }
        _setStatusCode((HttpStatusCode)returnElement->getCode());
        locationHeader = "Location: " + returnElement->getUri();
    }
    _allocContentLength(ContentLength::e_content_length_header, 0);
    _buildDefaultResponseHeader(buffer);

    std::string header = locationHeader + "\r\n\r\n";
    buffer.insert(buffer.end(), header.begin(), header.end());
}