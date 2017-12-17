#include "object.h"

// #include "adaptor/adaptor_base.h"

msgpack::object::object()
{
        type = msgpack::type::NIL;
        ref = 1;
}

msgpack::object::~object()
{
        release();
        cleanup();

        if (!ref)
                switch (type) {
                        case msgpack::type::ARRAY : {
                                // Serial.println("dtor: arr");
                                free(via.array.ptr);
                        } break;

                        case msgpack::type::MAP : {
                                free(via.map.ptr);
                        } break;

                        case msgpack::type::STR : {
                                // Serial.println("dtor: str");
                                free((void *) via.str.ptr);
                        } break;

                        default : break;
                }
}

void msgpack::object::add_ref() {
        ref++;
}

void msgpack::object::release() {
        ref--;
}

void msgpack::object::cleanup() {
        if (type == msgpack::type::ARRAY) {
                for (int i=0; i<via.array.size; i++) {
                        via.array.ptr[i].~object();
                }
        }
}
