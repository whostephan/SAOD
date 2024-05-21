#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec;
    size_t old_capacity = vec.capacity();
    for (int i = 0; i < 32; ++i) {
        vec.push_back(1);
        if (vec.capacity() != old_capacity) {
            old_capacity = vec.capacity();
            std::cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;
        }
    }
    return 0;
}
