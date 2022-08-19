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

queue *create_queue(void)
{
        queue *new_queue = malloc(sizeof(queue));
        if (new_queue == NULL) {
                fprintf(stderr, "malloc() failed: insufficient memury\n");
                exit(EXIT_FAILURE);
        }
        new_queue->size = 0;
        new_queue->head = NULL;
        new_queue->tail = NULL;

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
        if (tmp_queue->head == NULL) {
                tmp_queue->head = new_node;
                tmp_queue->tail = new_node;
        } else {
                tmp_queue->tail->next = new_node;
                tmp_queue->tail = new_node;
        }
        ++tmp_queue->size;
}

void pop(queue *tmp_queue)
{
        if (tmp_queue->size == 0) {
                printf("Queue is empty\n");
                return ;
        }

        node *free_node = tmp_queue->head;
        tmp_queue->head = free_node->next;
        --tmp_queue->size;
        free(free_node);
}

void delete_queue(queue *tmp_queue)
{
        node *tmp_node = tmp_queue->head;
        node *tmp_free_node;
        free(tmp_queue);

        while (tmp_node) {
                tmp_free_node = tmp_node;
                tmp_node = tmp_node->next;
                free(tmp_free_node);
        }
}

int main(void)
{
	queue *test_queue = create_queue();
	show_queue(test_queue);
	push(test_queue, 3);
	push(test_queue, 2);
	push(test_queue, 1);
	show_queue(test_queue);
        pop(test_queue);
	show_queue(test_queue);
        pop(test_queue);
	show_queue(test_queue);
        push(test_queue, 4);
        push(test_queue, 5);
        push(test_queue, 6);
	show_queue(test_queue);

        delete_queue(test_queue);

	return 0;
}
