#include "ServerTest.h"

class Server {
public:
    Server(asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), io_context_(io_context) {
        start_accept();
    }

private:
    void start_accept() {
        auto socket = std::make_shared<tcp::socket>(io_context_);

        acceptor_.async_accept(*socket, [this, socket](const asio::error_code& error) {
            if (!error) {
                std::lock_guard<std::mutex> lock(client_mutex_);
                clients_.push_back(socket);
                std::cout << "Client connected! Total clients: " << clients_.size() << "\n";

                start_read(socket);
            }
            start_accept(); // Accept the next client
            });
    }

    void start_read(std::shared_ptr<tcp::socket> socket) {
        auto buffer = std::make_shared<std::vector<char>>(1024);

        socket->async_read_some(asio::buffer(*buffer),
            [this, socket, buffer](const asio::error_code& error, std::size_t length) {
                if (!error) {
                    std::string message(buffer->begin(), buffer->begin() + length);
                    std::cout << "Received: " << message << "\n";

                    // Process the message asynchronously
                    std::thread(&Server::process_request, this, socket, message).detach();

                    // Continue listening for more data
                    start_read(socket);
                }
            });
    }

    void process_request(std::shared_ptr<tcp::socket> socket, std::string message) {
        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Create response message
        std::string response = "Processed: " + message;

        // Broadcast result to all clients
        broadcast_message(response);
    }

    void broadcast_message(const std::string& message) {
        std::lock_guard<std::mutex> lock(client_mutex_);
        for (auto& client : clients_) {
            send_message(client, message);
        }
    }

    void send_message(std::shared_ptr<tcp::socket> socket, const std::string& message) {
        auto buffer = std::make_shared<std::string>(message);
        asio::async_write(*socket, asio::buffer(*buffer),
            [buffer](const asio::error_code& error, std::size_t /*length*/) {
                if (error) {
                    std::cerr << "Send failed: " << error.message() << "\n";
                }
            });
    }

    tcp::acceptor acceptor_;
    asio::io_context& io_context_;
    std::vector<std::shared_ptr<tcp::socket>> clients_;
    std::mutex client_mutex_;
};

int main() {
    try {
        asio::io_context io_context;
        Server server(io_context, 12345);

        // Run the server with multiple worker threads
        std::vector<std::thread> threads;
        for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads.emplace_back([&io_context]() { io_context.run(); });
        }

        for (auto& thread : threads) {
            thread.join();
        }

    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
