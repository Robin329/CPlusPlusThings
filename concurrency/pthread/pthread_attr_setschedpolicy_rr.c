#include "pthread_common.h"

int main(void) {
    int rc;
    struct params p;

    p.policy = SCHED_RR;
    p.priority = PRIORITY_RR;
    p.policy_label = "SCHED_RR";
    p.status = PTS_UNRESOLVED;
    rc = create_test_thread(&p);

    if (rc == PTS_PASS) printf("Test PASSED\n");

    return rc;
}
