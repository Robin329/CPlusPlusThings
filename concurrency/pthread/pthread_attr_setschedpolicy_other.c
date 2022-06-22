#include "pthread_common.h"

int main(void) {
    int rc;
    struct params p;

    p.policy = SCHED_OTHER;
    p.priority = PRIORITY_OTHER;
    p.policy_label = "SCHED_OTHER";
    p.status = PTS_UNRESOLVED;
    rc = create_test_thread(&p);

    if (rc == PTS_PASS) printf("Test PASSED\n");

    return rc;
}
