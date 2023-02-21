# Matrix Product

Analysis and Measurement of Energy Comsumption for Matrix Multiplication.

## Dependencies

1. A C++ compiler compatible with C++20
    1. We use [`g++`](https://gcc.gnu.org/) but others should work fine
2. [PAPI](https://icl.utk.edu/papi/)
3. `perf`, toolkit for performance measurements available in Linux
    1. Requires a compatible CPU w/ RAPL, learn more [here](https://web.eece.maine.edu/~vweaver/projects/rapl/rapl_support.html)
    2. See the manual page w/ `man perf`
4. [OpenMP](https://www.openmp.org/)
    1. *Optional*, but required in order to execute `./ompproduct`
5. [GNU Make](https://www.gnu.org/software/make/)
    1. Again, *optional* - just for compilation convinience

## Usage

```sh
make            # builds colproduct and lineproduct
./colproduct    # column-based algorithm
./lineproduct   # line-based algorithm
./ompproduct    # line-based parallel algorithm
make clean      # removes executable file
```

In case of measuring energy:

```sh
# Requires elevated privileges!
# It is also possible to measure the energy consumption of other components
perf stat -e power/energy-cores/ <executable>
```

---
Authors:
- [Miguel Rodrigues](mailto:up201906042@edu.fe.up.pt)
- [Sérgio Estêvão](mailto:up201905680@edu.fe.up.pt)

[CPA @ M.EIC](https://sigarra.up.pt/feup/pt/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=486270)
