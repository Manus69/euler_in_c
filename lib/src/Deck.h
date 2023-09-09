#ifndef DECK_H
#define DECK_H

#include "def.h"
#include "View.h"

typedef struct Deck Deck;

struct Deck
{
    void *  data;
    i64     item_size;
    i64     idx;
    i64     len;
    i64     capacity;
};

#define Deck_new(type) Deck_new_item_size(sizeof(type))
#define Deck_set(deck, idx, item, type) (deref(type) Deck_get(deck, idx) = item)

#define Deck_push_right(deck_ptr, item, type) \
{ \
    if (unlikely(Deck_capacity_right(* deck_ptr) == 0)) Deck_double_right(deck_ptr); \
    Deck_set(* deck_ptr, (deck_ptr)->len ++, item, type); \
}

#define Deck_push_left(deck_ptr, item, type) \
{ \
    if (unlikely(Deck_capacity_left(* deck_ptr) == 0)) Deck_double_left(deck_ptr); \
    (deck_ptr)->idx --; \
    (deck_ptr)->len ++; \
    Deck_set(* deck_ptr, 0, item, type); \
}

Deck    Deck_own(void * data, i64 item_size, i64 idx, i64 len, i64 capacity);
Deck    Deck_new_capacity(i64 capacity, i64 item_size);
Deck    Deck_new_item_size(i64 item_size);
void    Deck_del(Deck * deck);
i64     Deck_item_size(Deck deck);
i64     Deck_len(Deck deck);
bool    Deck_empty(Deck deck);
i64     Deck_size_allocated(Deck deck);
i64     Deck_size_data(Deck deck);
i64     Deck_capacity_left(Deck deck);
i64     Deck_capacity_right(Deck deck);
void *  Deck_get(Deck deck, i64 idx);
void *  Deck_first(Deck deck);
void *  Deck_last(Deck deck);
void *  Deck_pop_right(Deck * deck);
void *  Deck_pop_left(Deck * deck);
void    Deck_extend_right(Deck * deck, i64 len);
void    Deck_extend_left(Deck * deck, i64 len);
void    Deck_double_right(Deck * deck);
void    Deck_double_left(Deck * deck);
void    Deck_reserve_right(Deck * deck, i64 len);
void    Deck_reserve_right_agro(Deck * deck, i64 len);
void    Deck_right_buffer_memset0(Deck deck);
View    Deck_view(Deck deck, i64 idx, i64 len);
View    Deck_to_View(Deck deck);
void    Deck_map(Deck deck, F f);

#endif