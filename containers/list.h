/* File: list.h
 * Desc: Generic double linked list implementation
 */

#ifndef __CONTAINER_LIST_H__
#define __CONTAINER_LIST_H__

/* Opaque handle */
struct list;

/* Function: list_create
 * Input: A reference to an opaque list pointer
 * Output:
 *
 * Description: Creates a list container to store objects
 * Spec: Call this function only once
 */
extern int list_create(struct list **list);


/* Function: list_destroy
 * Input: A reference to an opaque list pointer
 *
 * Description: This functions destroys the list
 * Spec: Call this function only once
 */
extern void list_destroy(struct list **list);

/* Function list_get_size
 * Input: A pointer to the list object
 *
 * Description: Returns the actual size of the list
 */
extern unsigned int list_get_size(struct list *list);

/* Function: list_get_data
 * Input: A pointer to the list object and the position to go look at
 * Output: The object or NULL on error
 *
 * Description: A way to get the stored objects in the list
 */
extern void* list_get_data(struct list *list, unsigned int pos);

/* Function: list_prepend
 * Input: A pointer to the list object and the data to store
 * Output:
 *
 * Descriptions: Puts the data at the beginning of the list
 */
extern int list_prepend(struct list *list, void *data);

/* Function: list_append
 * Input: A pointer to the list object and the data to store
 * Output:
 *
 * Descriptions: Puts the data at the end of the list
 */
extern int list_append(struct list *list, void *data);

/* Function: list_insert
 * Input: A pointer to the list object, the position where to store the data and the data to store
 * Output:
 *
 * Descriptions: Puts the data at the specified position in the list
 */
extern int list_insert(struct list *list, unsigned int pos, void *data);

/* Function: list_remove
 * Input: A pointer to the list object, the position where to remove the data
 * 		  and a reference to a location to store the data from the node that is
 * 		  getting removed
 * Output:
 *
 * Descriptions: Removes the node at the specified location. Optionally, the user
 * 			     can specify a location to store the data object of the node.
 *
 * Spec: if data NON-NULL, the object associated with the node getting removed will
 * 		 be placed there for the user to get.
 */
extern int list_remove(struct list *list, unsigned int pos, void **data);

#endif
