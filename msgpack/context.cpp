#include "context.h"
#include "parser.h"


detail::context::context()
{

}

void detail::context::init()
{

}

// TODO: refactor to agregate item
// void detail::context::push_item(msgpack::object& obj, const uint8_t& selector) {
//         uint8_t selector;

//         Serial.readBytes(&selector, 1);

//         if (0x00 <= selector && selector <= 0x7f) {

//         } else if (0xe0 <= selector && selector <= 0xff) {
//                 //neg int
//         }

//         } else if (0xa0 <= selector && selector <= 0xbf) {
//                 uint8_t str_size = selector & 0x1f;

//                 char *str;
//                 Serial.readBytes(str, str_size);

//                 detail::parse_str(str, str_size, obj);

//         } else {
//                 detail::parse_uint8(selector, obj);
//         }
// }

// TODO: refactor to process item
void detail::context::push_proc(msgpack::object& obj)
{
        uint8_t selector;

        Serial.readBytes(&selector, 1);

        // positive fix int
        if (0x00 <= selector && selector <= 0x7f) {
                detail::parse_uint8(selector, obj);
        // negative fix int
        } else if (0xe0 <= selector && selector <= 0xff) {
                detail::parse_int8(selector, obj);
        // fix string
        } else if (0xa0 <= selector && selector <= 0xbf) {
                uint8_t str_size = selector & 0x1f;

                char str[str_size];
                Serial.readBytes(&str[0], str_size);

                detail::parse_str(&str[0], str_size, obj);

        // fix map
        } else if (0x80 <= selector && selector <= 0x8f) {
                uint8_t map_size = selector & 0x0f;

                detail::parse_map()(map_size, obj);

                for (int i=0; i<map_size; i++) {
                        msgpack::object c;

                        msgpack::object key;
                        msgpack::object val;

                        push_proc(key);
                        push_proc(val);

                        detail::parse_map_item(c, key, val);
                }
        // fix array
        } else if (0x90 <= selector && selector <= 0x9f) {
                uint8_t array_size = selector & 0x0f;

                detail::parse_array()(array_size, obj);

                for (int i=0; i<array_size; i++) {
                        msgpack::object item;
                        push_proc(item);

                        detail::parse_array_item(obj, item);
                }
        // others
        } else if (0xc4 <= selector && selector <= 0xdf) {
                return;
        } else if (0xc0 == selector) {
                // nil
                detail::parse_nil(obj);
        } else if (0xc2 == selector) {
                // false
                detail::parse_false(obj);
        } else if (0xc3 == selector) {
                // true
                detail::parse_true(obj);
        // error
        } else {
                return;
        }
}

void detail::context::execute()
{
        push_proc(m_o);
}

const msgpack::object& detail::context::data() {
        return m_o;
}
