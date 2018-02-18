#ifndef RPC_REQUEST_H__
#define RPC_REQUEST_H__

#include "protocol.h"

class request {
public:
        request(msgid_t id, msgpack::object method, msgpack::object params);

        msgpack::object method();
        msgpack::object params();

        template <typename Result>
        void result(Result res);

        void result_nil();

        template <typename Error>
        void error(Error err);

        template <typename Error, typename Result>
        void error(Error err, Result res);


private:
        template <typename Result, typename Error>
        void call(Result &res, Error &err);

        msgid_t m_msgid;

        msgpack::object m_method;
        msgpack::object m_params;
};

/*
    Pack response when function is called
*/

template <typename Result, typename Error>
void request::call(Result &res, Error &err) {
        msg_response<Result, Error> msgres(res, err, m_msgid);

        msgpack::packer packer;

        pack<msg_response<Result, Error> >()(packer, msgres);
}

/*
    Handles results of functions
*/

template <typename Result>
void request::result(Result res) {
        msgpack::type::nil_t err;

        call(res, err);
}


#endif
