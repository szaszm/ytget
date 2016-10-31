#include "HttpResponse.h"
#include <string>


HttpResponse::HttpResponse() {}

HttpResponse::HttpResponse(int code, std::string body) :code(code), body(body) {}

HttpResponse::HttpResponse(std::string body) :code(200), body(body) {}

HttpResponse::HttpResponse(int code) :code(code) {}
