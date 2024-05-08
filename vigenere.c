#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* readFile(FILE* f, int size);
void getfilesize(FILE* f, int* size);
void propprint(char* text, int length, FILE* out);
char* encrypt(char* text, char* key, int textsize, int keysize);

int main(int argc, char** argv) {
	char outfilename[11] = "stu";
	printf("%c", argv[1][1]);
	outfilename[2] = argv[1][1];
	strcat(outfilename, "Output");
	FILE* key = fopen(argv[1], "r");
	FILE* plain = fopen(argv[2], "r");
	FILE* output = fopen(outfilename, "w");
	int keysize;
	int textsize = 512;
	if (key == NULL || plain == NULL) {
		printf("\nCANT OPEN FILES!!");
		exit(-999);
	}
	char* plaintext = readFile(plain, textsize);
	getfilesize(key, &keysize);
	char* keytext = readFile(key, keysize);
	fprintf(output,"\nVigenere Key:\n");
	propprint(keytext, keysize, output);
	fprintf(output,"\n\nPlaintext:\n");
	propprint(plaintext, textsize, output);
	char* cipher = encrypt(plaintext, keytext, textsize, keysize);
	fprintf(output,"\n\nCiphertext:\n");
	propprint(cipher, textsize, output);

	fclose(key);
	fclose(plain);
	fclose(output);
	free(cipher);
	free(keytext);
	free(plaintext);
}

char* readFile(FILE* f, int size){
	int track = 0;
	char* out = malloc(sizeof(char )*size);
	int c;
	while ((c = fgetc(f)) != EOF && track < size){
		if (c >= 97 && c <=122)
			out[track++] = (char) c;
		else if(c >= 65 && c <= 90)
			out[track++] = (char)(c+32);
	}
	while(track < size){
		out[track++] = 'x';
	}
	return out;
}

void getfilesize(FILE* f, int* size){
	*size = 0;
	int c;
	while ((c = fgetc(f)) != EOF)
		if((c >= 97 && c <=122) || (c >= 65 && c <= 90))
			(*size)++;

	rewind(f);
}

void propprint(char text[], int length, FILE* out){
	int i, j;
	i=0;
	while (i < length){
		if(i%80 == 0) //&& i!=0 // not using for now
			fprintf(out, "\n");
		fprintf(out,"%c", text[i]);
		i++;
	}
}

char* encrypt(char* text, char* key, int textsize, int keysize){
	int i, track;
	track = 0;
	char* cipher = malloc(sizeof(char)*textsize);
	for(i = 0; i < textsize; i++){
		if(track == keysize)
			track = 0;
		cipher[i] = (char)(((text[i]-97)+(key[track++]-97))%26) +97;
	}

	return cipher;
}