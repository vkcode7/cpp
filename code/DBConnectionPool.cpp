
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

// Mock database connection class
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

// Singleton Connection Pool Class
class DBConnectionPool {
public:
    static const int INITIAL_CONNECTIONS = 5;
    static const int MAX_CONNECTIONS = 20;

    // Singleton accessor
    static DBConnectionPool& getInstance() {
        static DBConnectionPool instance;  // Meyers Singleton (thread-safe)
        return instance;
    }

    // Prevent copying
    DBConnectionPool(const DBConnectionPool&) = delete;
    DBConnectionPool& operator=(const DBConnectionPool&) = delete;

    std::shared_ptr<DBConnection> acquireConnection() {
        std::unique_lock<std::mutex> lock(mtx);

        if (connections.empty() && connCounter < MAX_CONNECTIONS) {
            // Create a new connection if under limit
            connections.push(std::make_shared<DBConnection>(++connCounter));
        }

        // Wait until a connection is available
        cond.wait(lock, [this]() { return !connections.empty(); });

        auto conn = connections.front();
        connections.pop();
        return conn;
    }

    void releaseConnection(std::shared_ptr<DBConnection> conn) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            connections.push(conn);
        }
        cond.notify_one();
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
    std::condition_variable cond;
    int connCounter = 0;
};

// Example usage
int main() {
    // Get singleton instance
    DBConnectionPool& pool = DBConnectionPool::getInstance();

    // Acquire a connection
    auto conn = pool.acquireConnection();
    conn->executeQuery("SELECT * FROM users");

    // Release it back
    pool.releaseConnection(conn);

    return 0;
}

