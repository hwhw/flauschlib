#include "fifo.h"
#include <stdlib.h> // for malloc()

void fifo_init(fifo_t* fifo, const int size) {
        fifo->buf = malloc(size);
        fifo->head = fifo->buf;
        fifo->tail = fifo->buf;
        fifo->size = size;
}

void fifo_push(fifo_t* fifo, const char data) {
	register char* target = fifo->head;
        *target = data;
	target++;
	if(target == fifo->buf + fifo->size) {
		target = fifo->buf;
	}
	fifo->head = target;
}

char fifo_pop(fifo_t* fifo) {
	register char value = *(fifo->tail);
	fifo->tail++;
	if(fifo->tail == fifo->buf + fifo->size) {
		fifo->tail = fifo->buf;
	}
        return value;
}

int fifo_has_data(const fifo_t* fifo) {
	return (fifo->head != fifo->tail);
}
