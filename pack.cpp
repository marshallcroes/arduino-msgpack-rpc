#include "pack.h"

msgpack::packer::packer() {}

/*
    Helper function to take the first byte of T
 */

template<typename T>
char take8(T d)
{
        return static_cast<char>(reinterpret_cast<uint8_t *>(&d)[0]);
}

/*
    Helper function to store value in a printable char buffer
 */

template<typename T>
void msgpack_store(char *buf, const T &d)
{
        memcpy((T *) buf, (void *) d, sizeof(T));
}

/*
    Function to append to buffer
 */

void msgpack::packer::append_buffer(const char* buf, uint32_t l)
{
        Serial.write(buf, l);
}


msgpack::packer& msgpack::packer::pack_char(char d)
{
        pack_int8(static_cast<uint8_t>(d));

        return *this;
}



msgpack::packer& msgpack::packer::pack_nil()
{
        const char d = static_cast<char>(0xc0u);
        append_buffer(&d, 1);
        return *this;
}

msgpack::packer& msgpack::packer::pack_true()
{
        const char d = static_cast<char>(0xc3u);
        append_buffer(&d, 1);
        return *this;
}

msgpack::packer& msgpack::packer::pack_false()
{
        const char d = static_cast<char>(0xc2u);
        append_buffer(&d, 1);
        return *this;
}

msgpack::packer& msgpack::packer::pack_array(uint32_t n)
{
        if (n < 16) {
                char d = static_cast<char>(0x90u | n);
                append_buffer(&d, 1);
        } else if (n < 65536) {
                char buf[3];
                buf[0] = static_cast<char>(0xdcu);
                msgpack_store(buf, n);
                append_buffer(buf, 3);
        } else {
                char buf[5];
                buf[0] = static_cast<char>(0xddu);
                msgpack_store(buf, n);
                append_buffer(buf, 5);
        }
        return *this;
}

msgpack::packer& msgpack::packer::pack_map(uint32_t n)
{
        if (n < 16) {
                unsigned char d = static_cast<unsigned char>(0x80u | n);
                char buf = take8(d);
                append_buffer(&buf, 1);
        } else if (n < 65536) {
                char buf[3];
                buf[0] = static_cast<char>(0xdeu);
                msgpack_store(buf, n);
                append_buffer(buf, 3);
        } else {
                char buf[5];
                buf[0] = static_cast<char>(0xdfu);
                msgpack_store(buf, n);
                append_buffer(buf, 5);
        }
        return *this;
}

msgpack::packer& msgpack::packer::pack_str(uint32_t l)
{
        if (l < 32) {
                unsigned char d = static_cast<uint8_t>(0xa0u | l);
                char buf = take8(d);
                append_buffer(&buf, 1);
        } else if (l < 256) {
                char buf[2];
                buf[0] = static_cast<char>(0xd9u);
                buf[1] = static_cast<uint8_t>(l);
                append_buffer(buf, 2);
        } else if (l < 65536) {
                char buf[3];
                buf[0] = static_cast<char>(0xdau);
                msgpack_store(buf, l);
                append_buffer(buf, 3);
        } else {
                char buf[5];
                buf[0] = static_cast<char>(0xdbu);
                msgpack_store(buf, l);
                append_buffer(buf, 5);
        }
        return *this;
}

msgpack::packer& msgpack::packer::pack_str_body(const char* buff, uint32_t l)
{
        append_buffer(buff, l);
        return *this;
}

/*
    implemantation unsigned int packer
 */

msgpack::packer& msgpack::packer::pack_uint8(uint8_t d)
{
        if (d < (1 << 7)) {
                char buf = take8(d);
                append_buffer(&buf, 1);
        } else {
                char buf[2] = {static_cast<char>(0xccu), take8(d)};
                append_buffer(buf, 2);
        }

        return *this;
}

msgpack::packer& msgpack::packer::pack_uint16(uint16_t d)
{
        if (d < (1 << 8)) {
                return pack_uint8(static_cast<uint8_t>(d));
        } 

        char buf[3];
        buf[0] = static_cast<char>(0xcdu);
        msgpack_store(buf, d);
        append_buffer(buf, 3);

        return *this;
}

msgpack::packer& msgpack::packer::pack_uint32(uint32_t d)
{

        if (d < (1 << 16)) {
                return pack_uint16(static_cast<uint16_t>(d));
        }

        char buf[5];
        buf[0] = static_cast<char>(0xceu);
        msgpack_store(buf, d);
        append_buffer(buf, 5);

        return *this;
}

/*
    implemantation signed int packer
 */

msgpack::packer& msgpack::packer::pack_int8(int8_t d)
{
        if (d < -(1 << 5)) {
                char buf[2] = {static_cast<char>(0xd0u), take8(d)};
                append_buffer(buf, 2);
        } else {
                char buf = take8(d);
                append_buffer(&buf, 1);
        }

        return *this;
}

msgpack::packer& msgpack::packer::pack_int16(int16_t d)
{
        if (d < -(1 << 5)) {
                if (d < -(1 << 7)) {
                        /* signed 16 */
                        char buf[3];
                        buf[0] = static_cast<char>(0xd1u);
                        msgpack_store(buf, d);
                        append_buffer(buf, 3);
                } else {
                        /* signed 8 */
                        char buf[2] = {static_cast<char>(0xd0u), take8(d)};
                        append_buffer(buf, 2);
                }
        } else if (d < (1 << 7)) {
                /* fixnum */
                char buf = take8(d);
                append_buffer(&buf, 1);
        } else {
                if (d < (1 << 8)) {
                        /* unsigned 8 */
                        char buf[2] = {static_cast<char>(0xccu), take8(d)};
                        append_buffer(buf, 2);
                } else {
                        /* unsigned 16 */
                        char buf[3];
                        buf[0] = static_cast<char>(0xcdu);
                        msgpack_store(buf, d);
                        append_buffer(buf, 3);
                }
        }

        return *this;
}

msgpack::packer& msgpack::packer::pack_int32(int32_t d)
{
        if (d < -(1 << 5)) {
                if (d < -(1 << 15)) {
                        /* signed 32 */
                        char buf[5];
                        buf[0] = static_cast<char>(0xd2u);
                        msgpack_store(buf, d);
                        append_buffer(buf, 5);
                } else if (d < -(1 << 7)) {
                        /* signed 16 */
                        char buf[3];
                        buf[0] = static_cast<char>(0xd1u);
                        msgpack_store(buf, d);
                        append_buffer(buf, 3);
                } else {
                        /* signed 8 */
                        char buf[2] = {static_cast<char>(0xd0u), take8(d)};
                        append_buffer(buf, 2);
                }
        } else if (d < (1 << 7)) {
                /* fixnum */
                char buf = take8(d);
                append_buffer(&buf, 1);
        } else {
                if (d < (1 << 8)) {
                        /* unsigned 8 */
                        char buf[2] = {static_cast<char>(0xccu), take8(d)};
                        append_buffer(buf, 2);
                } else if (d < (1 << 16)) {
                        /* unsigned 16 */
                        char buf[3];
                        buf[0] = static_cast<char>(0xcdu);
                        msgpack_store(buf, d);
                        append_buffer(buf, 3);
                } else {
                        /* unsigned 32 */
                        char buf[5];
                        buf[0] = static_cast<char>(0xceu);
                        msgpack_store(buf, d);
                        append_buffer(buf, 5);
                }
        }

        return *this;
}
