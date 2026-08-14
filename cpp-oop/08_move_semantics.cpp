#include <iostream>
#include <string>

class PacketBuffer {
private:
    size_t capacity;
    int* data;
    std::string label;
public:
    PacketBuffer(std::string name, size_t cap) : label(name), capacity(cap) {
        data = new int[cap];
        std::cout << "[Constructor] Create Buffer '" << label << "' with capacity " << cap << std::endl;

    }

    ~PacketBuffer() {
        std::cout << "[Destructor] Destroying Buffer '" << label << "' (Data ptr: " << static_cast<void*>(data) << std::endl;
        delete[] data;
    }

    PacketBuffer(const PacketBuffer& other) {
        data = new int[other.capacity];
        std::cout << "[Copy Constructor] DEEP COPY from '" << other.label << "' to '" << label << "' (Expensive)" << std::endl;
    }

    PacketBuffer(PacketBuffer&& other) noexcept : data(other.data), capacity(other.capacity) {
        other.data = nullptr;
        other.capacity = 0;
        std::cout << "[Move Constructor] STOLE resources from '" << other.label << "' (Fast)\n";
    }

    PacketBuffer& operator=(PacketBuffer&& other) noexcept {
        if(this != &other) {
            delete[] data;

            data = other.data;
            capacity = other.capacity;
            label = other.label;

            other.data = nullptr;
            other.capacity = 0;

            std::cout << "[Move Assignment] STOLE resources via operator= from '" << other.label << "'\n";
        }

        return *this;
    }
};

int main() {
    PacketBuffer buf1("Buffer1", 100);

    PacketBuffer buf2 = std::move(buf1);
    PacketBuffer buf3("Buffer3", 50);

    buf3 = std::move(buf2);
}
