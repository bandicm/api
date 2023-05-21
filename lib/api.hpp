#ifndef _API_
#define _API_

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class defapi {
    public:
    vector<string> options;
    vector<string> keys;

    map<string, vector<string>> val_matrix;

    defapi(const vector<string> _options, const vector<string> _keys);
    void necessary(const string _option, const vector<string> _keys);

};

class api {
    public:
    defapi *def;

    string option;
    map<string, string> object;
    string body;

    api(defapi *_def, const string _option, const map<string, string> _object);
    api(defapi *_def, const string _body);
        
    private:
    bool validate();
    void parse();  // čitaj api
    void format(); // šalji api

    // ~api();
};

#endif
