mincurl
=======

`mincurl` is a simple C++ library that wraps common operations using libcurl. It provides easy-to-use methods for making HTTP GET, POST requests, downloading files, and handling custom headers.

* * *

Features
--------

* **GET Requests**: Fetch data from a URL.
    
* **POST Requests**: Send JSON data to a URL with custom headers.
    
* **File Download**: Download files from a URL.
    
* **Mediafire Direct Download**: Extract direct download links from Mediafire URLs.
    
* **Custom Headers**: Set custom headers for HTTP requests.
    

* * *

Installation
------------

### Prerequisites

* C++17 or later.
    
* libcurl library.
    
* Required libraries on Windows:
    
    * `ws2_32.lib`
        
    * `crypt32.lib`
        
    * `wldap32.lib`
        
    * `normaliz.lib`
        
    * `libcurl2.lib`
        

### Windows Setup

1. **Install libcurl**:
    
    * Download libcurl from curl.haxx.se/download.html.
        
    * Ensure that `libcurl` headers and libraries are properly linked.
        
2. **Include mincurl in your project**:
    
    * Copy the `mincurl` folder or clone it into your project directory.
        
    * Add the header file to your project:
        
    
    ```cpp
    #include "mincurl/mincurl.h"
    ```
    
3. **Link Dependencies**:
    
    * The following libraries are included inside mincurl.h using #pragma comment:
        
        * `ws2_32.lib`
            
        * `crypt32.lib`
            
        * `wldap32.lib`
            
        * `normaliz.lib`
            
        * `libcurl2.lib`
            

* * *

Usage
-----

### Simple Example: GET Request

```cpp
#include "mincurl/mincurl.h"

int main() {
    std::string response;
    std::string url = "https://example.com";
    
    // Perform GET request
    if (mincurl::GetURLString(&response, url)) {
        std::cout << "Response: " << response << std::endl;
    } else {
        std::cerr << "Request failed" << std::endl;
    }
}
```

### Simple Example: POST Request

```cpp
#include "mincurl/mincurl.h"

int main() {
    std::string response;
    std::string url = "https://example.com";
    std::string jsonData = "{\"key\":\"value\"}";

    // Perform POST request
    if (mincurl::PostData(&response, url, jsonData)) {
        std::cout << "Response: " << response << std::endl;
    } else {
        std::cerr << "Request failed" << std::endl;
    }
}
```

### File Download

```cpp
#include "mincurl/mincurl.h"
#include <vector>

int main() {
    std::vector<uint8_t> fileData;
    const char* url = "https://example.com/file.zip";

    // Download file to vector
    if (mincurl::DownloadFileFromURL(fileData, url)) {
        std::cout << "File downloaded successfully!" << std::endl;
    } else {
        std::cerr << "Failed to download file" << std::endl;
    }
}
```

### Mediafire Direct Download Link Extraction

```cpp
#include "mincurl/mincurl.h"

int main() {
    std::string html = "<html>...<a href=\"http://download.example.com/file\">Download</a>...</html>";
    std::string directLink = mincurl::GetMediafireDirectDownload(html);

    std::cout << "Direct download link: " << directLink << std::endl;
}
```