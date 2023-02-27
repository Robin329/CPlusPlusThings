#include <stdio.h>

struct list_head {
    struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) \
    { &(name), &(name) }

#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

/**
 * INIT_LIST_HEAD - Initialize a list_head structure
 * @list: list_head structure to be initialized.
 *
 * Initializes the list_head to point to itself.  If it is a list header,
 * the result is an empty list.
 */

static inline void INIT_LIST_HEAD(struct list_head *list) {
    list->next = list;
    list->prev = list;
}
/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next) {
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}
/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add(struct list_head *new, struct list_head *head) {
    __list_add(new, head, head->next);
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_head *new, struct list_head *head) {
    __list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head *prev, struct list_head *next) {
    next->prev = prev;
    prev->next = next;
}

static inline void __list_del_entry(struct list_head *entry) {
    __list_del(entry->prev, entry->next);
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
static inline void list_del(struct list_head *entry) {
    __list_del_entry(entry);
    entry->next = NULL;
    entry->prev = NULL;
}
typedef struct {
    int               data;
    struct list_head *list;
} list_test;

typedef struct {
    char              data;
    struct list_head *list;
} list_test_add;

static LIST_HEAD(foo_list);

int main(void) {
    list_test *    test = (struct list_test *)malloc(sizeof(list_test));
    list_test_add *test_add = (struct list_test_add *)malloc(sizeof(list_test_add));
    test->data = 0;
    INIT_LIST_HEAD(test->list);
    list_add(test->list, &foo_list);
    list_add_tail(test->list, test_add->list);
    printf("hello, world!!\n");
    if (test) free(test);
    if (test_add) free(test_add);
    return 0;
}