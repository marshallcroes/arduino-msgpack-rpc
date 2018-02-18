#ifndef MSGPACK_PACK_H__
#define MSGPACK_PACK_H__

#include "Arduino.h"
// #include <cstddef>
// #include <cstdint>
// #include <string>

namespace  msgpack {

class packer {
public:
        packer();

        template<typename T>
        packer &pack(const T &v);

        /*
            pack unsigned ints
         */

        packer &pack_uint8(uint8_t d);

        packer &pack_uint16(uint16_t d);

        packer &pack_uint32(uint32_t d);

        packer &pack_uint64(uint64_t d);

        /*
            pack signed ints
         */

        packer &pack_int8(int8_t d);

        packer &pack_int16(int16_t d);

        packer &pack_int32(int32_t d);

        packer &pack_int64(int64_t d);

        /*
            pack char
         */

        packer &pack_char(char d);

        /*
            pack nil, bool
         */

        packer &pack_nil();

        packer &pack_true();

        packer &pack_false();

        /*
            pack containers
         */

        packer &pack_array(uint32_t n);

        packer &pack_map(uint32_t n);

        packer &pack_str(uint32_t);

        packer &pack_str_body(const char* b, uint32_t l);


private:
        void append_buffer(const char* buf, uint32_t l);
};

}

#endif
