#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
} node;

typedef struct queue {
	unsigned long size;
	node *head;
	node *tail;
} queue;

node *create_node(int data)
{
	node *new_node = malloc(sizeof(node));
	if (new_node == NULL) {
		fprintf(stderr, "malloc() failed: insufficient memory\n");
		exit(EXIT_FAILURE);
	}
	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

queue *create_queue(int data)
{
	queue *new_queue = malloc(sizeof(queue));
	if (new_queue == NULL) {
		fprintf(stderr, "malloc() failed: insufficient memory\n");
		exit(EXIT_FAILURE);
	}
	new_queue->head  = create_node(data);
	new_queue->tail  = new_queue->head;
	new_queue->size  = 1;

	return new_queue;
}

void show_queue(queue *tmp_queue)
{
	node *tmp_node = tmp_queue->head;

	printf("Queue's size : %lu\n", tmp_queue->size);
	while (tmp_node) {
		printf(" -> [%d]", tmp_node->data);
		tmp_node = tmp_node->next;
	}
	printf("\n");
}

void push(queue *tmp_queue, int data)
{
	node *new_node = create_node(data);
	new_node->next = tmp_queue->head;
	tmp_queue->head = new_node;
	++tmp_queue->size;
}

int main(void)
{
	queue *test_queue = create_queue(5);
	show_queue(test_queue);
	push(test_queue, 3);
	push(test_queue, 2);
	push(test_queue, 1);
	show_queue(test_queue);
	return 0;
}
