#include <iostream>

#include "../lib/api.hpp"

using namespace std;

int main() {

    try {

        api uf(GET, "delete", {make_pair("id", "4")}, "bay");
        http_request myreq(&uf);
        myreq.putheader("Content-type", "text/plain");

        cout << myreq.raw << endl;

        http_response myres("HTTP/1.1 200 OK\r\n\r\nnotauth");
        cout << myres.protocol << endl;
        cout << myres.status << endl;
        // cout << myres.headers << endl;
        cout << myres.body << endl;


        http_response myres2(OK, "nnotauth", "1.0" );
        cout << myres2.protocol << endl;
        cout << myres2.status << endl;
        // cout << myres2.headers << endl;
        cout << myres2.body << endl;


    

    // http myHttp(&myApi, "GET /fghfhf HTTP/1.1\r\nBaba");
    // //http myHttp(&myApi, "GET /hello/?id=4&post=99 HTTP/1.1\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\nHost: www.tutorialspoint.com\r\nAccept-Language: en-us\r\nAccept-Encoding: gzip, deflate\r\nConnection: Keep-Alive\r\n\r\nHELLO WORLD\r\n");


    //cout << myHttp.rawall;

    // http_request mojzahtjev("GET", "/baba/maloroga?value1=54", "good" );
    // mojzahtjev.putheader("Content-type", "text/plain");

    // cout << mojzahtjev.method << " " << mojzahtjev.url << endl << mojzahtjev.raw;


    // http_request myres(&uf);
    

    // http_request myres("GET /delete?id=4 HTTP/1.1\r\nContent-type: text/plain\r\n\n\rBAY");

    // myres.get("HTTP/1.1 200 OK\r\n\r\nnotauth");
    // myres.get("HTTP/1.1 200 OK");


    // api uf(&myApi, myres);

    // cout << uf.method << " " << uf.path  << " " << uf.body << endl;
    // cout << myres.method << " " << myres.url  << " " << myres.body << endl << myres.raw << endl;


    // for(auto i : uf.params) 
    //     cout << i.first << " " << i.second << endl;

    } catch (string err) {
        cout << err << endl;
    }

}
