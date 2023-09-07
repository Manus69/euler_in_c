#include "Deck.h"
#include "mem.h"
#include <string.h>

#define DECK_DC 1 << 4

Deck Deck_new_capacity(i64 capacity, i64 item_size)
{
    return (Deck)
    {
        .data = mem_alloc0(capacity * item_size),
        .item_size = item_size,
        .idx = capacity / 2,
        .len = 0,
        .capacity = capacity,
    };
}

Deck Deck_new_item_size(i64 item_size)
{
    return Deck_new_capacity(DECK_DC, item_size);
}

void Deck_del(Deck * deck)
{
    mem_del(deck->data);
    to0(deck, Deck);
}

i64 Deck_item_size(Deck deck)
{
    return deck.item_size;
}

i64 Deck_len(Deck deck)
{
    return deck.len;
}

i64 Deck_size_allocated(Deck deck)
{
    return deck.capacity * deck.item_size;
}

i64 Deck_size_data(Deck deck)
{
    return deck.len * deck.item_size;
}

i64 Deck_capacity_left(Deck deck)
{
    return deck.idx;
}

i64 Deck_capacity_right(Deck deck)
{
    return deck.capacity - (deck.idx + deck.len + 1);
}

void * Deck_get(Deck deck, i64 idx)
{
    return deck.data + (deck.idx + idx + 1) * deck.item_size;
}

void * Deck_first(Deck deck)
{
    return Deck_get(deck, 0);
}

void * Deck_last(Deck deck)
{
    return Deck_get(deck, Deck_len(deck) - 1);
}

void * Deck_pop_right(Deck * deck)
{
    return Deck_get(* deck, -- deck->len);
}

void * Deck_pop_left(Deck * deck)
{
    void * ptr;

    ptr = Deck_first(* deck);
    deck->idx ++;

    return ptr;
}

void Deck_extend_right(Deck * deck, i64 len)
{
    mem_extend(& deck->data, Deck_size_allocated(* deck), len * deck->item_size);
    deck->capacity += len;
}

void Deck_extend_left(Deck * deck, i64 len)
{
    Deck_extend_right(deck, len);
    memmove(Deck_get(* deck, len), Deck_get(* deck, 0), Deck_size_data(* deck));
    deck->idx += len;
}

void Deck_double_right(Deck * deck)
{
    Deck_extend_right(deck, deck->len);
}

void Deck_double_left(Deck * deck)
{
    Deck_extend_left(deck, deck->len);
}

View Deck_view(Deck deck, i64 idx, i64 len)
{
    return View_init(Deck_get(deck, idx), deck.item_size, len);
}

View Deck_to_View(Deck deck)
{
    return Deck_view(deck, 0, deck.len);
}

void Deck_map(Deck deck, F f)
{
    View_map(Deck_to_View(deck), f);
}