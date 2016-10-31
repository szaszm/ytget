#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>

struct HttpResponse {
	int code;
	std::string body;

	HttpResponse();
	HttpResponse(int code, std::string body);
	HttpResponse(std::string body);
	HttpResponse(int code);
};

#endif
