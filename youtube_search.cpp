#include "config.h"

#include "cURL.h"
#include "HttpResponse.h"
#include "json.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
	using namespace std;
	using json = nlohmann::json;

	if(argc < 2) {
		cerr << "Too few arguments." << endl;
		return 1;
	}

	const char *query_string = argv[1];
	auto response = cURL().get(std::string("https://www.googleapis.com/youtube/v3/search?part=snippet&maxResults=20&q=") 
			+ cURL::urlEncode(query_string) + "&type=video&key=" + YOUTUBE_DATA_API_KEY);
	if(response.code != 200) {
		cerr << "HTTP status code: " << response.code << endl;
		return 1;
	}

	auto data = json::parse(response.body);
	data = data["items"];
	for(auto it = data.begin(); it != data.end(); ++it) {
		cout << it.value()["id"]["videoId"].get<std::string>() << " " << it.value()["snippet"]["title"].get<std::string>() << '\n';
	}

	return 0;
}
