#include "parser.h"

void detail::parse_uint8(uint8_t d, msgpack::object &o)
{
        o.type = msgpack::type::POSITIVE_INTEGER;
        o.via.u64 = d;
}

void detail::parse_uint16(uint16_t d, msgpack::object &o)
{
        o.type = msgpack::type::POSITIVE_INTEGER;
        o.via.u64 = d;
}

void detail::parse_uint32(uint32_t d, msgpack::object &o)
{
        o.type = msgpack::type::POSITIVE_INTEGER;
        o.via.u64 = d;
}

void detail::parse_uint64(uint64_t d, msgpack::object &o)
{
        o.type = msgpack::type::POSITIVE_INTEGER;
        o.via.u64 = d;
}

void detail::parse_int8(int8_t d, msgpack::object &o)
{
        if (d >= 0) {
                o.type = msgpack::type::POSITIVE_INTEGER;
                o.via.u64 = static_cast<uint64_t>(d);
        } else {
                o.type = msgpack::type::NEGATIVE_INTEGER;
                o.via.i64 = d;
        }
}

void detail::parse_int16(int16_t d, msgpack::object &o)
{
        if (d >= 0) {
                o.type = msgpack::type::POSITIVE_INTEGER;
                o.via.u64 = static_cast<uint64_t>(d);
        } else {
                o.type = msgpack::type::NEGATIVE_INTEGER;
                o.via.i64 = d;
        }
}

void detail::parse_int32(int32_t d, msgpack::object &o)
{
        if (d >= 0) {
                o.type = msgpack::type::POSITIVE_INTEGER;
                o.via.u64 = static_cast<uint64_t>(d);
        } else {
                o.type = msgpack::type::NEGATIVE_INTEGER;
                o.via.i64 = d;
        }
}

void detail::parse_int64(int64_t d, msgpack::object &o)
{
        if (d >= 0) {
                o.type = msgpack::type::POSITIVE_INTEGER;
                o.via.u64 = static_cast<uint64_t>(d);
        } else {
                o.type = msgpack::type::NEGATIVE_INTEGER;
                o.via.i64 = d;
        }
}

void detail::parse_nil(msgpack::object &o) { o.type = msgpack::type::NIL; }

void detail::parse_true(msgpack::object &o)
{
        o.type = msgpack::type::BOOLEAN;
        o.via.boolean = true;
}

void detail::parse_false(msgpack::object &o)
{
        o.type = msgpack::type::BOOLEAN;
        o.via.boolean = false;
}

void detail::parse_array::operator()(uint32_t n, msgpack::object &o) const
{
        o.type = msgpack::type::ARRAY;
        o.via.array.size = 0;
        size_t size = n * sizeof(msgpack::object);
        o.via.array.ptr =
                static_cast<msgpack::object *>(malloc(size));
}

void detail::parse_array_item(msgpack::object &c, msgpack::object const &o)
{
        // c.via.array.ptr[c.via.array.size++] = o;

        memcpy(&c.via.array.ptr[c.via.array.size++], &o, sizeof(msgpack::object));

        o.add_ref();
}

void detail::parse_map::operator()(uint32_t n, msgpack::object &o) const
{
        // o.type = msgpack::type::MAP;
        // o.via.map.size = 0;
        // size_t size = n * sizeof(msgpack::object_kv);
        // o.via.map.ptr =
        //         static_cast<msgpack::object_kv *>(u.zone().allocate_align(
        //                 size, MSGPACK_ZONE_ALIGNOF(msgpack::object_kv)));
}

void detail::parse_map_item(msgpack::object &c, msgpack::object const &k,
                    msgpack::object const &v)
{

        // c.via.map.ptr[c.via.map.size].key = k;
        // c.via.map.ptr[c.via.map.size].val = v;

        // ++c.via.map.size;
}

void detail::parse_str(const char *p, uint32_t l, msgpack::object &o)
{
        o.type = msgpack::type::STR;
        // o.via.str.ptr = p;

        o.via.str.ptr = (char *) malloc(sizeof(char) * l);
        memcpy(o.via.str.ptr,  p, l);

        o.via.str.size = l;
}
