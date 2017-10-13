// Hillari Denny
// CSCE A320 - Operating Systems
// Assignment 2
//
// This program uses the fread family of C library calls to read data from a specified file


#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {

	FILE* fp;
	unsigned long length;

//~~~the following lines get us the size of the file to determine a size for our buffer~~~// 
	fp = fopen(argv[1], "r");
	fseek(fp,0,SEEK_END); //to 0th byte from end of file (eof)
	length = ftell(fp); //obtains current value of file position indicator 
	fseek(fp, 0, SEEK_SET); //reset file pointer to 0th byte from beginning (aka to beginning of file)
	printf("Number of bytes in file: %ld\n", length);
	char* buf=malloc(length); //allocate a buffer for the amount of bytes returned by ftell

//~~~Read from the file pointer while not eof
	while (!feof(fp)) {   
    fread(buf, length, 1, fp);  //reads from fp into buf
    //printf("%c",*buf);
    }


    free(buf);
    fclose(fp);


    

    
//The following code is for personal reference and testing purposes only//
//     int ch;
//     int charcount = 0;
//     int word;

//     puts("Text in file is:");
//     while ((ch = fgetc(fp)) != EOF) {
//         charcount++;
//         printf("%c", ch);
//         if (ch != ' ') {
//             word++;
//         }
//     }

//     printf("Character count is: %d\n", word);

// //*****write to new file 
// 	FILE* output;
//     output = fopen("output.txt", "w");
//     if(output == NULL ) {
//         puts("file read error");
//     }
//     else {

//        fwrite(buf, 1, 100, output);
// }

}