#include "../lib/api.hpp"

defapi::defapi(const vector<string> _methods, const vector<string> _paths, const vector<string> _keys) {
    methods = _methods;
    paths = _paths;
    keys = _keys;
}

void defapi::necessary(const string _path, const vector<string> _keys) {
    val_matrix[_path].insert( val_matrix[_path].end(), _keys.begin(), _keys.end());
}

// radi
api::api(defapi* _def, const string _method, const string _path, const map<string, string> _params, const string _body) {
    def = _def;
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

    if (!validate()) {
        cout << "Nije ispravan API" << endl;
    }
}

// radi
api::api(defapi* _def, const http_request _req) {
    def = _def;
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

    // if (!validate()) {
    //     cout << "Nije ispravan API" << endl;
    // }

}


bool api::validate() {
    bool isValidate = true;

    // api validacija ključeva
    for (uint i=0; i<def->val_matrix[path].size(); i++) {
        def->val_matrix[path][i];
        if (params[def->val_matrix[path][i]].empty()) {
            isValidate = false;
            break;           
        }
    }

    return isValidate;
}

