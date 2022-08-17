#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	struct node *next;
	int data;
} node;

typedef struct stack {
	node *head;
	unsigned long size;
} stack;

node *create_node(int data)
{
	node *new_node = malloc(sizeof(node));
	new_node->next = NULL;
	new_node->data = data;

	return new_node;
}

stack *create_stack(int data)
{
	stack *new_stack = malloc(sizeof(new_stack));
	new_stack->head = create_node(data);
	new_stack->size = 1;

	return new_stack;
}

void show_stack(stack *tmp_stack)
{
	node *tmp_node = tmp_stack->head;

	printf("Stack's size : %lu\n", tmp_stack->size);
	while (tmp_node) {
		printf("-> [%d] ", tmp_node->data);
		tmp_node = tmp_node->next;
	}
	printf("\n");
}

void push_stack(stack *tmp_stack, int data)
{
	node *tmp_node = create_node(data);
	tmp_node->next = tmp_stack->head;
	tmp_stack->head = tmp_node;
	++tmp_stack->size;
}

void pop_stack(stack *tmp_stack)
{
	node *tmp_node = tmp_stack->head;
	tmp_stack->head = tmp_node->next;
	--tmp_stack->size;
	free(tmp_node);
}

void delete_stack(stack *tmp_stack)
{
	node *tmp_node = tmp_stack->head;
	node *tmp_free_node;
	free(tmp_stack);

	while (tmp_node) {
		tmp_free_node = tmp_node;
		tmp_node = tmp_node->next;
		free(tmp_free_node);
	}
}

int main(void)
{
	stack *test_stack = create_stack(2);
	show_stack(test_stack);

	push_stack(test_stack, 3);
	push_stack(test_stack, 4);
	push_stack(test_stack, 3);
	show_stack(test_stack);

	pop_stack(test_stack);
	pop_stack(test_stack);
	show_stack(test_stack);
	push_stack(test_stack, 5);

	delete_stack(test_stack);

	return 0;
}
