#include "config.h"

#include "HttpResponse.h"
#include "cURL.h"
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
	string nextPageToken;
	do {
		std::string str = std::string("https://www.googleapis.com/youtube/v3/playlistItems?part=id,snippet&maxResults=50&playlistId=") 
			+ cURL::urlEncode(query_string) + "&key=" + YOUTUBE_DATA_API_KEY;
		if(nextPageToken != "") {
			str += "&pageToken=" + nextPageToken;
		}

		nextPageToken = "";

#ifdef DEBUG
		cout << "url: " << str << endl;
#endif
		auto response = cURL().get(str);
		if(response.code != 200) {
			cerr << "HTTP status code: " << response.code << endl;
			return 1;
		}

		auto data = json::parse(response.body);
		auto items = data["items"];
		for(auto it = items.begin(); it != items.end(); ++it) {
			int position = it.value()["snippet"]["position"].get<int>();

			string videoId = "null";
			try {
				videoId = it.value()["snippet"]["resourceId"]["videoId"].get<string>();
			} catch(...) {}

			string title = "null";
			try {
				title = it.value()["snippet"]["title"].get<string>();
			} catch(...) {}

			cout << position << ' ' << videoId << ' ' << title << endl;
		}

		if(data["nextPageToken"].type() != json::value_t::null) {
			nextPageToken = data["nextPageToken"];
#ifdef DEBUG
			cout << "next page token: " << nextPageToken << endl;
#endif
		}
	} while(nextPageToken != "");

	return 0;
}
