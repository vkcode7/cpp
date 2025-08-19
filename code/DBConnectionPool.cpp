#include <iostream>
#include <queue>
#include <memory>
#include <mutex>

// Mock database connection
class DBConnection {
public:
    DBConnection(int id) : connId(id) {
        std::cout << "DBConnection " << connId << " created.\n";
    }
    ~DBConnection() {
        std::cout << "DBConnection " << connId << " destroyed.\n";
    }

    void executeQuery(const std::string& query) {
        std::cout << "Executing query on connection " << connId << ": " << query << "\n";
    }

private:
    int connId;
};

// Singleton DBConnectionPool without condition_variable
class DBConnectionPool {
public:
    static const int INITIAL_CONNECTIONS = 5;
    static const int MAX_CONNECTIONS = 20;

    static DBConnectionPool& getInstance() {
        static DBConnectionPool instance;
        return instance;
    }

    DBConnectionPool(const DBConnectionPool&) = delete;
    DBConnectionPool& operator=(const DBConnectionPool&) = delete;

    std::shared_ptr<DBConnection> acquireConnection() {
        std::lock_guard<std::mutex> lock(mtx);

        if (!connections.empty()) {
            auto conn = connections.front();
            connections.pop();
            return conn;
        }

        if (connCounter < MAX_CONNECTIONS) {
            return std::make_shared<DBConnection>(++connCounter);
        }

        // No connection available and max reached
        std::cout << "No available connections. Try again later.\n";
        return nullptr;
    }

    void releaseConnection(std::shared_ptr<DBConnection> conn) {
        std::lock_guard<std::mutex> lock(mtx);
        connections.push(conn);
    }

private:
    DBConnectionPool() {
        for (int i = 0; i < INITIAL_CONNECTIONS; i++) {
            connections.push(std::make_shared<DBConnection>(++connCounter));
        }
    }

    ~DBConnectionPool() = default;

    std::queue<std::shared_ptr<DBConnection>> connections;
    std::mutex mtx;
    int connCounter = 0;
};

// Example usage
int main() {
    auto& pool = DBConnectionPool::getInstance();

    for (int i = 0; i < 22; i++) {
        auto conn = pool.acquireConnection();
        if (conn) {
            conn->executeQuery("SELECT * FROM test");
            pool.releaseConnection(conn);
        }
    }

    return 0;
}
