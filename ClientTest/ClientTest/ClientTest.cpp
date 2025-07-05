#include "ClientTest.h"


using asio::ip::tcp;

class Client {
public:
    Client(asio::io_context& io_context, const std::string& host, short port)
        : socket_(io_context) {
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        asio::async_connect(socket_, endpoints,
            [this](const asio::error_code& error, const tcp::endpoint&) {
                if (!error) {
                    std::cout << "Connected to server!\n";
                    start_read();
                    start_write();
                }
            });
    }

private:
    void start_read() {
        auto buffer = std::make_shared<std::vector<char>>(1024);
        socket_.async_read_some(asio::buffer(*buffer),
            [this, buffer](const asio::error_code& error, std::size_t length) {
                if (!error) {
                    std::cout << "Server: " << std::string(buffer->begin(), buffer->begin() + length) << "\n";
                    start_read();
                }
            });
    }

    void start_write() {
        std::thread input_thread([this]() {
            std::string message;
            while (std::getline(std::cin, message)) {
                auto buffer = std::make_shared<std::string>(message);
                asio::async_write(socket_, asio::buffer(*buffer),
                    [buffer](const asio::error_code& error, std::size_t /*length*/) {
                        if (error) {
                            std::cerr << "Send failed: " << error.message() << "\n";
                        }
                    });
            }
            });
        input_thread.detach();
    }

    tcp::socket socket_;
};

int main() {
    try {
        asio::io_context io_context;
        Client client(io_context, "127.0.0.1", 12345);

        io_context.run(); // Run the async handlers

    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}