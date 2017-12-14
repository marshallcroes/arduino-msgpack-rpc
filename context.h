#ifndef MSGPACK_DETAIL_CONTEXT_H__
#define MSGPACK_DETAIL_CONTEXT_H__

#include "Arduino.h"

#include "object.h"

namespace detail {

    class context {
    public:
        context();

        void init();

        void execute();

        const msgpack::object& data();

    private:
        // template <typename T>
        // static uint32_t next_cs(T p);

        // template <typename T, typename Func>
        // int push_aggregate(
        //         const Func& f,
        //         uint32_t container_type,
        //         msgpack::object& obj,
        //         const char* load_pos,
        //         std::size_t& off);

        void push_item(msgpack::object& obj);

        void push_proc(msgpack::object& obj);

        msgpack::object m_o;
    };

} // detail

#endif
