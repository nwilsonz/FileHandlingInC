//Written by Nick Wilson
//
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

//The objective of this program is to switch lower-case letters in an input file to upper-case letters and upper-case letters to lower-case ones through the use of memory-mapped file I/O. This program will write back to the original input file.

//Memory mapped files are generally files in the file system which have been mapped by the operating system to some range of bytes in memory of a process. Therefore, when the process writes to the memory, the operating system ensures that the bytes are written to the file. When the process reads from memory, the operating system ensures that the file is read. Essentially, the system creates a file mapping to associate the file and the address space of the process.

//In comparison to the open()/read()/write() system calls and the fopen()/fread()/fwrite() library functions, memory-mapped file I/O reduces the amount of data copying required. It is much more efficient. It saves time and does not require many expensive system calls.

//This function is utilized in order to get the size of the file.
size_t getFileSize(const char* filename) {
        struct stat st;
        if(stat(filename, &st) != 0)
                return 0;
        return st.st_size;
}

using namespace std;

int main(int argc, char* argv[]) {
	char* path = argv[1];
	int fd = open(argv[1], O_RDWR);

	size_t size = getFileSize(argv[1]);

	char *file_in_mem;
	
	//This is perhaps the most critical part of this program. Here, the file is mapped into memory and the function returns a pointer to the mapped area which can be used to access the memory. It is critical to have the MAP_SHARED property so that we can write the changes back to the file.
	file_in_mem = static_cast<char*>(mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

	//This for-loop simply changes the cases of the letters in the file.
	for (int i=0; i < size; i++) {
		if (islower(file_in_mem[i])) {
			file_in_mem[i] = toupper(file_in_mem[i]);
		} else if (isupper(file_in_mem[i])) {
			file_in_mem[i] = tolower(file_in_mem[i]);
		}
	}

	//Here I make sure to remove the mapping so no further access to the allocated memory remains legal. I also make sure to close the file.
	munmap(file_in_mem, size);
	close(fd);

	return 0;
}

