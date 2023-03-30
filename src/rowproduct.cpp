/*
 *  rowproduct.cpp - row based matrix multiplication
 *  CPA @ M.EIC, 2023
 *  Authors:
 *      Miguel Rodrigues <up201906042@edu.fe.up.pt>
 *      Sérgio Estêvão <up201905680@edu.fe.up.pt>
 */
#include <memory>
#include "mphelpers.h"


// globals & aliases
using matrix_t = double[];
using matrix_size_t = std::size_t;
static constexpr matrix_size_t N = 1400;


std::unique_ptr<matrix_t>
mult(const matrix_t a, const matrix_t b)
{
    auto result = std::make_unique<matrix_t>(N * N);

    for (matrix_size_t i = 0; i < N; i++)
        for (matrix_size_t k = 0; k < N; k++)
            for (matrix_size_t j = 0; j < N; j++)
                result[i * N + j] += a[i * N + k] * b[k * N + j];

    return result;
}


int
main(void)
{
    /* helper struct which handles PAPI internals */
    cpa::matrix_product::PAPI_helper helper;

    /* matrix allocation and filling */
    auto a = std::make_unique<matrix_t>(N * N);
    auto b = std::make_unique<matrix_t>(N * N);
    cpa::matrix_product::fill<N>(a.get(), b.get());

    helper.start();

    /* perform the computation of matrix multiplication */
    const auto start = std::chrono::steady_clock::now();
    auto c = mult(a.get(), b.get());
    const auto end = std::chrono::steady_clock::now();

    helper.stop();

    /* report the results */
    const auto elapsed = end - start;
    cpa::matrix_product::report<N>(helper, elapsed);

    return 0;
}
