#ifndef _HTTP_
#define _HTTP_

#include <iostream>
#include <string>
#include <map>

#include "api.hpp"

using namespace std;

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
    http_request(const string _method, const string _url, const string _body = "");
    http_request(const api *_api);
    //dolazni
    http_request(const string _raw);

    void putheader(const string _key, const string _value);
    void setheaders(const map<string, string> _headers);
    void parse();
    void mold();

};


class http_response {
    public:
    string status;
    map<string, string> headers;
    string body;
    string raw;

    //konstruktor odgovora
    // odlazni
    void send(const string _body);
    // dolaznih
    void get(const string _raw);
    
    void mold();   // za slanje
    void parse();  // čitaj http
};

#endif
