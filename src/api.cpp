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

    // Extract the query string from the API request
    size_t queryStart = body.find('?');
    size_t protocolEnd = body.find("HTTP/");
    if (queryStart == string::npos || (protocolEnd != string::npos && queryStart > protocolEnd)) {
        // cout << "No object found in the API request." << endl;
        return;
    }

    size_t queryStringStart = (queryStart != string::npos) ? queryStart + 1 : 0;
    string queryString = body.substr(queryStringStart, protocolEnd - queryStringStart);

    // Parse the query string and extract key-value pairs
    istringstream iss(queryString);
    string parameter;
    while (getline(iss, parameter, '&')) {
        size_t equalSignPos = parameter.find('=');
        if (equalSignPos != string::npos) {
            string key = parameter.substr(0, equalSignPos);
            string value = parameter.substr(equalSignPos + 1);
            object[key] = value;
        }
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
