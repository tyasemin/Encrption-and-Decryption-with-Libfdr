# Encryption and Decryption with Libfdr

## Description
A text encryption/decryption tool using JRB (Red-Black Trees) from the Libfdr library. The program maps words to numeric codes stored in a `.kilit` file and performs encryption or decryption operations on text files.

## Usage

### Build
```bash
make
```

### Encrypt
```bash
./bin/kripto -e <input_file> <output_file>
```

### Decrypt
```bash
./bin/kripto -d <input_file> <output_file>
```

**Note:** A `.kilit` file containing word-to-code mappings must be present in the current directory.

---

Libfdr: https://web.eecs.utk.edu/~huangj/cs360/360/notes/Libfdr/
