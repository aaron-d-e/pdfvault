#define DS_IMPLEMENTATION
#define DS_IO_IMPLEMENTATION
#include "ds.h"

int main(){
	int result = 0;
	char *buffer = NULL;
	long buffer_len = ds_io_read("/home/aaron/pdfvault/pdfs/randomwords.pdf", &buffer, "rb");
	if (buffer_len < 0){
		DS_LOG_ERROR("Failed to read file");
		return_defer(1);
	}
	DS_LOG_INFO("%s", buffer);

	//parse for stream, start and end
	int beg_index = 0, end_index = 0;
	for(int i = 0; i < buffer_len; i++){
		if(strncmp("stream", buffer + i, 6) == 0){
			beg_index = i + 6;
		}
	}
	for(int i = beg_index; i < buffer_len; i++){
		if(strncmp("endstream", buffer + i, 9) == 0){
			end_index = i
		}
	}

defer:
	if(buffer != NULL){
		DS_FREE(NULL, buffer);
	}
	return result;
}
