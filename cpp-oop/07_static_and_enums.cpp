#include <cstdint>
#include <iostream>
#include <string>

enum class HttpMethod : uint8_t {
    GET,
    POST, 
    PUT, 
    DELETE_REQ
};

enum class ResponseCode : uint16_t {
    OK = 200,
    BAD_REQUEST = 400,
    TOO_MANY_REQUESTS = 429,
    INTERNAL_ERROR = 500
};

class APIRequest {
private:
    inline static size_t totalRequestsCreated = 0;
    inline static size_t activeRequests = 0;

    uint64_t requestId;
    HttpMethod method;
    std::string endpoint;
    ResponseCode responseStatus;

public:
    APIRequest(HttpMethod method, std::string endpoint) : method(method), endpoint(endpoint), responseStatus(ResponseCode::OK) {
        requestId = ++totalRequestsCreated;
        ++activeRequests;
        std::cout << "[Request # " << requestId << " Started]" << endpoint << " | Active: " << activeRequests << std::endl;
    };

    ~APIRequest() {
        --activeRequests;
        std::cout << "[Request # " << requestId << " Finished] Completed with code " << static_cast<uint16_t>(responseStatus) << " | Active: " << activeRequests << std::endl;
    }

    void setResponseCode(ResponseCode code) {
        responseStatus = code;
    } 

    void loginDetails() const {
        std::cout << "Request ID: " << requestId << " | endpoint: " << endpoint << " | status: " << static_cast<uint16_t>(responseStatus) << std::endl;
    }

    static size_t getTotalRequestsCreated() {
        return totalRequestsCreated;
    }

    static size_t getActiveRequestCount() {
        return activeRequests;
    }
};

int main(void) {
    std::cout << "Size of APIRequest: " << sizeof(APIRequest) << std::endl;

    std::cout << "Initial active requests: " << APIRequest::getActiveRequestCount() << std::endl;
    std::cout << "Initial total requests: " << APIRequest::getTotalRequestsCreated() << std::endl;

    APIRequest req1(HttpMethod::POST, "/api/v1/auth"); 

    {
        APIRequest req2(HttpMethod::GET, "/api/v1/users");
        APIRequest req3(HttpMethod::PUT, "/api/v1/users/42");

        req3.setResponseCode(ResponseCode::BAD_REQUEST);

        std::cout << "Active Request Count: " << APIRequest::getActiveRequestCount() << std::endl;
    }

    std::cout << "Final Total Requests: " << APIRequest::getTotalRequestsCreated() << std::endl;
    std::cout << "Final Active Requests: " << APIRequest::getActiveRequestCount() << std::endl;
}

