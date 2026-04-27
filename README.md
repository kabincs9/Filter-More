# 🖼️ Filter - Image Processing in C

![C](https://img.shields.io/badge/Language-C-blue.svg)
![CS50](https://img.shields.io/badge/CS50-Week%204-orange.svg)
![Image Processing](https://img.shields.io/badge/Image%20Processing-BMP-brightgreen.svg)

A fun and powerful C program that applies four classic filters to **24-bit BMP images**.

## ✨ Overview

This program reads a BMP image file, applies one of four beautiful filters, and saves the result as a new image. It works directly with pixel data, making it an excellent introduction to image processing and file I/O at the byte level.

## 🎯 Features

- ✅ **Grayscale** — Converts image to black and white
- ✅ **Sepia** — Applies warm vintage sepia tone
- ✅ **Reflection** — Mirrors the image horizontally (left-right flip)
- ✅ **Edges** — Detects and highlights edges using Sobel operator
- ✅ Supports 24-bit uncompressed BMP files
- ✅ Clean command-line interface
- ✅ Preserves original image (creates a new output file)
- ✅ Accurate mathematical calculations for each filter

## 🚀 Quick Start

```bash
# Clone the repository
git clone https://github.com/kabincs9/filter.git
cd filter

# Compile
make

# Run any filter
./filter -g infile.bmp outfile.bmp     # Grayscale
./filter -s infile.bmp outfile.bmp     # Sepia
./filter -r infile.bmp outfile.bmp     # Reflection
./filter -e infile.bmp outfile.bmp     # Edges
