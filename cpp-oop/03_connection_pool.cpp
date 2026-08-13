#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

class PooledConnection {
private:
    int connectionId;
    std::string dbName;
    bool inUse;

public:
    PooledConnection(int id, std::string db) : connectionId(id), dbName(db), inUse(false) {};

    int getId() const {
        return connectionId;
    }

    std::string getDbName() const {
        return dbName;
    }

    bool isBusy() const {
        return inUse;
    }

    void setbusy(bool status) {
        if(status == inUse) return;
        inUse = status;
    }

    void execute(const std::string& query) const {
        if(inUse) {
            std::cout << "Error!!! DB is busy" << std::endl;
            return;
        }
        std::cout << "[ " << connectionId << " @ " << dbName << " ] Executing: " << query << std::endl;
    }
};

class ConnectionPool {
private:
    std::string poolName;
    std::vector<PooledConnection*> connections;

public:
    ConnectionPool(std::string name, int poolSize, std::string dbName) : poolName(name) {
        connections.reserve(poolSize);

        for(int i = 1; i <= poolSize; i++){
            connections.push_back(new PooledConnection(i, dbName));
        }
    }

    ~ConnectionPool() {
        for(auto conn : connections) {
            delete conn;
        }
    }

    PooledConnection* acquireConnection() {
        for(auto& conn : connections) {
            if(!conn->isBusy()){
                conn->setbusy(true);
                return conn;
            }
        }

        std::cout << "[Pool " << poolName << "] No available connections!" << std::endl;
        return nullptr;
    }

    void releaseConnection(PooledConnection* conn){ 
        if(conn) {
            conn->setbusy(false);
            std::cout << "[Pool " << poolName << " ] Released Connection ID " << conn->getId() << std::endl;
        }
    }

    size_t getAvailableCount() const {
        size_t available = 0;
        for(auto& conn : connections) {
            if(!conn->isBusy()){
                available++;
            }
        }
        return available;
    }

    size_t getTotalCapacity() const {
        return connections.size();
    }
};

int main(void) {
    ConnectionPool pool1("cpool", 2, "production_db");
    PooledConnection* con1 = pool1.acquireConnection();
    con1->execute("Query 1 in pool1 using con1");
    PooledConnection* con2 = pool1.acquireConnection();
    con2->execute("Query 2 in pool1 using con2");
    
    pool1.releaseConnection(con1);
    PooledConnection* con3 = pool1.acquireConnection();
    con3->execute("Query 3 in pool1 using con3");
    delete con1;
    delete con2;
    delete con3;
}
