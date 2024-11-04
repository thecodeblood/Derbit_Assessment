#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <set>
#include <string>

class WebSocketServer {
public:
    WebSocketServer();
    void run(uint16_t port);
    void sendMessage(const std::string& message);

private:
    typedef websocketpp::server<websocketpp::config::asio> server;
    server ws_server;
    std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections;

    void onOpen(websocketpp::connection_hdl hdl);
    void onClose(websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);
};

#endif
