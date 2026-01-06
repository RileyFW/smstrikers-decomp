#ifndef _VM_H_
#define _VM_H_

#include <stdint.h>  // for uintptr_t
#include <stddef.h>  // for size_t

void VMInit(uintptr_t baseAddr, size_t initialCommitSize, uintptr_t limitAddr);
void VMAlloc(uintptr_t address, size_t size);

#endif // _VM_H_
