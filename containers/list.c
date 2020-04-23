#include "list.h"

#include <stdlib.h>

struct node{
	struct node *next;
	struct node *prev;
	void *data;
};

struct list{

	struct node *first;
	struct node *current;
	struct node *last;

	unsigned int size;
	unsigned int pos;
};


/* ========================== */
/* Static Function Definition */
/* ========================== */

static int set_pos(struct list *list, unsigned int pos){

	if(pos > list->size) return -1;

	struct node *n;
	unsigned int i;

	if(pos == 0)
		list->current = list->first;

	else if(pos == list->size - 1)
			list->current = list->last;

	/* Fast +1 and -1 getters */
	else if(list->pos == pos - 1)
		list->current = list->current->next;

	else if(list->pos - 1 == pos)
		list->current = list->current->prev;

	else if(pos < list->pos){

		if(list->pos - pos < pos + 0){
			n = list->current;

			for(i = list->pos; i > pos; i -= 1) n = n->prev;
			list->current = n;
		}
		else{
			n = list->first;

			for(i = 0; i < pos; i += 1) n = n->next;
			list->current = n;
		}

	}
	else if(pos > list->pos){

		if(pos - list->pos < list->size - pos){
			n = list->current;

			for(i = list->pos; i < pos; i += 1) n = n->next;
			list->current = n;
		}
		else{
			n = list->last;

			for(i = list->size - 1; i > pos; i -= 1) n = n->prev;
			list->current = n;
		}
	}
	else return -69;	//impossible state

	list->pos = pos;

	return 0;
}

/* ============================= */
/* Interface Function Definition */
/* ============================= */

extern int list_create(struct list **list){

	if(!list) return -1;

	*list = malloc(sizeof(**list));
	if(!(*list)) return -2;

	(*list)->first = NULL;
	(*list)->current = NULL;
	(*list)->last = NULL;

	(*list)->pos = 0;
	(*list)->size = 0;

	return 0;
}


extern void list_destroy(struct list **list){

	if(!list) return;
	if(!(*list)) return;

	struct node *n = (*list)->first;
	struct node *t;

	while(n){
		t = n->next;
		free(n);
		n = t;
	}

	free(*list);
	*list = NULL;
}


extern unsigned int list_get_size(struct list *list){
	return list ? list->size : 0;
}


extern void* list_get_data(struct list *list, unsigned int pos){
	return set_pos(list, pos) ? NULL : list->current->data;
}


extern int list_prepend(struct list *list, void *data){

	if(!list || !data) return -1;

	/* Node creation and insertion */
	struct node *new_node = malloc(sizeof(*new_node));
	if(!new_node) return -2;

	new_node->data = data;
	new_node->next = list->first;

	if(!list->last) list->last = new_node;
	if(list->first) list->first->prev = new_node;
	new_node->prev = NULL;

	list->first = new_node;

	list->size += 1;

	/* Modify position */
	if(list->pos == 0) list->current = new_node;

	return 0;
}


extern int list_append(struct list *list, void *data){

	if(!list || !data) return -1;

	/* Node creation and insertion */
	struct node *new_node = malloc(sizeof(*new_node));
	if(!new_node) return -2;

	new_node->next = NULL;
	new_node->data = data;

	if(list->last)
		list->last->next = new_node;
	else
		list->first = new_node;

	new_node->prev = list->last;
	list->last = new_node;

	list->size += 1;

	return 0;
}


extern int list_insert(struct list *list, unsigned int pos, void *data){

	if(!list || !data) return -1;

	if(pos == 0) return list_prepend(list, data);
	else if(pos < list->size){

		if(pos == list->size - 1) return list_append(list, data);

		/* Node creation */
		struct node *new_node = malloc(sizeof(*new_node));
		if(!new_node) return -2;

		new_node->data = data;

		if(set_pos(list, pos)) return -3;

		new_node->next = list->current;
		new_node->prev = list->current->prev;
		list->current->prev->next = new_node;
		list->current->prev = new_node;

		list->current = new_node;
		list->size += 1;
	}
	return 0;
}


extern int list_remove(struct list *list, unsigned int pos, void **data){

	if(!list) return -1;

	if(set_pos(list,pos)){
		if(data) *data = NULL;
		return -2;
	}

	struct node *n = list->current;

	if(data) *data = n->data;

	if(n->prev) n->prev->next = n->next;
	if(n->next) n->next->prev = n->prev;

	if(list->pos == list->size - 1){
		list->last = n->prev;
		list->current = n->prev;
		list->pos -= 1;
	}
	else{
		if(pos == 0) list->first = n->next;
		list->current = n->next;
	}

	free(n);

	list->size -= 1;

	return 0;
}
