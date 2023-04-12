#ifndef __BST_LIST_H__
#define __BST_LIST_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

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
 * Insert a new_ entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *new_, struct list_head *prev, struct list_head *next) {
    next->prev = new_;
    new_->next = next;
    new_->prev = prev;
    prev->next = new_;
}
/**
 * bst_list_add - add a new_ entry
 * @new_: new_ entry to be added
 * @head: list head to add it after
 *
 * Insert a new_ entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void bst_list_add(struct list_head *new_, struct list_head *head) {
    __list_add(new_, head, head->next);
}
/**
 * bst_list_add_tail - add a new_ entry
 * @new_: new_ entry to be added
 * @head: list head to add it before
 *
 * Insert a new_ entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void bst_list_add_tail(struct list_head *new_, struct list_head *head) {
    __list_add(new_, head->prev, head);
}
/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head *prev, struct list_head *next) {
    next->prev = prev;
    prev->next = next;
}
static inline void __list_del_entry(struct list_head *entry) {
    __list_del(entry->prev, entry->next);
}

/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
#define LIST_POISON1 NULL
#define LIST_POISON2 LIST_POISON1
static inline void bst_list_del(struct list_head *entry) {
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

/**
 * bst_list_del_rcu - deletes entry from list without re-initialization
 * @entry: the element to delete from the list.
 *
 * Note: bst_list_empty on entry does not return true after this,
 * the entry is in an undefined state. It is useful for RCU based
 * lockfree traversal.
 *
 * In particular, it means that we can not poison the forward
 * pointers that may still be used for walking the list.
 */
static inline void bst_list_del_rcu(struct list_head *entry) {
    __list_del(entry->prev, entry->next);
    entry->prev = LIST_POISON2;
}

/**
 * list_is_first -- tests whether @list is the first entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int bst_list_is_first(const struct list_head *list, const struct list_head *head) {
    return list->prev == head;
}

/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int bst_list_is_last(const struct list_head *list, const struct list_head *head) {
    return list->next == head;
}

/**
 * bst_list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static inline void bst_list_del_init(struct list_head *entry) {
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}

/**
 * bst_list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static inline void bst_list_move(struct list_head *list, struct list_head *head) {
    __list_del(list->prev, list->next);
    bst_list_add(list, head);
}

/**
 * bst_list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void bst_list_move_tail(struct list_head *list, struct list_head *head) {
    __list_del(list->prev, list->next);
    bst_list_add_tail(list, head);
}

/**
 * bst_list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int bst_list_empty(struct list_head *head) {
    return head->next == head;
}

static inline void __list_splice(struct list_head *list, struct list_head *head) {
    struct list_head *first = list->next;
    struct list_head *last = list->prev;
    struct list_head *at = head->next;

    first->prev = head;
    head->next = first;

    last->next = at;
    at->prev = last;
}

/**
 * bst_list_splice - join two lists
 * @list: the new_ list to add.
 * @head: the place to add it in the first list.
 */
static inline void bst_list_splice(struct list_head *list, struct list_head *head) {
    if (!bst_list_empty(list)) __list_splice(list, head);
}

/**
 * bst_list_splice_init - join two lists and reinitialise the emptied list.
 * @list: the new_ list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */
static inline void bst_list_splice_init(struct list_head *list, struct list_head *head) {
    if (!bst_list_empty(list)) {
        __list_splice(list, head);
        INIT_LIST_HEAD(list);
    }
}
/*
 * swap - swap value of @a and @b
 */
#define swap(a, b)             \
    do {                       \
        typeof(a) __tmp = (a); \
        (a) = (b);             \
        (b) = __tmp;           \
    } while (0)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member)                    \
    ({                                                     \
        const typeof(((type *)0)->member) *__mptr = (ptr); \
        (type *)((char *)__mptr - offsetof(type, member)); \
    })
/**
 * bst_list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define bst_list_entry(ptr, type, member) container_of(ptr, type, member)

/**
 * bst_list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define bst_list_for_each(pos, head) for (pos = (head)->next, (pos->next); pos != (head); pos = pos->next, (pos->next))

/**
 * __list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 *
 * This variant differs from bst_list_for_each() in that it's the
 * simplest possible list iteration code, no prefetching is done.
 * Use this for code that knows the list to be very short (empty
 * or 1 entry) most of the time.
 */
#define __list_for_each(pos, head) for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * bst_list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define bst_list_for_each_prev(pos, head) \
    for (pos = (head)->prev, (pos->prev); pos != (head); pos = pos->prev, (pos->prev))

/**
 * bst_list_for_each_safe	-	iterate over a list safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop counter.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define bst_list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

/**
 * bst_list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define bst_list_for_each_entry(pos, head, member)                                                             \
    for (pos = bst_list_entry((head)->next, typeof(*pos), member), (pos->member.next); &pos->member != (head); \
         pos = bst_list_entry(pos->member.next, typeof(*pos), member), (pos->member.next))

/**
 * bst_list_for_each_entry_reverse - iterate backwards over list of given type.
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define bst_list_for_each_entry_reverse(pos, head, member)                                                     \
    for (pos = bst_list_entry((head)->prev, typeof(*pos), member), (pos->member.prev); &pos->member != (head); \
         pos = bst_list_entry(pos->member.prev, typeof(*pos), member), (pos->member.prev))

/**
 * bst_list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop counter.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define bst_list_for_each_entry_safe(pos, n, head, member)          \
    for (pos = bst_list_entry((head)->next, typeof(*pos), member),  \
        n = bst_list_entry(pos->member.next, typeof(*pos), member); \
         &pos->member != (head); pos = n, n = bst_list_entry(n->member.next, typeof(*n), member))

#ifdef __cplusplus
}
#endif

#endif /* __BST_LIST_H__ */