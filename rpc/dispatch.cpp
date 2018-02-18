#include "dispatch.h"
#include "Arduino.h"

namespace detail
{
        constexpr uint8_t sdbm(uint8_t h, const char* s) {
                return (*s == 0) ? h :
                        sdbm((static_cast<int>(*s) + (h << 6) + (h << 16) - h)
                            , s+1);
        }
}
constexpr uint64_t sdbm(const char* s)
{
        return detail::sdbm(0u, s);
}

void dispatcher::dispatch(request req)
{
        const long selector = hash(req.method().via.str.ptr);

        switch (selector) {
                case sdbm("add") : {
                        add(req);
                } break;

                default : break;
        }
}

uint8_t dispatcher::hash(const char* entry)
{
        uint8_t hash = 0;
        int c;

        while (c = *entry++)
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
}

void dispatcher::add(request req)
{
        // Serial.println("add");
        req.result(
                static_cast<uint16_t>(req.params().via.array.ptr[0].via.u64 + req.params().via.array.ptr[1].via.u64));
}
