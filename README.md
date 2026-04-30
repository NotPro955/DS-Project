# File Compressor using Huffman Coding (DS Project)

A simple and efficient file compression and decompression tool written in C using **Huffman Coding**, developed by *Geeks 5*.

---

##  Overview

This project demonstrates how lossless data compression works using Huffman encoding.

The program:

* Reads a file (text or binary)
* Calculates frequency of each byte
* Builds a Huffman Tree
* Encodes data into compressed format (`.g5`)
* Decodes compressed file back to original (`.txt`)

---

## Concept Used

* Huffman Coding (Greedy Algorithm)
* Binary Trees
* Min Heap (Priority Queue)
* Bit-level file handling

---

## Project Structure

```
.
├── main.c          → CLI interface and program flow
├── freq.h          → Frequency calculation  
├── huffman.h       → Tree + heap + code generation
├── compress.h      → Compression logic
├── decompress.h    → Decompression logic
└── README.md
```

---

## How It Works

### Compression

1. Read input file
2. Count frequency of each character
3. Build Huffman Tree
4. Generate binary codes
5. Store:

   * Total characters
   * Encoded Huffman tree
   * Compressed data

Output file → `.g5`

---

### Decompression

1. Read `.g5` file
2. Reconstruct Huffman Tree
3. Decode bit stream
4. Write original data

Output file → `.txt`

---

## 🛠️ Build Instructions

Compile using GCC:

```bash
gcc main.c -o main
```

---

## Usage

### Compress

```bash
./main <filename> --compress
```

Example:

```bash
./main sample.txt --compress
```

Then enter output name → creates:

```
output.g5
```

---

### Decompress

```bash
./main <filename> --decompress
```

Example:

```bash
./main sample.g5 --decompress
```

Then enter output name → creates:

```
output.txt
```

---

## Example

```bash
gcc main.c -o main
./main input.txt --compress
./main input.g5 --decompress
```

---

## Features

* Lossless compression
* Custom `.g5` format
* Bit-level encoding
* Tree serialization
* Works on any file type

---

## Limitations

* Output filename must be entered manually
* No GUI (command line only)
* Limited error handling
* Not optimized for very large files

---

## Future Improvements

* Add command-line flags for output file
* Improve error handling
* Add Makefile
* Add GUI interface
* Optimize compression ratio

---

## Team

**Geeks 5**

* Bharath
* Hrushikesh
* Mukesh
* Raghav
* Shanmukh

---

## Notes

* Compression appends `.g5` automatically
* Decompression appends `.txt` automatically
* Empty files are not supported

---

## Reference

Basic implementation inspired from standard Huffman Coding concepts and data structures.

---

## 💡 Final Thought

This project is a practical implementation of how real-world compression systems work at a low level using bits and trees.
