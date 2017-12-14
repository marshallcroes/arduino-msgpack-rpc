#ifndef RPC_REQUEST_H__
#define RPC_REQUEST_H__

#include "protocol.h"

class request {
public:
        msgpack::object method();
        msgpack::object params();

        template <typename Result>
        void result(Result res);

        void result_nil();

        template <typename Error>
        void error(Error err);

        template <typename Error, typename Result>
        void error(Error err, Result res);

        template <typename Result>
        class type;

private:
        template <typename Result, typename Error>
        void call(Result &res, Error &err);

        uint32_t get_msgid() const;
        // void send_data(msgpack::sbuffer *buff);
};

template <typename Result>
class request::type : public request {
public:
        type(const request &req) : request(req) {  }

        void result(Result res) { request::result(res); }
};

template <>
class request::type<void> : public request {
public:
        type(const request &req) : request(req) {  }

        void result() { request::result_nil(); }
};

#endif
