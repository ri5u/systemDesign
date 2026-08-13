#include <cstdint>
#include <iostream>
#include <string>

class UserSession{
private:
    std::string sessionId;
    uint64_t userId;
    int timeoutSeconds;
    bool isActive;

public:
    explicit UserSession(std::string sessionId) : sessionId(sessionId), userId(0), timeoutSeconds(3600), isActive(true) {};

    UserSession(std::string sessionId, uint64_t userId, int timeoutSeconds) : sessionId(sessionId), userId(userId), timeoutSeconds(timeoutSeconds) {};
    // UserSession(std::string sessionId, uint64_t userId, int timeoutSeconds) {
    //     this->sessionId = sessionId;
    //     this->userId = userId;
    //     this->timeoutSeconds = timeoutSeconds;
    //     this->isActive = true;
    // }
    
    UserSession(const UserSession&) = delete;
    UserSession& operator=(const UserSession&) = delete;

    ~UserSession(){
        if(isActive){
            isActive = false;
            std::cout << "[Session Terminated] Session " << sessionId << " for User " << userId << " closed." << std::endl;
        }
    }

    void extendSession(int additionalSeconds) {
        if(isActive){
            timeoutSeconds += additionalSeconds;
        }
    }

    void invalidate() {
        isActive = false;
        std::cout << "[Explicit Logout] Session " << sessionId << " invalidated" << std::endl;
    }

    bool isValid() const {
        return isActive;
    }

    std::string getSessionId() const {
        return sessionId;
    }
    
    uint64_t getUserId() const {
        return userId;
    }

    int getTimeoutSeconds() const {
        return timeoutSeconds;
    }
};

int main(void) {
    UserSession user("abc");
    std::cout << "User id: " << user.getUserId() << std::endl;
    std::cout << "Current Session id: " << user.getSessionId() << std::endl;
    std::cout << "Session timeouts in: " << user.getTimeoutSeconds() << std::endl;

    user.extendSession(20);
    std::cout << "Session time remaining after extension: " << user.getTimeoutSeconds() << std::endl;
    
    {
        UserSession tempSession("Sess_9999", 42, 3000);
        std::cout << "Inside block: Session is active." << std::endl;
    }
    // UserSession user2 = user;  //this works and fails to compile. We deleted the copy constructor so we can't copy an object to the other. 

}
