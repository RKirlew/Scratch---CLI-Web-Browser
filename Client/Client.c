#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
void perform_get_request(const char *url) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        //Follow HTTP redirects
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        //Support HTTPS
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        //Set a default user agent (optional)
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    //Check if the user provided a scheme (http or https), if not, prepend "https://"
    const char *url = argv[1];
    char full_url[256]; 
    if(strncmp(url, "http://", 7) && strncmp(url, "https://", 8)) {
        snprintf(full_url, sizeof(full_url), "https://%s", url);
    } else {
        strncpy(full_url, url, sizeof(full_url));
    }
    perform_get_request(full_url);

    return 0;
}
