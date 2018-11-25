#include "memory_allocator.h"
#define AVAILABLE 0
#define OCCUPIED 1
#define MANAGER sizeof(size_t)

struct MemoryAllocator{
    size_t m_size;
    void *m_memory_ptr;
};

MemoryAllocator* MemoryAllocator_init(void* memoryPool, size_t size)
{
    
    MemoryAllocator * ma = malloc(sizeof(MemoryAllocator));

    if(size%sizeof(size_t)==0)
        size -= size % size%sizeof(size_t);

    ma->m_size=size;
    ma->m_memory_ptr=memoryPool;
    *((size_t*)ma->m_memory_ptr)=size-MANAGER;

    return ma;
}

void* MemoryAllocator_allocate(MemoryAllocator* allocator, size_t size)
{
    /* iterates on block managers */
    void* current_block = allocator->m_memory_ptr;
    /*size of the current block*/
    size_t index;
    size_t *end_of_allocator = (size_t*)current_block + allocator->m_size;

    /*align size to sizeof size_t */
    while(size++ % sizeof(size_t)){}

    while(current_block != end_of_allocator)
    {
        /*if current block is available*/
        if((*((size_t*)current_block) & AVAILABLE)==AVAILABLE)
        {
            /*if current block size fits*/
            if(*((size_t*)current_block - AVAILABLE) >= size)
            {
                if(*((size_t*)current_block - AVAILABLE) > size )
                    *(((size_t*)current_block) + size + MANAGER ) = *((size_t*)current_block) - size - MANAGER;

                *(((size_t*)current_block)) = size + OCCUPIED;
                return current_block;
            }

                /*combine with the next block*/
            else if((*((size_t*)current_block + *((size_t*)current_block) + MANAGER ) & AVAILABLE)==AVAILABLE)
                *((size_t*)current_block) += *((size_t*)current_block + *((size_t*)current_block) + MANAGER) -AVAILABLE ;
        }
        else
        {
            /*if not available goes to the next block*/
            index = *((size_t*)current_block) + MANAGER;
            current_block = index +(size_t*)current_block ;
        }
    }
    return NULL;
}

/* Return number of still allocated blocks */
size_t MemoryAllocator_free(MemoryAllocator* allocator, void* ptr){

    void* current_block = allocator->m_memory_ptr;
    size_t allocated_blocks = 0;
    size_t *end_of_allocator = (size_t*)current_block + allocator->m_size;

    *(size_t*)ptr -= OCCUPIED;

    while(current_block != end_of_allocator)
    {
        if(*((size_t*)current_block) & OCCUPIED)
            allocated_blocks += 1;

        current_block = *((size_t*)current_block) + MANAGER + (size_t*)current_block;

    }

    return allocated_blocks;

}

int main(){
    return 0;
}