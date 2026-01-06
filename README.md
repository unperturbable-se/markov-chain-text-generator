# Markov Chain Text Generator (Pre-release)

This is a C++ project that generates random text based on Markov chains. It uses only the standard library. 
Note that this is currently in a pre-release state and the generated output is still being refined.

## Installation

* **Option 1:** Download and extract the ZIP file from the latest pre-release.
* **Option 2:** Manually compile the C++ source files.

## How to Run

The process involves two steps:

1. **Preprocessing:** Run `preprocess.exe`. This cleans the dataset and saves the Markov chain data into a file.
2. **Generation:** Run `main.exe` to produce text.

**Note:** It may take a little while for the program to load the data file before it starts.

## Training Data

The program trains on the content of `train.txt`. You can replace the text in this file with your own data to change the output style. The current file contains a random novel found online.
