#ifndef CURL_H
#define CURL_H

#include "HttpResponse.h"

#include <sstream>
#include <stdexcept>
#include <string>


class cURL {
	void *curl;

	class WriteHandler;

public:
	struct Exception;

	cURL();
	~cURL() noexcept;

	HttpResponse get(const std::string &url);
	static std::string urlEncode(const std::string &);
};

class cURL::WriteHandler {
	std::stringstream ss;

	size_t write(void *buf, size_t size);
public:
	static size_t handler(void *buffer, size_t size, size_t nmemb, void *userdata);

	std::string getContent();
};

struct cURL::Exception : public std::runtime_error {
	Exception(const char *msg);
};




#endif
