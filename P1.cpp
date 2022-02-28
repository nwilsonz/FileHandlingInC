//Written by Nick Wilson

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//The objective of this program is to use the open(), read(), and write() system calls to switch lower-case letters in a file to upper-case letters and upper-case letters to lower-case letters. The output is stored in a separate text file than the original input file. These I/O system calls are very useful for file handling and are important to know. 

//Here is a brief summary of what these system calls allow us to do.

//open() - This system call allows us to open a file for reading, writing, or both. It may also create a file if one does not already exist. It also returns a file descriptor.
//read() - This system call allows us to read from a file indicated by the file descriptor. It will read up to n number of bytes and store them into a buffer. On success, it will return the number of bytes read and update the file position by that number.
//write() - This system call allows us to write to a file descriptor. It will write up to n number of bytes from the buffer to the file referred to by its file descriptor.
//close() - This sytem call allows us to tell the operating system that we are done with a file descriptor and it will close the file pointed to by the file descriptor.


//Initially, I thought that this function for getting the file size would be useful, but I ended up not needing it. However, I will leave it here because I think it may be useful to utilize in the future.
//size_t getFileSize(const char* filename) {
//	struct stat st;
//	if(stat(filename, &st) != 0)
//		return 0;
//	return st.st_size;
//}

using namespace std;

int main(int argc, char* argv[]) {
	cout << "P1 Starting" << endl;

	int fd1, fd2;
	char c;
	int bytes;

	char* path1 = argv[1];
	char* path2 = argv[2];

	//Make sure to open the files so that we can get their respective file descriptors.
	//Note that the input file will be read only whereas the output file will be write only.
	fd1 = open(path1, O_RDONLY);
	fd2 = open(path2, O_WRONLY);

//	size_t size = getFileSize(argv[1]);

	//Error checking
	if (fd1 == -1 || fd2 == -1) {
		printf("Error opening file");
		return -1;
	}

	//This is the main function of the program which switches the case of the letters in the original input file.
	while((bytes = read(fd1, &c, sizeof(c))) > 0) {

		for(int i = 0; i < bytes; i++) {
			if (islower(c)) {
                   	     c = toupper(c);
               		 } else if (isupper(c)) {
				 c = tolower(c);
			 }
		}
		//Now, we can write to the empty output text file.
		write(fd2, &c, sizeof(c));
	}

	cout << "Success" << endl;

	//Make sure to close the files pointed to by the file descriptors.
	close(fd1);
	close(fd2);

	return 0;
}
