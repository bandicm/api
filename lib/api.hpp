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


class defapi {
    public:
    vector<string> methods;
    vector<string> paths;
    vector<string> keys;
    map<string, vector<string>> val_matrix;

    defapi(const vector<string> _methods, const vector<string> _paths, const vector<string> _keys);
    void necessary(const string _path, const vector<string> _keys);
};

class api {
    public:
    defapi* def;

    string method;
    string path;
    map<string, string> params;
    string url;
    string body;

    // odlazni api zahtjev
    api(defapi* _def, const string _method, const string _path, const map<string, string> _params = {}, const string _body = {});
    // dolazni api zahjtev
    api(defapi* _def, const http_request _req);
    // bool validate();

};

#endif
