#include "request.h"

/*
    Constructor
*/

request::request(msgid_t id, msgpack::object method, msgpack::object params)
        : m_msgid(id), m_method(method), m_params(params) { }

/*
    Request getters
*/

msgpack::object request::method()
{
        return m_method;
}

msgpack::object request::params()
{
        return m_params;
}

/*
    Handles results for functions with return type void
*/

void request::result_nil() {
        msgpack::type::nil_t res;
        msgpack::type::nil_t err;

        call(res, err);
}

/*
    Handles errors of functions
*/

template <typename Error>
void request::error(Error err) {
        msgpack::type::nil_t res;

        call(res, err);
}

template <typename Error, typename Result>
void request::error(Error err, Result res) {
        call(res, err);
}
