/*
 * Оголосити структурний тип "Автор" -- прізвище і гонорар.
 * Створити однозвязний список із змінних такого структурного типу.
 * Передбачити наступні функці:
 * 1. Додавання чергово елементу до початку cписку із заповненням вмісту цього 
 * елементу з клавіатури.
 * 2. Створення списку додаванням елементу в початок.
 * 3. Редагування k-го елемента списку (k передати як параметр).
 * 4. Вивдення вмісту створеного списку на екран.
 * 5. Поміняти місцями k-й і j-й елемент (k i j передати як параметр).
 * 6. Видалення елемента перед k-м (k передати як параметр).
 * Створити текстовий файл, кожний рядок якого міститиме повну інформацію
 * про черного автора із списку.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum { max_surname_len = 32 };

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

struct Author {
	char surname[max_surname_len];
	int fee;
};

struct item {
	struct Author author;
	struct item *next;
};

struct item *create_list(char *str, int fee);
struct item *add_node(struct item *first, char *str, int fee);
void print_list(struct item *first);
void edit_k_node(struct item *first, unsigned int k);
struct item *swap_k_j(struct item *first, unsigned int k, unsigned int j);
struct item *swap_first_second(struct item *first);
struct item *swap_first_k(struct item *first, unsigned int k);
void swap_neighboring(struct item *first, unsigned int k);
void write_to_file(struct item *first, char *name_file);
struct item *delete_before_k(struct item *first, unsigned int k);
void delete_list(struct item *first);

int main(int argc, char **argv)
{
	/*
	char first_surname[max_surname_len];
	int first_fee;

	printf("first surname: ");
	if(!fgets(first_surname, max_surname_len, stdin)) {
		fprintf(stderr, "fgets() failed");
		return 1;
	}
	printf("first fee: ");
	scanf("%d", &first_fee);

	struct item *list = create_list(first_surname, first_fee);
	*/

	if (argc < 1) {
		fprintf(stderr, "too few arguments\n");
		exit(EXIT_FAILURE);
	}

	struct item *list = create_list("a1", 100);

	list = add_node(list, "a2", 200);
	list = add_node(list, "a3", 300);
	list = add_node(list, "a4", 400);
	list = add_node(list, "a5", 500);
	list = add_node(list, "a6", 600);

	printf("-------------------");
	print_list(list);
	printf("-------------------");
	printf("\n EDIT 3 NODE \n");
	edit_k_node(list, 3);
	print_list(list);
	printf("-------------------");
	printf("\n SWAP 0 <-> 1\n");
	list = swap_k_j(list, 0, 1);
	print_list(list);
	printf("-------------------");
	printf("\n SWAP 0 <-> 3\n");
	list = swap_k_j(list, 0, 3);
	print_list(list);
	printf("-------------------");
	printf("\n SWAP 2 <-> 4\n");
	list = swap_k_j(list, 2, 4);
	print_list(list);
	printf("-------------------");
	printf("\n SWAP 3 <-> 4\n");
	list = swap_k_j(list, 3, 4);
	print_list(list);
	printf("-------------------");
	printf("\n DELETE BERORE 3\n");
	list = delete_before_k(list, 3);
	print_list(list);
	printf("-------------------");
	printf("\n DELETE BERORE 1\n");
	list = delete_before_k(list, 1);
	print_list(list);
	printf("-------------------\n");

	write_to_file(list, argv[1]);
	delete_list(list);

	return 0;
}

struct item *create_list(char *str, int fee)
{
	struct item *tmp = malloc(sizeof(*tmp));

	if (!tmp) {
		fprintf(stderr, "malloc() failed: insufficient memory!\n");
		exit(EXIT_FAILURE);
	}

	strcpy(tmp->author.surname, str);
	tmp->author.fee = fee;
	tmp->next = NULL;

	return tmp;
}

struct item *add_node(struct item *first, char *str, int fee)
{
	struct item *tmp = malloc(sizeof(*tmp));

	if (!tmp) {
		fprintf(stderr, "Malloc() failed: insufficient memory!\n");
		exit(EXIT_FAILURE);
	}

	strcpy(tmp->author.surname, str);
	tmp->author.fee = fee;
	tmp->next = first;

	return tmp;
}

