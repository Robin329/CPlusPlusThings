
#include "shm_comm.h"
int main() {
    sem_t sp;
    int retval;

    retval = sem_init(&sp, 1, 2);
    if (retval != 0) {
        perror("Couldn't initialize.");
        return -1;
    }
    retval = sem_trywait(&sp);
    printf("Did trywait. Returned %d>\n", retval);

    retval = sem_trywait(&sp);
    printf("Did trywait. Returned %d>\n", retval);

    retval = sem_trywait(&sp);
    printf("Did trywait. Returned %d>\n", retval);

    return 0;
}