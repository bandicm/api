#ifndef _API_
#define _API_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "http.hpp"

using namespace std;

class http_request;
class http_response;

class api {
    public:
    string method;
    string path;
    map<string, string> params;
    string url;
    string body;

    // odlazni api zahtjev
    api(const string _method, const string _path, const map<string, string> _params = {}, const string _body = {});
    // dolazni api zahjtev
    api(const http_request _req);
};

#endif
