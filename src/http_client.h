#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

class HttpClient {
public:
    HttpClient(const std::string& api_key);
    ~HttpClient();

    std::string placeOrder(const std::string& instrument, int amount, const std::string& type, double price);
    std::string cancelOrder(const std::string& order_id);
    std::string modifyOrder(const std::string& order_id, double new_price);
    std::string getOrderBook(const std::string& instrument);
    std::string viewCurrentPositions();

private:
    std::string apiKey;
    std::string makeRequest(const std::string& endpoint, const std::string& data);
};

#endif
