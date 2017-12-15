#include "pack.h"
#include "type.h"

namespace msgpack {
/*
    template functions for packing
 */

template <>
packer& packer::pack<uint8_t>(const uint8_t& v)
{
        return pack_uint8(v);
}

template <>
packer& packer::pack<uint16_t>(const uint16_t& v)
{
        return pack_uint16(v);
}

template <>
packer& packer::pack<uint32_t>(const uint32_t& v)
{
        return pack_uint32(v);
}

template <>
packer& packer::pack<uint64_t>(const uint64_t& v)
{
        return pack_uint32(static_cast<uint32_t>(v));
}

template <>
packer& packer::pack<int8_t>(const int8_t& v)
{
        return pack_int8(v);
}

template <>
packer& packer::pack<int16_t>(const int16_t& v)
{
        return pack_int16(v);
}

template <>
packer& packer::pack<int32_t>(const int32_t& v)
{
        return pack_int32(v);
}

template <>
packer& packer::pack<int64_t>(const int64_t& v)
{
        return pack_int32(static_cast<int32_t>(v));
}

template <>
packer& packer::pack<bool>(const bool& v)
{
        if (v)
                return pack_true();

        return pack_false();
}

template <>
packer& packer::pack<msgpack::type::nil_t>(const msgpack::type::nil_t& v)
{
        return pack_nil();
}

} // msgpack
