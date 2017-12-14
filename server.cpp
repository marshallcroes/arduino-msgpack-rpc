#include "server.h"

void server::listen()
{
        detail::context ctx;

        if (Serial.available() > 0) {
                ctx.execute();

                on_message(ctx.data());
        }
}

void server::on_message(const msgpack::object& data)
{
        msg_rpc msg;
        convert<msg_rpc>()(data, msg);

        if (msg.type == REQUEST) {
                msg_request<msgpack::object, msgpack::object> req;
                convert<msg_request<msgpack::object, msgpack::object> >()(data, req);

                on_request(req.msgid, req.method, req.param);
        }

        if (msg.type == NOTIFY) {
                msg_notify<msgpack::object, msgpack::object> nty;
                convert<msg_notify<msgpack::object, msgpack::object> >()(data, nty);

                on_notify(nty.method, nty.param);
        }
}

void server::on_request(msgid_t msgid, msgpack::object method, msgpack::object params)
{
        char *str = (char *) malloc(sizeof(char) * method.via.str.size + 1);
        str[method.via.str.size] = '\0';
        memcpy(str, method.via.str.ptr, method.via.str.size);

        Serial.println(str);

        free(str);
}

void server::on_notify(msgpack::object method, msgpack::object params) {}

// void server::close() {}