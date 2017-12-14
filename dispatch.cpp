#include "dispatch.h"

void dispatcher::dispatch(request req)
{
        const long selector = hash(req.method);

        switch (selector) {
                case hash("add") : {
                        add(req.param);
                } break;

                default : break;
        }
}

long dispatcher::hash(const char* entry)
{
        return 0;
}
