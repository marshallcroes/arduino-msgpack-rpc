#ifndef MSGPACK_DETAIL_PARSER_H__
#define MSGPACK_DETAIL_PARSER_H__

#include "object.h"

// #include "unpack_user.h"

namespace detail {

void parse_uint8(uint8_t d, msgpack::object &o);
void parse_uint16(uint16_t d, msgpack::object &o);
void parse_uint32(uint32_t d, msgpack::object &o);
void parse_uint64(uint64_t d, msgpack::object &o);

void parse_int8(int8_t d, msgpack::object &o);
void parse_int16(int16_t d, msgpack::object &o);
void parse_int32(int32_t d, msgpack::object &o);
void parse_int64(int64_t d, msgpack::object &o);

// void parse_float(float d, msgpack::object &o);
// void parse_double(double d, msgpack::object &o);

void parse_nil(msgpack::object &o);

void parse_true(msgpack::object &o);
void parse_false(msgpack::object &o);

struct parse_array {
        void operator()(uint32_t n, msgpack::object &o) const;
};

void parse_array_item(msgpack::object &c, msgpack::object const &o);

struct parse_map {
        void operator()(uint32_t n, msgpack::object &o) const;
};

void parse_map_item(msgpack::object &c, msgpack::object const &k,
                    msgpack::object const &v);

void parse_str(const char *p, uint32_t l, msgpack::object &o);
// void parse_bin(unpack_user &u, const char *p, uint32_t l, msgpack::object &o);
// void parse_ext(unpack_user &u, const char *p, std::size_t l, msgpack::object &o);

};

#endif
