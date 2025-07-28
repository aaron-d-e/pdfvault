#define DS_IMPLEMENTATION
#define DS_IO_IMPLEMENTATION
#include "ds.h"
#include "zlib.h"
#include "mupdf/fitz.h"
int main(){
	int result = 0;
	//filename should be complete path
	char *filename = NULL;

	fz_context *ctx = NULL;
	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);

	fz_document *doc = NULL;
	doc = fz_open_document(ctx, filename);


	fz_print_text_page(ctx, NULL, fz_text_page *page)
	return result;
}
