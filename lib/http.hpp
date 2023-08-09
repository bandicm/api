#ifndef _HTTP_
#define _HTTP_

#include <iostream>
#include <string>
#include <map>

#include "elementary.hpp"
#include "api.hpp"

using namespace std;

class defapi;
class api;

class http_request {
    public:
    string method;
    string url;
    map<string, string> headers;
    string body;
    string raw;

    // konstruktori zahtjeva
    // odlazni
    http_request(const http_method _method, const string _url, const string _body = "");
    http_request(const api *_api);
    //dolazni
    http_request(const string _raw);

    //bool validate();
    void putheader(const string _key, const string _value);
    void setheaders(const map<string, string> _headers);
    void parse();
    void mold();

};


class http_response {
    public:
    string protocol;
    string status;
    map<string, string> headers;
    string body;
    string raw;

    //konstruktor odgovora
    // odlazni
    http_response(const http_response_code _status, const string _body, const string _protocol = "1.1");
    // dolaznih
    http_response(const string _raw);

    //bool validate();
    // void putheader(const string _key, const string _value);
    // void putheaders(const map<string, string> _headers);
    
    void mold();   // za slanje
    void parse();  // čitaj http
};



#endif
