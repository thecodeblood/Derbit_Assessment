#include "websocket_server.h"
#include <boost/bind/bind.hpp>
#include <boost/bind.hpp>
#include <iostream>
using namespace boost::placeholders;

WebSocketServer::WebSocketServer() {
    ws_server.init_asio();

    ws_server.set_open_handler(boost::bind(&WebSocketServer::onOpen, this, _1));
    ws_server.set_close_handler(boost::bind(&WebSocketServer::onClose, this, _1));
    ws_server.set_message_handler(boost::bind(&WebSocketServer::onMessage, this, _1, _2));
}

void WebSocketServer::run(uint16_t port) {
    ws_server.listen(port);
    ws_server.start_accept();
    ws_server.run();
}

void WebSocketServer::sendMessage(const std::string& message) {
    for (auto& conn : connections) {
        ws_server.send(conn, message, websocketpp::frame::opcode::text);
    }
}

void WebSocketServer::onOpen(websocketpp::connection_hdl hdl) {
    connections.insert(hdl);
}

void WebSocketServer::onClose(websocketpp::connection_hdl hdl) {
    connections.erase(hdl);
}

void WebSocketServer::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg) {
    std::cout << "Received message: " << msg->get_payload() << std::endl;
}
