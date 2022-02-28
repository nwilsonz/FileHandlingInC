//Written by Nick Wilson

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fstream>
#include <cstring>

#define BUFFER_SIZE 4096

//The objective of this program is to use the fopen(), fread(), and fwrite() APIs to switch lower-case letters in a file to upper-case letters and upper-case letters to lower-case letters. The output is then stored in a separate text file than the original input file. Unlike the open(), read(), and write() system calls, these functions are not system calls. In fact, they are part of the C library, and they provide buffered I/O, whereas the system calls do not.

//Here is a brief overview of these APIs

//fopen() - This returns a pointer to the FILE structure on success or NULL in case of failure. It is used to open a file and associate an I/O stream with it.
//fread() and fwrite() - These functions are very similar. However, one is for reading and one is for writing, as the names imply. 

using namespace std;

int main(int argc, char* argv[]) {
        char* fpath = argv[1];
        char* fpath2 = argv[2];

	//Make sure to open the files with fopen and specify whether the file should be opened in read only		or write only mode. 
        FILE *fp1 = fopen(fpath, "r");
        FILE *fp2 = fopen(fpath2, "w");

        if (fp1 == NULL || fp2 == NULL) {
                printf("Error opening file(s)");
                return -1;
        }

        char buffer[BUFFER_SIZE];

        int len;

	//This is the main function of the program. Instead of directly using fread(), I went with the fgets() function, which reads characters from a stream and stores them as a C string into the buffer. It is different from fread() in the sense that it will read until the first new line, maximum bytes to read at once, or the End of File (whichever is encountered first). fread() is similar, but it will read a specfic chunk of bytes and stop when that limit has been reached or zero bytes have been read. Both are viable methods. I found that fgets() was easier to implement for me.
	//In this function, we get all of the input file's contents and store it into a buffer. From there, we iterate over the contents and change the case of the letters as desired.
        while(fgets(buffer, BUFFER_SIZE, fp1) != NULL) {
                len = strlen(buffer);
                for(int i=0; i < len; i++) {
                        if (islower(buffer[i])) {
                                buffer[i] = toupper(buffer[i]);
                      } else if (isupper(buffer[i])) {
                                buffer[i] = tolower(buffer[i]);
                      }

                }
		//Here I use fwrite() to write the newly updated contents of the buffer to the output file.
                fwrite(buffer, sizeof(char), len, fp2);
        }

        cout << "Success" << endl;

	//Here I make sure to close the files associated with the stream and disassociate them.
        fclose(fp1);
        fclose(fp2);

        return 0;
}

