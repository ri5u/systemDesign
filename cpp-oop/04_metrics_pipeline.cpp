#include <cstdint>
#include <iostream>
#include <string>

class Metric{
protected:
    std::string metricName;
    std::string metricUnit;

public:
    Metric(std::string name, std::string unit) : metricName(name), metricUnit(unit) {
        std::cout << "[Base Constructor] Metric initialized: " << metricName << std::endl;
    }

    ~Metric() {
        std::cout << "[Base Destructor] Metric destroyed: " << metricName << std::endl;
    }

    std::string getName() const {
        return metricName;
    }

    std::string getUnit() const {
        return metricUnit;
    }
};

class CounterMetric : public Metric {
private:
    uint64_t count;
public:
    CounterMetric(std::string name, std::string unit) : Metric(name, unit), count(0) {
        std::cout << "[Derived Constructor] CounterMetric created" << std::endl;
    }

    ~CounterMetric() {
        std::cout << "[Derived Destructor] CounterMetric destroyed" << std::endl;
    }

    void increment(uint64_t value = 1) {
        count += value;
    }

    uint64_t getValue() const {
        return count;
    }

    void printMetric() const {
        std::cout << "[COUNTER] " << metricName << ": " << count << " " << metricUnit << std::endl;
    }
};

class GaugeMetric : public Metric {
private:
    double currentLevel;

public: 
    GaugeMetric(std::string name, std::string unit, double initialLvel = 0.0) : Metric(name, unit), currentLevel(initialLvel) {
        std::cout << "[Derived Constructor] GaugeMetric created" << std::endl;
    }

    ~GaugeMetric() {
        std::cout << "[Derived Destructor] GaugeMetric destroyed" << std::endl;
    }
    
    void update(double value) {
        currentLevel = value;
    }

    double getValue() const {
        return currentLevel;
    }

    void printMetric() const {
        std::cout << "[GAUGE] " << metricName << ": " << currentLevel << " " << metricUnit << std::endl;
    }
};


int main(void){
    CounterMetric c_metric("http_requests_total", "requests");
    c_metric.increment();
    c_metric.increment(5);
    c_metric.printMetric();

    {
        GaugeMetric g_metric("memory_usage", "MB");
        g_metric.update(512.5);
        g_metric.printMetric();
    }

}
