#include <stdio.h>
#include <string.h>

#define DEC_A 65
#define DEC_Z 90
#define DEC_a 97
#define DEC_z 122

#define MAXTEXTSIZE 256
#define false 0
#define true 1

#define SHIFT_RIGHT(a, left, right) ((a > right) ? (a % right + left) : a)
#define SHIFT_LEFT(a, left, right) ((a < left) ? (right - left % a) : a)

typedef char* string;
typedef unsigned int uint;
typedef char bool;


bool is_letter(char c);

string decryption(char* str, int key);
string encryption(char* str, int key);
void show(void);

int main() {
	uint key;
	char text[MAXTEXTSIZE];
	char c;

	show();

	while ((c = getchar()) != 'f') {
		printf("enter key: ");
		scanf("%u", &key);
		printf("enter your text: ");
		scanf("%s", text);
		getchar();
		
		if (c == 'e') {
			printf("\nencryption text: ");
			printf("%s\n", encryption(text, key));
		} else {
			if (c == 'd') {
				printf("\ndecryption text: ");
				printf("%s\n", decryption(text, key));
			} else {
				printf("please enter f/e/d\n");
			}
		}
		show();
	}

	return 0;
}

void show(void) 
{
	printf("\nenter 'f' for finish\n");
	printf("enter 'e' for encryption\n");
	printf("enter 'd' for decryption\n");
}

string encryption(string str, int key)
{
	int i = 0;
	while (str[i] != '\0') {
		if (is_letter(str[i])) {
			str[i] += key;
			if (DEC_A <= str[i] && str[i] <= DEC_Z) {
				str[i] = SHIFT_RIGHT(str[i], DEC_A, DEC_Z);
			} else {
				str[i] = SHIFT_RIGHT(str[i], DEC_a, DEC_z);
			}
		}
		++i;
	}
	
	return str;
}

string decryption(string str, int key)
{
	int i = 0;
	while (str[i] != '\0') {
		if (is_letter(str[i])) {
			str[i] -= key;
			if (DEC_A <= str[i] && str[i] <= DEC_Z) {
				str[i] = SHIFT_LEFT(str[i], DEC_A, DEC_Z);
			} else {
				str[i] = SHIFT_LEFT(str[i], DEC_a, DEC_z);
			}
		}
		++i;
	}
	
	return str;
}



bool is_letter(char c)
{
	if ((DEC_A <= c && c <= DEC_Z) || (DEC_a <= c && c <= DEC_z)) {
		return true;
	} else {
		return false;
	}
}
