//need zlib and ds.h

#include <iostream>
#include "zlib.h"
#include "ds.h"

#define DS_IO_IMPLEMENTATION
using namespace std;


int main(){
	const char* filename = "/home/aaron/Downloads/randomwords.pdf";
	char* buffer = NULL;
	
	int buffer_len = ds_io_read_binary("/home/aaron/Downloads/randomwords.pdf", &buffer);

	DS_LOG_INFO("%s", buffer);

	return 0;
}
