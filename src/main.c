#define DS_IMPLEMENTATION
#define DS_IO_IMPLEMENTATION
#include "ds.h"
#include "zlib.h"
int main(){
	int result = 0;
	int uncmp = 0;
	char *buffer = NULL;
	long buffer_len = ds_io_read("/home/aaron/pdfvault/pdfs/randomwords.pdf", &buffer, "rb");
	if (buffer_len < 0){
		DS_LOG_ERROR("Failed to read file");
		return_defer(-1);
	}

	//parse for stream, start and end, breaks are to stop strncmp when you find what youre looking for
	int start_index = 0, end_index = 0;
	for(int i = 0; i < buffer_len; i++){
		if(strncmp("stream", buffer + i, 6) == 0){
			start_index = i + 7;
			break;
		}
	}
	for(int i = start_index; i < buffer_len; i++){
		if(strncmp("endstream", buffer + i, 9) == 0){
			end_index = i;
			break;
		}
	}

	//Bytef is an unsigned char
	Bytef *source = (Bytef *)(buffer + start_index);

	//unsigned long - len of shortened buffer
	uLong source_len = (uLong)(end_index - start_index);

	//basically an abritrary size, source times 8 bytes
	uLongf dest_len = source_len * 10;

	//allocate enough size for length of source
	Bytef *dest = calloc(sizeof(Bytef), dest_len);	
	
	result = uncompress(dest, &dest_len, source, source_len);
	if(result != Z_OK){
		DS_LOG_ERROR("Uncompress failed: %d", result);
		return_defer(-1);
	}


defer:
	if(buffer != NULL){
		DS_FREE(NULL, buffer);
	}
	return result;
}
