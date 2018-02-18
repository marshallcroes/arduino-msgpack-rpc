//
// Created by marshall croes on 05/12/17.
//

#ifndef MSGPACK_RPC_TYPE_H__
#define MSGPACK_RPC_TYPE_H__

namespace msgpack {

namespace type {

enum object_type {
    NIL              = 0x00,
    BOOLEAN          = 0x01,
    POSITIVE_INTEGER = 0x02,
    NEGATIVE_INTEGER = 0x03,
    FLOAT32          = 0x0a,
    FLOAT64          = 0x04,
    FLOAT            = 0x04,
    STR              = 0x05,
    BIN__              = 0x08,
    ARRAY            = 0x06,
    MAP              = 0x07,
    EXT              = 0x09
};

struct nil_t {};

}//type

}//msgpck


#endif //MSGPACK_RPC_TYPE_H
