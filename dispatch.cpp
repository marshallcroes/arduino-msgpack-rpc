#include "dispatch.h"
#include "Arduino.h"

constexpr long case_hash(const char* entry)
{
        return 0;
}

void dispatcher::dispatch(request req)
{
        const long selector = hash(req.method().via.str.ptr);

        switch (selector) {
                case case_hash("add") : {
                        add(req);
                } break;

                default : break;
        }
}

long dispatcher::hash(const char* entry)
{
        return 0;
}

void dispatcher::add(request req)
{
        Serial.println("add");
        req.result(req.params().via.array.ptr[0].via.u64 + req.params().via.array.ptr[1].via.u64);
}
