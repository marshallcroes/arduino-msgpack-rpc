#ifndef RPC_SERVER_H__
#define RPC_SERVER_H__

// #include "request.h"
#include "context.h"
#include "object.h"
#include "protocol.h"
#include "dispatch.h"

// using msgpack::object;

// class dispatcher {
// public:
//         virtual void dispatch(request req) = 0;
// };

class server {
public:
        void listen();

        void on_message(const msgpack::object& data);
        void on_request(msgid_t msgid, msgpack::object method, msgpack::object params);
        void on_notify(msgpack::object method, msgpack::object params);

        // void close();

        // class base;

private:
        dispatcher m_dp;
};

// class server::base : public dispatcher {
// public:
//         base() : instance() {
//                 instance.serve(this);
//         }

//         server instance;
// };

#endif
