#pragma once
#include <iostream>
#include <format>
#include <vector>

#include "ascii_colors.h"
#include "string_extensions.hpp"

#define CURL_STATICLIB
#include <curl/curl.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "normaliz.lib")
#pragma comment(lib, "libcurl2.lib")

namespace mincurl {
	struct Header {
		std::string name;
		std::string value;

		inline std::string Raw() const {
			return std::format("{}: {}", name, value);
		}
	};

	typedef std::vector<Header> HeaderList;


	bool GetURLString(const std::string* response, const std::string url, const HeaderList headers = HeaderList());

	bool PostData(const std::string* response, const std::string url, const std::string& jsonData, const HeaderList headers = HeaderList());

	std::string GetMediafireDirectDownload(std::string& html);

	int DownloadFileFromURL(std::vector<uint8_t>& out, const char* url);

	// private functions
	namespace {
		void SetHeaders(CURL* curl, const HeaderList& headers) {
			if (headers.size() > 0) {
				curl_slist* slist = NULL;
				for (int i = 0; i < headers.size(); i++) {
					slist = curl_slist_append(slist, headers[i].Raw().c_str());
				}
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
			}
		}
	}
}