// this is a file operation exercise
// 2015/7/24
// for personal learning
//	
//


#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<getopt.h>  //for supporting long option looks like --help
#include<errno.h>

int main(int argc, char *argv[])
{

	char *filename;
//get parameters from terminal
	int ch;
	opterr = 0;
	while((ch = getopt(argc, argv, "c:sh")) != -1)
	{
		switch(ch)
		{
			case 'c': strcpy(filename, optarg); break;
			default:; 
		}
	}

// to get non-optional parameter
	if(argv[optind] != NULL)
		strncpy(filename, argv[optind], sizeof(argv[optind])-1);

//	printf("%s\n",filename);
//	open a file, if no exist, creat it
	int fd;
	fd = open(filename, O_RDONLY|O_NONBLOCK);
	if(fd == -1)
	{
		//error info ouput
		perror("wtf");
	};

//read a file

	ssize_t ret;
	int total_byte;
	char buf[1024];
	while((ret = read(fd, buf,1024)) > 0)
	{
		total_byte += ret;
		printf("%s", buf);
		memset(buf, 0, 1024);      //this is a important operation to blush buf
	}
	printf("\n%d", total_byte);

/*
// write into a file
	const char *buf = "fuck the programming\n";
	ssize_t nr;

	nr = write(fd, buf,strlen(buf));
	if(nr == -1)
	// error 
	{
		perror("write failed");
	}
*/
	fdatasync(fd);

	if(close(fd) == -1)
		perror("close");
	
	return 0;
}
