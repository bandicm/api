#include "../lib/http.hpp"

http_request::http_request(const http_method _method, const string _url, const string _body, const string _protocol) {
    method = http_method_to_str(_method);
    url = _url;
    protocol = get_protocol(_protocol);
    if (!_body.empty()) {
        body = _body;
        this->header("Content-Length", to_string(body.length()));
    }
    mold();
}

http_request::http_request(const api *_api,  const string _protocol) {
    method = _api->method;
    url = _api->url;
    protocol = get_protocol(_protocol);
    if (!_api->body.empty()) {
        body = _api->body;
        this->header("Content-Length", to_string(body.length()));
    }
    mold();
}

http_request::http_request(const string _raw) {
    raw = _raw;
    parse();
}

void http_request::parse() {

    if (raw.empty()) {
        return;
    }

    method = raw.substr(0, raw.find(" "));
    url = raw.substr(raw.find("/"), raw.find("HTTP/")-raw.find("/")-1);

    string _headers = raw.substr(raw.find("\r\n")+2, raw.find("\r\n\r\n")-raw.find("\r\n")-2);
    while (!_headers.empty()) {
        string key, value;
        key = _headers.substr(0, _headers.find(": "));
        _headers.erase(0, key.length()+2);
        value = _headers.substr(0, _headers.find("\r\n"));
        _headers.erase(0, value.length()+2);
        headers.insert(make_pair(key, value));
    }

    if ((size_t)raw.find("\r\n\r\n") == (size_t)raw.find("\r\n"))
        body = raw.substr(raw.find("\r\n\r\n")+4, raw.length()-raw.find("\r\n\r\n")-4);

    else if ((size_t)raw.find("\r\n\r\n") < raw.length())
        body = raw.substr(raw.find("\r\n\r\n")+4, raw.find("\r\n")-raw.find("\r\n\r\n")-4);

}

void http_request::header(const string _key, const string _value) {
    headers[_key] = _value;
    mold();
}

void http_request::header(const map<string, string> _headers) {
    headers = _headers;
    mold();
}

/**
 * http zahtjev formiranje raw 
*/

void http_request::mold() {

    raw = method.empty() ? "GET" : method;
    raw += " " + url + " " + protocol + "\r\n";

    if (!headers.empty()) {
        for (auto i : headers) {
            raw += i.first + ": " + i.second + "\r\n"; 
        }
    }

    raw += "\r\n" + body;
}

http_response::http_response(const http_response_code _status, const string _body, const string _protocol) {
    status = to_string(_status) + " " + http_response_code_txt(_status);
    if (!_body.empty()) {
        body = _body;
        // kad merge s header-response branch možeš omogućit ovu liniju
        // this->header("Content-Length", to_string(body.length()));
    }
    protocol = get_protocol(_protocol);
    mold();        
}


static string get_protocol(const string _protocol) {
    string protocol;
    if (_protocol == "1.0" || _protocol == "1.1" || _protocol == "2.0") {
        protocol = "HTTP/" + _protocol;
    }
    else { 
        protocol = "HTTP/1.1";
    }
    return protocol;
}


http_response::http_response(const string _raw) {
    raw = _raw;
    parse();
}

void http_response::header(const string _key, const string _value) {
    headers[_key] = _value;
    mold();
}

void http_response::header(const map<string, string> _headers) {
    headers = _headers;
    mold();
}


void http_response::mold() {
    raw = protocol + " " + status + "\r\n"; //"HTTP/1.1 200 OK\r\n"; // implementirati status
    if (!headers.empty()) {
        for (auto i : headers) {
            raw += i.first + ": " + i.second + "\r\n"; 
        }
    }

    raw += "\r\n" + body;
}


void http_response::parse() {

    if (raw.empty()) {
        return;
    }

    string protocol = raw.substr(0, raw.find(" "));
    status = raw.substr(raw.find(" ")+1, raw.find(" ",raw.find(" ")+1)-raw.find(" ")-1);

    if ((size_t)raw.find("\r\n") < raw.length()) {
        string _headers = raw.substr(raw.find("\r\n")+2, raw.find("\r\n\r\n")-raw.find("\r\n")-2);
        while (!_headers.empty()) {
            string key, value;
            key = _headers.substr(0, _headers.find(": "));
            _headers.erase(0, key.length()+2);
            value = _headers.substr(0, _headers.find("\r\n"));
            _headers.erase(0, value.length()+2);
            headers.insert(make_pair(key, value));
        }
    }
    // ne radi za specijalan slučaj kada nema zaglavlja
    if ((size_t)raw.find("\r\n\r\n") == (size_t)raw.find("\r\n"))
        body = raw.substr(raw.find("\r\n\r\n")+4, raw.length()-raw.find("\r\n\r\n")-4);

    else if ((size_t)raw.find("\r\n\r\n") < raw.length())
        body = raw.substr(raw.find("\r\n\r\n")+4, raw.find("\r\n")-raw.find("\r\n\r\n")-4);

}

static string set_protcol(const string _protocol) {
    string protocol;
    if (_protocol == "1.0" || _protocol == "1.1" || _protocol == "2.0") {
        protocol = "HTTP/" + _protocol;
    }
    else { 
        protocol = "HTTP/1.1";
    }
    return protocol;
}