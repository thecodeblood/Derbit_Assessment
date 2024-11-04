#include "httplib.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <json/json.h>

void placeOrder() {
    httplib::Client cli("https://test.deribit.com");
    httplib::Headers headers = { {"Authorization", "Bearer YOUR_API_KEY"} };
    Json::Value json_data;
    json_data["instrument_name"] = "BTC-PERPETUAL";
    json_data["amount"] = 1;
    json_data["type"] = "limit";
    json_data["price"] = 30000;

    Json::StreamWriterBuilder writer;
    std::string request = Json::writeString(writer, json_data);
    auto res = cli.Post("/api/v2/private/buy", headers, request, "application/json");

    if (res && res->status == 200) {
        std::cout << "Order placed successfully!" << std::endl;
    } else {
        std::cout << "Failed to place order." << std::endl;
    }
}
void cancelOrder(const std::string& order_id) {
    httplib::Client cli("https://test.deribit.com");
    httplib::Headers headers = { {"Authorization", "Bearer YOUR_API_KEY"} };

    Json::Value json_data;
    json_data["order_id"] = order_id;

    Json::StreamWriterBuilder writer;
    std::string request = Json::writeString(writer, json_data);
    auto res = cli.Post("/api/v2/private/cancel", headers, request, "application/json");

    if (res && res->status == 200) {
        std::cout << "Order canceled successfully!" << std::endl;
    } else {
        std::cout << "Failed to cancel order." << std::endl;
    }
}
void modifyOrder(const std::string& order_id, double new_price) {
    httplib::Client cli("https://test.deribit.com");
    httplib::Headers headers = { {"Authorization", "Bearer YOUR_API_KEY"} };

    Json::Value json_data;
    json_data["order_id"] = order_id;
    json_data["price"] = new_price;

    Json::StreamWriterBuilder writer;
    std::string request = Json::writeString(writer, json_data);
    auto res = cli.Post("/api/v2/private/edit", headers, request, "application/json");

    if (res && res->status == 200) {
        std::cout << "Order modified successfully!" << std::endl;
    } else {
        std::cout << "Failed to modify order." << std::endl;
    }
}
