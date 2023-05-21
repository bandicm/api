#include "../lib/api.hpp"

defapi::defapi(const vector<string> _options, const vector<string> _keys) {
    options = _options;
    keys = _keys;
}

void defapi::necessary(const string _option, const vector<string> _keys) {
    val_matrix[_option].insert( val_matrix[_option].end(), _keys.begin(), _keys.end());
}

api::api(defapi *_def, const string _option, const map<string, string> _object) {
    def = _def;
    object = _object;
    option = _option;
    
    if (!validate()) {
        cout << "Validate API error" << endl;
    }
    format();

}

api::api(defapi *_def, const string _body) {
    def = _def;
    body = _body;

    parse();
    if (!validate()) {
        cout << "Validate API error" << endl;
    }
        
}

bool api::validate() {
    bool isValidate = true;

    for (uint i=0; i<def->val_matrix[option].size(); i++) {
        def->val_matrix[option][i];
        if (object[def->val_matrix[option][i]].empty()) {
            isValidate = false;
            break;           
        }
    }

    return isValidate;
}

void api::parse() {

    for (uint i=0; i<def->options.size(); i++) {
        if (body.find("/"+def->options[i]+"/") < body.length()) {
            option = def->options[i];
        }
    }

    for (uint i=0; i<def->keys.size(); i++) {
        string key = def->keys[i]+"=";
        string value;
        if (body.find(key) < body.length()) {
            value = body.substr(body.find(key)+key.length(),  body.find('&',body.find(key)+key.length())-body.find(key)-key.length() < body.find(' ',body.find(key)+key.length())-body.find(key)-key.length() ? body.find('&',body.find(key)+key.length())-body.find(key)-key.length() : body.find(' ',body.find(key)+key.length())-body.find(key)-key.length());
        }
        object[def->keys[i]] = value;
    }

}

void api::format() {
    
    body = "GET /";

    if (!option.empty()) {
        body += option + '/';
    }
    
    body += '?';

    for (uint i=0; i<def->keys.size(); i++) {
        if (!object[def->keys[i]].empty()) {
            body += def->keys[i] + "=" + object[def->keys[i]] + "&";
        }
    }

    body.pop_back();
    body += " HTTP/1.1";

}