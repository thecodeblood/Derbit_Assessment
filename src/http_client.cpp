#include "http_client.h"
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <json/json.h>

HttpClient::HttpClient(const std::string& api_key) : apiKey(api_key) {}

HttpClient::~HttpClient() {}

std::string HttpClient::makeRequest(const std::string& endpoint, const std::string& data) {
    httplib::Client cli("https://test.deribit.com");
    httplib::Headers headers = { {"Authorization", "Bearer " + apiKey} };
    
    auto res = cli.Post(endpoint.c_str(), headers, data, "application/json");
    if (res && res->status == 200) {
        return res->body;
    } else {
        return "Error: " + std::to_string(res->status);
    }
}

std::string HttpClient::placeOrder(const std::string& instrument, int amount, const std::string& type, double price) {
    Json::Value json_data;
    json_data["instrument_name"] = instrument;
    json_data["amount"] = amount;
    json_data["type"] = type;
    json_data["price"] = price;

    Json::StreamWriterBuilder writer;
    std::string request = Json::writeString(writer, json_data);
    return makeRequest("/api/v2/private/buy", request);
}

std::string HttpClient::cancelOrder(const std::string& order_id) {
    Json::Value json_data;
    json_data["order_id"] = order_id;

    Json::StreamWriterBuilder writer;
    std::string request = Json::writeString(writer, json_data);
    return makeRequest("/api/v2/private/cancel", request);
}

std::string HttpClient::modifyOrder(const std::string& order_id, double new_price) {
    Json::Value json_data;
    json_data["order_id"] = order_id;
    json_data["price"] = new_price;

    Json::StreamWriterBuilder writer;
    std::string request = Json::writeString(writer, json_data);
    return makeRequest("/api/v2/private/edit", request);
}

std::string HttpClient::getOrderBook(const std::string& instrument) {
    httplib::Client cli("https://test.deribit.com");
    auto res = cli.Get(("/api/v2/public/get_order_book?instrument_name=" + instrument).c_str());
    return res->body;
}

std::string HttpClient::viewCurrentPositions() {
    httplib::Client cli("https://test.deribit.com");
    httplib::Headers headers = { {"Authorization", "Bearer " + apiKey} };

    auto res = cli.Get("/api/v2/private/get_positions", headers);
    return res->body;
}
