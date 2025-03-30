#include "mincurl.h"

// callback function to write data to a std::vector<uint8_t>
size_t WriteCallbackVec(void* contents, size_t size, size_t nmemb, void* userp) {
	auto* vec = static_cast<std::vector<uint8_t>*>(userp);
	uint8_t* data = static_cast<uint8_t*>(contents);
	size_t totalSize = size * nmemb;

	// append to end of vector data
	vec->insert(vec->end(), data, data + totalSize);

	return totalSize;
}

size_t WriteCallbackStr(void* contents, size_t size, size_t nmemb, void* userp) {
	reinterpret_cast<std::string*>(userp)->append(reinterpret_cast<char*>(contents), size * nmemb);
	return size * nmemb;
}


bool mincurl::GetURLString(const std::string* response, const std::string url, const HeaderList headers) {
	CURL* curl = NULL;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		SetHeaders(curl, headers);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackStr);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			printf(RED_TEXT("[-] curl_easy_perform() failed: %s\n"), curl_easy_strerror(res));
			return false;
		}

		curl_easy_cleanup(curl);
	}

	return true;
}

bool mincurl::PostData(const std::string* response, const std::string url, const std::string& jsonData, const HeaderList headers) {
	CURL* curl = NULL;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		SetHeaders(curl, headers);

		// check if content-type header is set
		bool contentHeaderIsSet = false;
		for (const auto& header : headers) {
			if (header.name == "Content-Type") {
				contentHeaderIsSet = true;
			}
		}

		if (!contentHeaderIsSet) {
			printf(RED_TEXT("[-] content header was no set\n"));
			return false;
		}

		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonData.length());

		if (response != NULL) {
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackStr);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
		}

		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			printf(RED_TEXT("[-] curl_easy_perform() failed: %s\n"), curl_easy_strerror(res));
			return false;
		}

		curl_easy_cleanup(curl);
	}

	return true;
}

std::string mincurl::GetMediafireDirectDownload(std::string& html) {
	// find direct download on page and parse it
	size_t idPos;
	if ((idPos = html.find("id=\"downloadButton\"")) == std::string::npos) {
		std::cout << RED_TEXT("[-] couldn't find direct download link\n");
		return std::string();
	}

	size_t hrefPos{ 0 };
	hrefPos = html.substr(0, idPos).find_last_of('=');

	// get direct download and trim " and whitespaces
	std::string directoDownload = html.substr(hrefPos + 1, idPos - hrefPos - 1);
	directoDownload = str_ext::Trim("lr", directoDownload, { " ", "\""});

	return directoDownload;
}

int mincurl::DownloadFileFromURL(std::vector<uint8_t>& out, const char* url) {
	CURL* curl = NULL;
	CURLcode res;
	int ret{ 0 };

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackVec);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		// Perform the file download
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "Download failed: " << curl_easy_strerror(res) << std::endl;
		}
		else {
			//printf("file downloaded successfully from: %s\n", url);
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
	return ret;
}