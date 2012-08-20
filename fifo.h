#ifndef _FLAUSCH_FIFO_H
#define _FLAUSCH_FIFO_H

typedef struct {
        char *buf;
        volatile char *head;
        volatile char *tail;
        int size;
} fifo_t;

void fifo_init(fifo_t* fifo, const int size);
void fifo_push(fifo_t* fifo, const char data);
char fifo_pop(fifo_t* fifo);

int fifo_has_data(const fifo_t* fifo);

#endif // _FLAUSCH_FIFO_H
