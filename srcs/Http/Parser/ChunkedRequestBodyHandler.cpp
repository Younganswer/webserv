#include "../../../incs/Http/Parser/ChunkedRequestBodyHandler.hpp"

ChunkedRequestBodyHandler::ChunkedRequestBodyHandler(ft::shared_ptr<HttpRequest> req)
: RequestBodyHandler(0, req)
{
}

ChunkedRequestBodyHandler::~ChunkedRequestBodyHandler(void)
{}

bool ChunkedRequestBodyHandler::handleBody(std::vector<char> &buffer) {
	// find chunk size
	
	std::vector<char>::iterator find = std::search(buffer.begin(), buffer.end(), _crlfPattern.begin(), _crlfPattern.end());
	while (find != buffer.end()) {
		size_t chunkSize = _hexToDec(std::string(buffer.begin(), find));
		buffer.erase(buffer.begin(), find + _crlfPattern.size());
		if (chunkSize == 0) {
			buffer.erase(buffer.begin(), buffer.begin() + _crlfPattern.size());
			return true;
		}

		//find chunk data
		find = std::search(buffer.begin(), buffer.end(), _crlfPattern.begin(), _crlfPattern.end());
		if (find != buffer.end()) {
			size_t chunkDataSize = find - buffer.begin();
			if (chunkDataSize != chunkSize)
				throw ChunkDataSizeNotMatchException();
			ft::shared_ptr<IoReadAndWriteBuffer> body = this->_request->getBody();
			body->append(buffer.begin(), find);
			buffer.erase(buffer.begin(), find + _crlfPattern.size());
		}
		else 
			return false;
		//find chunk size
		find = std::search(buffer.begin(), buffer.end(), _crlfPattern.begin(), _crlfPattern.end());
	}
	return false;
}

void ChunkedRequestBodyHandler::_writeInMemory(std::vector<char> &writeBuffer) {
	this->_request->insertBody(writeBuffer);
}

int ChunkedRequestBodyHandler::_hexToDec(const std::string& hexStr) {
	int decValue;
	std::istringstream(hexStr) >> std::hex >> decValue;
	return decValue;
}

const char * ChunkedRequestBodyHandler::ChunkDataSizeNotMatchException::what() const throw()
{
	return "Chunk data size not match";
}