void print_list(struct item *first)
{
	if (!first) {
		fprintf(stderr, "List is empty\n");
		return ;
	}

	for (unsigned int i = 0; first; ++i) {
		printf("\nNODE[%d]:", i);
		printf("\nAuthor's surname: %s\n", first->author.surname);
		printf("fee = %d\n", first->author.fee);
		first = first->next;
	}
}

void edit_k_node(struct item *first, unsigned int k)
{
	
	char new_surname[max_surname_len] = "a3";
	int new_fee = 300;
	/*
	printf("\nNew surname: ");

	if(!fgets(new_surname, max_surname_len, stdin)) {
		fprintf(stderr, "fgets() failed\n");
		return ;
	}
	printf("New fee: ");
	scanf("%d", &new_fee);
	*/

	while (k--) {
		first = first->next;
	}
	first->author.fee = new_fee;
	strcpy(first->author.surname, new_surname);
}

struct item *swap_k_j(struct item *first, unsigned int k, unsigned int j)
{
	if (k == j) {
		return first;
	}

	if (max(k, j) == 1 && min(k, j) == 0) {
		return swap_first_second(first);
	}

	if (min(k, j) == 0) {
		return swap_first_k(first, max(k, j));
	}


	if (max(k, j) - min(k, j) == 1) {
		swap_neighboring(first, min(k, j));
		return first;
	}

	struct item *prev_k;
	struct item *prev_j = first;

	for (unsigned int i = 0; i < max(k, j) - 1; ++i) {
		if (i == min(k, j) - 1) {
			prev_k = prev_j;
		}
		if (!prev_j->next) {
			fprintf(stderr, "list has insufficient nodes\n");
			exit(EXIT_FAILURE);
		}
		prev_j= prev_j->next;
	}

	struct item *k_node = prev_k->next;
	struct item *j_node = prev_j->next;

	prev_k->next = j_node;
	prev_j->next = k_node;

	struct item *tmp = k_node->next;

	k_node->next = j_node->next;
	j_node->next = tmp;

	return first;
}

struct item *swap_first_second(struct item *first)
{
	if (!first->next->next) {
		fprintf(stderr, "list has insufficient nodes\n");
		exit(EXIT_FAILURE);
	}

	struct item *tmp = first->next;
	first->next = tmp->next;
	tmp->next = first;

	return tmp;
}

struct item *swap_first_k(struct item *first, unsigned int k)
{
	struct item *prev = first;
	for (unsigned int j = 0; j < k - 1; ++j) {
		if(!prev->next) {
			fprintf(stderr, "list has insufficient nodes\n");
			exit(EXIT_FAILURE);
		}
		prev = prev->next;
	}

	struct item *tmp = prev->next;
	prev->next = first;
	prev = tmp->next;
	tmp->next = first->next;
	first->next = prev;

	return tmp;
}

void swap_neighboring(struct item *prev_k, unsigned int k)
{
	for (unsigned int j = 0; j < k - 1; ++j) {
		prev_k = prev_k->next;
		if (!prev_k->next) {
			fprintf(stderr, "list has insufficient nodes\n");
			exit(EXIT_FAILURE);
		}
	}

	struct item *node_k = prev_k->next;
	struct item *node_j = node_k->next;

	prev_k->next = node_j;
	struct item *tmp = node_j->next;
	node_j->next = node_k;
	node_k->next = tmp;
}

void write_to_file(struct item *first, char *name_file)
{
	FILE *f = fopen(name_file, "w");
	if (!f) {
		perror(name_file);
		exit(EXIT_FAILURE);
	}
	while (first) {
		fprintf(f, "%d : ", first->author.fee);
		fprintf(f, "%s\n", first->author.surname);
		first = first->next;
	}

	fclose(f);
}

struct item *delete_before_k(struct item *first, unsigned int k)
{
	if (k == 0) {
		fprintf(stderr, "it's not possible to delete a node before 0");
		exit(EXIT_FAILURE);
	}

	if (k == 1) {
		struct item *new_first = first->next;
		free(first);
		return new_first;
	}

	struct item *prev_k = first;
	--k;
	while (--k) {
		prev_k = prev_k->next;
		if (!prev_k->next) {
			fprintf(stderr, "list has insufficient nodes\n");
			exit(EXIT_FAILURE);
		}
	}

	struct item *tmp = prev_k->next;
	prev_k->next = tmp->next;
	free(tmp);

	return first;
}

void delete_list(struct item *first)
{
	if (first) {
		delete_list(first->next);
		free (first);
	}
}
