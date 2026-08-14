#include <iostream>
#include <string> 
#include <vector>

class IPaymentGateway {
    int somevalue;
public:
    IPaymentGateway(int some) : somevalue(some) {};
    virtual ~IPaymentGateway() = default;
    virtual bool processPayment(double amount) = 0;
    virtual std::string getGatewayName() const = 0;
};

class StripeGateway : public IPaymentGateway {
private:
    std::string apiKey;
public:
    explicit StripeGateway(std::string key) :IPaymentGateway(5),  apiKey(key) {};
    bool processPayment(double amount) override {
        std::cout << "[Stripe API KEY: " << apiKey << "]" << "Charged $" << amount << " successfully" << std::endl;;
        return true;
    }

    std::string getGatewayName() const override{
        return  "Stripe";
    }
};

class PayPalGateway : public IPaymentGateway {
private:
    std::string clientEmail;
public:
    explicit PayPalGateway(std::string email) :IPaymentGateway(5), clientEmail(email) {}

    bool processPayment(double amount) override {
        std::cout << "[PayPal Account: " << clientEmail << "]" << "Processed Payment of $" << amount << std::endl;
        return true;

    }

    std::string getGatewayName() const override {
        return "PayPal";
    }
};

int main(void) {
    IPaymentGateway gway(5);
    std::vector<IPaymentGateway*> gateways;
    gateways.push_back(new StripeGateway("sk_live_998877"));
    gateways.push_back(new PayPalGateway("user@domain.com"));
    for(auto gateway : gateways) {
        gateway->getGatewayName();
        gateway->processPayment(149.99);
    }

    for(auto gateway: gateways) {
        delete gateway;
    }
}
