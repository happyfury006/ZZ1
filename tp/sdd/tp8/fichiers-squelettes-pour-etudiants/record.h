#ifndef RECORD_H
#define RECORD_H

typedef struct record {
	int variant;
	int limit;
	struct record * next;
} record;

typedef struct list {
	int length;
    record * head;
    record * tail;
} list;

list * listCreate();
int listSize(list * l);
void addRecord(list * l, int variant, int limit);
void listDisplay(list * l);
void listFree(list * l);
void listDestroy(list * l);

int veriTer(list * l);

#endif
