#ifndef RPC_PROTOCOL_H__
#define RPC_PROTOCOL_H__

#include "object.h"
#include "pack.h"

typedef uint32_t msgid_t;
typedef uint32_t method_t;

typedef uint8_t message_type_t;
typedef uint8_t error_type_t;

static const message_type_t REQUEST  = 0;
static const message_type_t RESPONSE = 1;
static const message_type_t NOTIFY   = 3;

static const error_type_t NO_METHOD_ERROR = 0x01;
static const error_type_t ARGUMENT_ERROR  = 0x02;

/*
    Message struct for the different msg types
 */

struct msg_rpc {
        msg_rpc() : type(REQUEST) {  }

        message_type_t type;

        bool is_request() const { return type == REQUEST; }
        bool is_response() const { return type == RESPONSE; }
        bool is_notify() const { return type == NOTIFY; }
};

template <typename Method, typename Parameter>
struct msg_request {
        msg_request() : type(REQUEST), msgid(0) {  }

        msg_request(Method method,
                    Parameter param,
                    msgid_t msgid) :
                type(REQUEST), msgid(msgid), method(method), param(param) {  }

        message_type_t type;
        msgid_t msgid;
        Method method;
        Parameter param;
};

template <typename Result, typename Error>
struct msg_response {
        msg_response() : type(RESPONSE), msgid(0) {  }

        msg_response(
                        Result result,
                        Error error,
                        msgid_t msgid) :
                type(RESPONSE), msgid(msgid), error(error), result(result) {  }

        message_type_t type;
        msgid_t msgid;
        Error error;
        Result result;
};

template <typename Method, typename Parameter>
struct msg_notify {
        msg_notify() : type(RESPONSE) {  }

        msg_notify(
                        Method method,
                        Parameter param) :
                type(NOTIFY), method(method), param(param) {  }

        message_type_t type;
        Method method;
        Parameter param;
};

/*
    addaptors to convert msgpack objects into structs
 */

template <typename T>
struct convert {
    msgpack::object const& operator()(const msgpack::object&, T&) const;
};

template <>
struct convert<msg_rpc> {
        msgpack::object const& operator()(const msgpack::object& o, msg_rpc& v) const {
                // Only necesary to distinct between requests and notify
                v.type = o.via.array.ptr[0].via.u64;
        }
};

template <>
struct convert<msg_request<msgpack::object, msgpack::object> > {
        msgpack::object const& operator()(const msgpack::object& o,
                                          msg_request<msgpack::object, msgpack::object>& v)
        const {
                // Standard for all request
                v.type   = o.via.array.ptr[0].via.u64;
                v.msgid  = o.via.array.ptr[1].via.u64;
                v.method = o.via.array.ptr[2];

                // Depends on caller
                v.param  = o.via.array.ptr[3];

                // Add refs count
                o.via.array.ptr[2].add_ref();
                o.via.array.ptr[3].add_ref();
        }
};

template <>
struct convert<msg_notify<msgpack::object, msgpack::object> > {
        const msgpack::object& operator()(const msgpack::object& o,
                                          msg_notify<msgpack::object, msgpack::object>& v)
        const {
                // Standard layout
                v.type   = o.via.array.ptr[0].via.u64;
                v.method = o.via.array.ptr[1];

                // Depends on caller
                v.param  = o.via.array.ptr[2];
        }
        
};

/*
    Adaptor to convert struct into msgpack buffer
 */

template <typename T>
struct pack {
    msgpack::packer& operator()(msgpack::packer&, const T&) const;
};

// template <>
// struct pack<msg_response<msgpack::object, msgpack::object> > {
//         msgpack::packer& operator()(msgpack::packer&o,
//                                     const msg_response<msgpack::object, msgpack::object>& v)
//         const {
//                 o.pack_array(4);

//                 // Standard for all response
//                 o.pack_uint8(v.type);
//                 o.pack_uint16(v.msgid);

//                 // Depends on caller
//                 o.pack(v.error);
//                 o.pack(v.result);
//         }
// };

// template <>
// struct pack<msg_response<msgpack::type::nil_t, msgpack::type::nil_t> > {
//         msgpack::packer& operator()(msgpack::packer&o,
//                                     const msg_response<msgpack::type::nil_t, msgpack::type::nil_t>& v)
//         const {
//                 o.pack_array(4);

//                 // Standard for all response
//                 o.pack_uint8(v.type);
//                 o.pack_uint16(v.msgid);

//                 // Depends on caller
//                 o.pack_nil();
//                 o.pack_nil();
//         }
// };

template <typename Result, typename Error>
struct pack<msg_response<Result, Error> > {
        msgpack::packer& operator()(msgpack::packer&o,
                                    const msg_response<Result, Error>& v)
        const {
                o.pack_array(4);

                // Standard for all response
                o.pack_uint8(v.type);
                o.pack_uint16(v.msgid);

                // Depends on caller
                o.pack(v.error);
                o.pack(v.result);
        }
};

#endif
