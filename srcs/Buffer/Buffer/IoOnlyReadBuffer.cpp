#include "../../../incs/Buffer/Buffer/IoOnlyReadBuffer.hpp"
IoOnlyReadBuffer* IoOnlyReadBuffer::_instance = NULL;
IoOnlyReadBuffer::IoOnlyReadBuffer() : BaseBuffer(), IoReadable(), _head(ft::Optional<ft::shared_ptr<LargeNode> >()) {}
IoOnlyReadBuffer::~IoOnlyReadBuffer() {
}
IoOnlyReadBuffer& IoOnlyReadBuffer::getInstance() {
    if (_instance == NULL) {
        try {
        _instance = new IoOnlyReadBuffer();
        }
        catch (const std::bad_alloc& e) {
            throw ;
        }
        catch (const std::exception& e) {
            throw;
        }
    }
    return *_instance;
}

ssize_t IoOnlyReadBuffer::size(){
	// ft::Assert::_assert((!_head.has_value()),
	// "IoOnlyReadBuffer:: size Invarint Error");
    if (!_head.has_value()) throw std::runtime_error("IoOnlyReadBuffer:: size Invarint Error");
	return (*_head)->size();
}
void	IoOnlyReadBuffer::recycleInstance(){
	// ft::Assert::_assert((!_head.has_value()),
	// "IoOnlyReadBuffer:: recycleInstance Invarint Error");
	if (_head.has_value()) 
		(*_head)->reset(BaseNode::AccessKey());
}
void	IoOnlyReadBuffer::_allocate() {
    try {
        _head = ft::shared_ptr<LargeNode>(new LargeNode());
    }
    catch (...) {
        throw;
    }
}

ssize_t	IoOnlyReadBuffer::ioRead(int fd) {
    //if No alloc->alloc
    try {
        if (!_head.has_value()) _allocate();
    }
    catch (const std::exception& e) {
        throw;
    }
    catch (...) {
        throw;
    }
    return _head.value()->ioRead(fd);
}

IoOnlyReadBuffer::iterator IoOnlyReadBuffer::begin() const {
    return _head.value()->begin();
}

IoOnlyReadBuffer::iterator IoOnlyReadBuffer::end() const {
    return _head.value()->end();
}
