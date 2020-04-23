//#define LIST_TEST

#ifdef LIST_TEST
#include <stdio.h>

#include "list.h"

int main(void){

	struct list *list;

	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int b[3] = {99,43,69};
	list_create(&list);

	int *data;
	unsigned int i;

	for(i=0;i<5;++i){
		list_prepend(list,a + i);
	}
	for(i=5;i<10;++i){
		list_append(list,a + i);
	}

	list_insert(list,3,b);
	list_insert(list,0,b + 1);
	list_insert(list,list_get_size(list) - 1,b + 2);

	for(i=0;i<list_get_size(list);++i){

		data = list_get_data(list,i);

		printf("%d ",*data);
	}
	printf("\n");

	data = list_get_data(list, 1);
	printf("%d\n",*data);

	data = list_get_data(list, list_get_size(list) - 2);
	printf("%d\n",*data);

	data = list_get_data(list, list_get_size(list) - 5);
	printf("%d\n",*data);

	data = list_get_data(list, 4);
	printf("%d\n",*data);


	list_remove(list, 3, NULL);
	list_remove(list, 0, NULL);
	list_remove(list, list_get_size(list) - 1, NULL);

	for(i=0;i<list_get_size(list);++i){

		data = list_get_data(list,i);

		printf("%d ",*data);
	}


	list_destroy(&list);
}

#endif
