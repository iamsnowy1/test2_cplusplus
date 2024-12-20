#include <iostream>
#include <windows.h>

int main() {
    // Size of memory to allocate (1 page - usually 4 KB)
    const size_t size = 4096;

    // Allocating memory using VirtualAlloc
    void* allocatedMemory = VirtualAlloc(
        nullptr, // Address. nullptr - choose any available address
        size,    // Size of memory
        MEM_COMMIT | MEM_RESERVE, // Allocation type
        PAGE_READWRITE // Access to memory
    );

    if (!allocatedMemory) {
        std::cerr << "Error: failed to allocate memory. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Memory successfully allocated at address: " << allocatedMemory << std::endl;

    // Filling memory with data
    char* data = static_cast<char*>(allocatedMemory);
    for (size_t i = 0; i < size; ++i) {
        data[i] = static_cast<char>(i % 256); // Write bytes from 0 to 255 cyclically
    }

    // Validating the data
    bool dataValid = true;
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != static_cast<char>(i % 256)) {
            dataValid = false;
            std::cerr << "Error: invalid data at index " << i << std::endl;
            break;
        }
    }

    if (dataValid) {
        std::cout << "Data successfully written and verified." << std::endl;
    }

    // Freeing memory using VirtualFree
    if (!VirtualFree(allocatedMemory, 0, MEM_RELEASE)) {
        std::cerr << "Error: failed to free memory. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Memory successfully freed." << std::endl;
    return 0;
}