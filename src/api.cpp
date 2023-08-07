#include "../lib/api.hpp"

api::api(const string _method, const string _path, const map<string, string> _params, const string _body) {
    method = _method;
    path = _path;   
    url = path;

    if (!_params.empty()) {
        url += '?';
        for (auto i : _params) {
            url += i.first + '=' + i.second + '&'; 
        }
        url.pop_back();
    }

    body = _body;

}

api::api(const http_request _req) {
    method = _req.method;
    //path = _path;   
    url = _req.url;

    if ( (size_t)url.find("?") < (size_t)url.length() ) {
        path = url.substr(0, url.find("?"));

        string str_params = url.substr(url.find("?")+1, url.length()-url.find("?")-1);
        while (!str_params.empty()) {
            string key, value;
            key = str_params.substr(0, str_params.find('='));
            str_params.erase(0, key.length()+1);
            value = str_params.substr(0, str_params.find('&'));
            str_params.erase(0, value.length()+1);
            params.insert(make_pair(key, value));
        }
    }
    else {
        path = url;
    }

    body = _req.body;

}