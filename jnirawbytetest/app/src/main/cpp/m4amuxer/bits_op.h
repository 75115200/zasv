/**
* Author: landerlyoung@gmail.com
* Date:   2016-09-02
* Time:   16:58
* Life with Passion, Code with Creativity.
*/
#pragma once


#include <stdint.h>
#include <limits.h>

typedef struct GetBitContext {
    const uint8_t *buffer, *buffer_end;
    int index;
    int size_in_bits;
    int size_in_bits_plus8;
} GetBitContext;

typedef struct PutBitContext {
    uint32_t bit_buf;
    int bit_left;
    uint8_t *buf, *buf_ptr, *buf_end;
    int size_in_bits;
} PutBitContext;

static inline int init_get_bits(GetBitContext *s, const uint8_t *buffer,
                                int bit_size)
{
    int buffer_size;
    int ret = 0;

    if (bit_size >= INT_MAX - 7 || bit_size < 0 || !buffer) {
        bit_size = 0;
        buffer = NULL;
        ret = -1;
    }

    buffer_size = (bit_size + 7) >> 3;

    s->buffer = buffer;
    s->size_in_bits = bit_size;
    s->size_in_bits_plus8 = bit_size + 8;
    s->buffer_end = buffer + buffer_size;
    s->index = 0;

    return ret;
}

static inline unsigned int get_bits_long(GetBitContext *s, int n)
{
    return 0;
}

static inline void skip_bits_long(GetBitContext *s, int n)
{
    s->index += n;
}

static inline int get_bits_count(const GetBitContext *s)
{
    return s->index;
}

static inline unsigned int get_bits(GetBitContext *s, int n)
{

}

static inline int get_bits_left(GetBitContext *gb)
{
    return gb->size_in_bits - get_bits_count(gb);
}

static inline unsigned int show_bits(GetBitContext *s, int n)
{

}
