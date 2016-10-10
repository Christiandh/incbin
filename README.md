# incbin 
A very simple program to convert files into normal c/c++ arrays.
### Usage: 
**incbin** *variablename* *datafilename*
### Output:
```
unsigned char variablename[FileLength] = { 
  0x41, 0x2D, 0x7A, 0xE4, ...
};
```
