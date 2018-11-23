#include "memory_allocator.h"


struct MemoryAllocator{
    size_t m_size;
    void *m_memory_pointer;
};

MemoryAllocator* MemoryAllocator_init(void* memoryPool, size_t size){
    MemoryAllocator * ma = malloc(sizeof(MemoryAllocator));

    if(size%sizeof(size_t)==0)
        size -= size % size%sizeof(size_t);

    ma->m_size=size;
    ma->m_memory_pointer=memoryPool;
    *((size_t*)ma->m_memory_pointer)=0

    return ma;
}

void* MemoryAllocator_allocate(MemoryAllocator* allocator, size_t size){
    int i;
    size_t m_size=allocator->m_size;

    for(i=0; i <allocator->m_size; i++){


    }
    return NULL;
}


int main(){
    return 0;
}