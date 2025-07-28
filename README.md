# PDF Vault - PDF Text Extractor

A simple C-based PDF text extractor using MuPDF library.

## Features

- Extracts text from PDF files
- Handles multiple pages
- Robust error handling
- Clean console output

## Requirements

- CMake 3.10 or higher
- MuPDF library (version 1.26.3 tested)
- C compiler with C11 support

## Installation

### Arch Linux
```bash
sudo pacman -S mupdf cmake
```

### Ubuntu/Debian
```bash
sudo apt-get install libmupdf-dev cmake build-essential
```

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
./main <pdf_file>
```

### Examples

```bash
# Extract text from a PDF file
./main ../pdfs/randomwords.pdf

# Extract text from another PDF
./main ../pdfs/Sample.pdf
```

## Project Structure

```
pdfvault/
├── CMakeLists.txt      # Build configuration
├── src/
│   ├── main.c         # Main PDF parser implementation
│   └── ds.h           # Utility library
├── pdfs/              # Sample PDF files
│   ├── randomwords.pdf
│   ├── Sample.pdf
│   └── ocrtest.pdf
└── build/             # Build output directory
```

## How it Works

The PDF parser uses MuPDF's structured text extraction API to:

1. Open the PDF document
2. Iterate through each page
3. Extract text using `fz_new_stext_device`
4. Print the extracted text to console
5. Handle errors gracefully

## Error Handling

The parser includes robust error handling for:
- Corrupted PDF files
- Pages with complex content
- Memory allocation failures
- File I/O errors

## Dependencies

- **MuPDF**: PDF rendering and text extraction library
- **ds.h**: Custom utility library for logging and memory management

## License

This project is open source. Feel free to modify and distribute as needed. 