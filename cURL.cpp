#include "cURL.h"

#include <curl/curl.h>
#include <sstream>
#include <iomanip>

cURL::cURL() :curl(curl_easy_init()) {}
cURL::~cURL() noexcept {
	if(curl) curl_easy_cleanup(reinterpret_cast<CURL*>(curl));
}

HttpResponse cURL::get(const std::string &url) {
	CURLcode res;
	WriteHandler handler;
	CURL *ch = curl;
	curl_easy_setopt(ch, CURLOPT_URL, url.c_str());
	curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1l);
	curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, WriteHandler::handler);
	curl_easy_setopt(ch, CURLOPT_WRITEDATA, &handler);

	res = curl_easy_perform(ch);
	if(res != CURLE_OK) {
		throw Exception(curl_easy_strerror(res));
	}
	long response_code = 0;
	curl_easy_getinfo(ch, CURLINFO_RESPONSE_CODE, &response_code);
	return HttpResponse(response_code, handler.getContent());
}

std::string cURL::urlEncode(const std::string &value) {
	using namespace std;
	ostringstream escaped;
	escaped.fill('0');
	escaped << hex;

	for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
		string::value_type c = (*i);

		// Keep alphanumeric and other accepted characters intact
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			escaped << c;
			continue;
		}

		// Any other characters are percent-encoded
		escaped << uppercase;
		escaped << '%' << setw(2) << int((unsigned char) c);
		escaped << nouppercase;
	}

	return escaped.str();
}

size_t cURL::WriteHandler::write(void *buf, size_t size) {
	ss.write(reinterpret_cast<char *>(buf), size);
	return size;
}

size_t cURL::WriteHandler::handler(void *buffer, size_t size, size_t nmemb, void *userdata) {
	return static_cast<WriteHandler *>(userdata)->write(buffer, size*nmemb);
}

std::string cURL::WriteHandler::getContent() {
	return ss.str();
}

cURL::Exception::Exception(const char *msg) :std::runtime_error(msg) {}
