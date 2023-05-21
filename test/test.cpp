#include <iostream>

#include "../lib/api.hpp"

using namespace std;

int main() {

    defapi myDef({"add", "delete", "update"}, {"id", "key", "value"});

    // cout << myDef.keys[2];

    myDef.necessary("add", {"id", "key", "value"});
    myDef.necessary("delete", {"id"});
    myDef.necessary("update", {"id"});
    myDef.necessary("update", {"value"});
    
    // cout << myDef.val_matrix["delete"].empty();

    api myApi(&myDef, "GET /update/?id=1&value=true HTTP/1.1");

    cout << myApi.object["value"];


}