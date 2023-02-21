# Matrix Product

Analysis and Measurement of Energy Comsumption for Matrix Multiplication.

## Dependencies

1. A C++ compiler compatible with C++20
    1. We use [g++](https://gcc.gnu.org/) but others should work fine
2. [PAPI](https://icl.utk.edu/papi/)
3. [OpenMP](https://www.openmp.org/)
    1. *Optional*, but required in order to execute `./ompproduct`
4. [GNU Make](https://www.gnu.org/software/make/)
    1. Again, *optional* - just for compilation convinience

## Usage

```sh
make            # builds colproduct and lineproduct
./colproduct    # column-based algorithm
./lineproduct   # line-based algorithm
./ompproduct    # line-based parallel algorithm
make clean      # removes executable file
```

---
Authors:
- [Miguel Rodrigues](mailto:up201906042@edu.fe.up.pt)
- [Sérgio Estêvão](mailto:up201905680@edu.fe.up.pt)

[CPA @ M.EIC](https://sigarra.up.pt/feup/pt/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=486270)
