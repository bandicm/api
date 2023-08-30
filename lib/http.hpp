#ifndef _HTTP_
#define _HTTP_

#include <iostream>
#include <string>
#include <map>

#include "elementary.hpp"
#include "api.hpp"

using namespace std;

class api;

class http_request {
    public:
    string protocol;
    string protocol;
    string method;
    string url;
    map<string, string> headers;
    string body;
    string raw;

    // konstruktori zahtjeva
    // odlazni
    http_request(const http_method _method, const string _url, const string _body = "", const string _protocol = "1.1");
    http_request(const api *_api, const string _protocol = "1.1");
    //dolazni
    http_request(const string _raw);

    //bool validate();
    void header(const string _key, const string _value);
    void header(const map<string, string> _headers);
    private:
    void parse();
    void mold();

};

static string get_protocol(const string _protocol);

class http_response {
    public:
    string protocol;
    string status;
    map<string, string> headers;
    string body;
    string raw;

    //konstruktor odgovora
    // odlazni
    http_response(const http_response_code _status, const string _body = "", const string _protocol = "1.1");
    // dolaznih
    http_response(const string _raw);

    //bool validate();
    void header(const string _key, const string _value);
    void header(const map<string, string> _headers);
    
    private:
    void mold();   // za slanje
    void parse();  // čitaj http
};

static string set_protcol(const string _protocol);

#endif
