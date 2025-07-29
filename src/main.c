#define DS_IMPLEMENTATION
#define DS_IO_IMPLEMENTATION
#include "ds.h"
#include "gtk/gtk.h"
#include "mupdf/fitz.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_welcome(GtkWidget *widget, gpointer data) {
  g_print("Welcome to PDF_Vault");
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  gtk_window_set_child(GTK_WINDOW(window), box);

  button =
      gtk_button_new_with_label("WELCOME TO PDF_Vault\n\n Click to Enter.");

  g_signal_connect(button, "clicked", G_CALLBACK(print_welcome), NULL);
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy),
                           window);

  gtk_box_append(GTK_BOX(box), button);

  gtk_window_present(GTK_WINDOW(window));
}

void gtk_test(int argc, char *argv[]) {
  GtkApplication *app = NULL;
  int status;
  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  printf("status: %i", status);
  g_object_unref(app);
}

void print_usage(const char *program_name) {
  printf("Usage: %s <pdf_file>\n", program_name);
  printf("Extracts text from a PDF file and prints it to console.\n");
}

int extract_text_from_pdf(const char *filename) {
  int result = 0;
  fz_context *ctx = NULL;
  fz_document *doc = NULL;
  fz_page *page = NULL;
  fz_stext_page *text = NULL;
  fz_device *device = NULL;
  fz_output *out = NULL;
  fz_rect rect;
  int page_count = 0;

  // Create a new context
  ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
  if (!ctx) {
    DS_LOG_ERROR("Failed to create MuPDF context");
    return_defer(1);
  }

  // Register document handlers
  fz_register_document_handlers(ctx);

  // Open the document
  doc = fz_open_document(ctx, filename);
  if (!doc) {
    DS_LOG_ERROR("Failed to open document: %s", filename);
    return_defer(1);
  }

  // Get page count
  page_count = fz_count_pages(ctx, doc);
  printf("Document has %d pages\n", page_count);

  if (page_count == 0) {
    printf("No pages found in document.\n");
    return_defer(0);
  }

  // Process each page
  for (int page_num = 0; page_num < page_count; page_num++) {
    printf("\n--- Page %d ---\n", page_num + 1);

    // Load the page
    page = fz_load_page(ctx, doc, page_num);
    if (!page) {
      DS_LOG_ERROR("Failed to load page %d", page_num + 1);
      continue;
    }

    // Get page bounds
    rect = fz_bound_page(ctx, page);

    // Create text extraction page
    text = fz_new_stext_page(ctx, rect);

    // Create text extraction device with default options
    fz_stext_options options = {0};
    device = fz_new_stext_device(ctx, text, &options);

    // Run the device on the page with error handling
    fz_try(ctx) { fz_run_page(ctx, page, device, fz_identity, NULL); }
    fz_catch(ctx) {
      DS_LOG_ERROR("Error processing page %d", page_num + 1);
      continue;
    }

    // Close the device first
    fz_close_device(ctx, device);
    fz_drop_device(ctx, device);
    device = NULL;

    // Extract and print text using the helper function
    fz_try(ctx) {
      out = fz_new_output_with_file_ptr(ctx, stdout);
      fz_print_stext_page_as_text(ctx, out, text);
      fz_close_output(ctx, out);
      fz_drop_output(ctx, out);
      out = NULL;
    }
    fz_catch(ctx) {
      DS_LOG_ERROR("Error extracting text from page %d", page_num + 1);
      if (out) {
        fz_close_output(ctx, out);
        fz_drop_output(ctx, out);
        out = NULL;
      }
    }

    // Clean up page-specific objects
    fz_drop_stext_page(ctx, text);
    fz_drop_page(ctx, page);

    text = NULL;
    page = NULL;
  }

defer:
  // Clean up
  if (device) {
    fz_close_device(ctx, device);
    fz_drop_device(ctx, device);
  }
  if (out) {
    fz_close_output(ctx, out);
    fz_drop_output(ctx, out);
  }
  if (text)
    fz_drop_stext_page(ctx, text);
  if (page)
    fz_drop_page(ctx, page);
  if (doc)
    fz_drop_document(ctx, doc);
  if (ctx)
    fz_drop_context(ctx);

  return result;
}

int main(int argc, char *argv[]) {

  gtk_test(argc, argv);

  if (argc != 2) {
    print_usage(argv[0]);
    return 1;
  }

  const char *filename = argv[1];

  printf("Extracting text from: %s\n", filename);

  int result = extract_text_from_pdf(filename);

  if (result == 0) {
    printf("\nText extraction completed successfully.\n");
  } else {
    printf("\nText extraction failed.\n");
  }

  return result;
}
