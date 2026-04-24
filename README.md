# DS-Project

A simple file compression and decompression project written in C using Huffman coding.

## Overview

This project:

- reads a text or binary file
- counts byte frequencies
- builds a Huffman tree
- compresses the file into a `.g5` format
- decompresses a `.g5` file back into a `.txt` file

The program is operated from the command line and prompts for the output filename during compression and decompression.

## Project Structure

- `main.c`  
  Entry point for the CLI. Handles command-line arguments and calls compression or decompression.

- `freq.h`  
  Counts and prints character frequencies from the input file.

- `huffman.h`  
  Defines the Huffman tree, min-heap, code generation, and memory cleanup helpers.

- `compress.h`  
  Handles Huffman-based compression and writes compressed output to a `.g5` file.

- `decompress.h`  
  Rebuilds the Huffman tree from the compressed file and restores the original contents into a `.txt` file.

## How It Works

### Compression

1. The program reads the input file.
2. It counts the frequency of each byte.
3. A Huffman tree is built from those frequencies.
4. Huffman codes are generated for each symbol.
5. The compressed file stores:
   - total character count
   - serialized Huffman tree
   - encoded file data

### Decompression

1. The program reads the compressed `.g5` file.
2. It rebuilds the Huffman tree from the stored header.
3. It decodes the bit stream using the tree.
4. The decoded result is written to a `.txt` output file.

## Build

Compile with `gcc`:

```bash
gcc main.c -o main
```

If your compiler defaults are stricter, this also works well:

```bash
gcc -std=c99 -Wall -Wextra main.c -o main
```

## Usage

### Compress a file

```bash
./main <filename> --compress
```

Example:

```bash
./main sample.txt --compress
```

The program will ask for an output name, then create:

```text
<output_name>.g5
```

### Decompress a file

```bash
./main <filename> --decompress
```

Example:

```bash
./main compressed.g5 --decompress
```

The program will ask for an output name, then create:

```text
<output_name>.txt
```

## Example Flow

```bash
gcc main.c -o main
./main input.txt --compress
./main input_compressed.g5 --decompress
```

## Notes

- Compression output always gets the `.g5` extension appended automatically.
- Decompression output always gets the `.txt` extension appended automatically.
- The program prints a frequency table before compression.
- Empty input files are currently rejected during compression.
- Output filenames are read interactively from standard input.

## Future Improvements

- support non-interactive output filenames through command-line flags
- improve validation and error handling
- add a `Makefile`
- add automated test cases
- better handling for edge cases and malformed compressed files
