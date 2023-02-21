# Matrix Product

Analysis and Measurement of Energy Comsumption for Matrix Multiplication.

## Dependencies

1. A C++ compiler compatible with C++20
    1. We use [g++](https://gcc.gnu.org/) but others should work fine
2. [PAPI](https://icl.utk.edu/papi/)
3. [GNU Make](https://www.gnu.org/software/make/)
    1. This is *optional*, just for conviniece of compilation

## Usage

```sh
make            # builds colproduct and lineproduct
./colproduct    # column-based algorithm
./lineproduct   # line-based algorithm
make clean      # removes executable file
```

---
Authors:
- [Miguel Rodrigues](mailto:up201906042@edu.fe.up.pt)
- [Sérgio Estêvão](mailto:up201905680@edu.fe.up.pt)
