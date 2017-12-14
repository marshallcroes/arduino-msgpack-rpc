#include "request.h"

template <typename Result, typename Error>
void request::call(Result &res, Error &err) {
        // msgpack::sbuffer sbuf;
        msg_response<Result &, Error> msgres(res, err, get_msgid());
        // msgpack::pack(sbuf, msgres);

        send_data(&sbuf);
}

template <typename Result>
void request::result(Result res) {
        msgpack::type::nil_t err;
        call(res, err);
}

template <typename Result>
void request::result_nil() {
        msgpack::type::nil_t res;
        msgpack::type::nil_t err;
        call(res, err);
}

template <typename Error>
void request::error(Error err) {
        msgpack::type::nil_t res;
        call(res, err);
}

template <typename Error, typename Result>
void request::error(Error err, Result res) {
        call(res, err);
}
