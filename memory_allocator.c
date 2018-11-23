#include "memory_allocator.h"


struct MemoryAllocator{
    size_t m_size;
    void *memory_pointer;
};

MemoryAllocator* MemoryAllocator_init(void* memoryPool, size_t size){
    MemoryAllocator * ma = malloc(sizeof(MemoryAllocator));

    if(size%sizeof(size_t)==0)
        size -= size % size%sizeof(size_t);
    ma->m_size=size;
    ma->memory_pointer=memoryPool;
    return ma;
}

void* MemoryAllocator_allocate(MemoryAllocator* allocator, size_t size){
    return NULL;
}


int main(){
    return 0;
}