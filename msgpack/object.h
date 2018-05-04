// -*-CPP-*- vim: syntax=cpp
#ifndef MSGPACK_OBJECT_H__
#define MSGPACK_OBJECT_H__

// #include <cstdint>
/* #include "Arduino.h" */
#include "type.h"

namespace msgpack {

struct object_kv;
struct object;

struct object_array {
        uint32_t size;
        object *ptr;
};

struct object_map {
        uint32_t size;
        object_kv *ptr;
};

struct object_str {
        uint32_t size;
        const char *ptr;
};

struct object_bin {
        uint32_t size;
        const char *ptr;
};

struct object_ext {
        int8_t type() const { return ptr[0]; }
        const char *data() const { return &ptr[1]; }
        uint32_t size;
        const char *ptr;
};

struct object {
        union union_type {
                bool boolean;
                uint64_t u64;
                int64_t  i64;
                double   f64;

                object_array array;
                object_map map;
                object_str str;
                object_bin bin;
                object_ext ext;
        };

        msgpack::type::object_type type;
        union_type via;

        bool is_nil() const { return type == msgpack::type::NIL; }

        object();
        ~object();

        void add_ref();
        void release();
        void cleanup();

        uint32_t ref;
};

struct object_kv {
    object key;
    object val;
};

} // namespace msgpack

#endif
