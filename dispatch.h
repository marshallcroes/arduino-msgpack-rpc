#ifndef RPC_DISPATCH_H__
#define RPC_DISPATCH_H__

#include "request.h"

class dispatcher {
public:
        void dispatch(request req);

private:
        void add(request req);

        uint8_t hash(const char* entry);
};

#endif
