#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, void *argv[]) {
	printf("Testing Malloc \n");
	
	void *ptr = malloc(-1); // malloc -1 bytes
	
	if (!ptr) {
		printf("Malloc error for -1 bytes \n");
	}

	ptr = malloc(0);

	if (!ptr) {
		printf("Malloc error for 0 bytes \n");
	}
	
	// Test out max malloc size
	// for large malloc sizes, limit is usually physical
    // otherwise, we can potentially page in/out(memory swapping) into disk(swap space) to free up more space in memory
	int size = 1000;
	for (;;) {
		ptr = malloc(size);
		if (!ptr) {
			printf("Can not malloc size %d \n", size);
		}
		free(ptr);
		size += 100;
	}
	
	return 0;
}
