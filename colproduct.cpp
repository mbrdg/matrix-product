/* 
    Column based multiplication @ CPA, 2023
    Authors: Miguel Rodrigues & Sérgio Estêvão
*/
#include <array>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string_view>

#include <papi.h>


static constexpr std::size_t MATRIX_SIZE = 2000;
using matrix_type = double*;


matrix_type
multiplication(const matrix_type a, const matrix_type b)
{
    matrix_type result = new double[MATRIX_SIZE * MATRIX_SIZE];

    for (auto i = 0; i < MATRIX_SIZE; i++) {
        for (auto j = 0; j < MATRIX_SIZE; j++) {
            
            double dot = 0.0;
            for (auto k = 0; k < MATRIX_SIZE; k++) {
                dot += a[i * MATRIX_SIZE + k] * b[k * MATRIX_SIZE + j];
            }

            result[i * MATRIX_SIZE + j] = dot;            
        }
    }

    return result;
}


int
main(void) 
{
    auto papi_handle_error = [](std::string_view name) {
        std::cerr << name << ' ' << "failed" << std::endl;
        std::exit(1);
    };

    int papi_eventset = PAPI_NULL;
    std::array<int, 4> papi_event_codes = { PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TOT_INS, PAPI_TOT_CYC };
    std::array<long long, 4> papi_values = { 0, 0, 0, 0 };
    int papi_retval = 0;

    papi_retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (papi_retval != PAPI_VER_CURRENT) {
        papi_handle_error("PAPI_library_init");
    }

    papi_retval = PAPI_create_eventset(&papi_eventset);
    if (papi_retval != PAPI_OK) {
        papi_handle_error("PAPI_create_eventset");
    }

    papi_retval = PAPI_add_events(papi_eventset, papi_event_codes.data(), papi_event_codes.size());
    if (papi_retval != PAPI_OK) {
        papi_handle_error("PAPI_add_events");
    }

    papi_retval = PAPI_start(papi_eventset);
    if (papi_retval != PAPI_OK) {
        papi_handle_error("PAPI_start failed");
    }

    matrix_type a = new double[MATRIX_SIZE * MATRIX_SIZE];
    matrix_type b = new double[MATRIX_SIZE * MATRIX_SIZE];

    for (auto i = 0; i < MATRIX_SIZE; i++) {
        for (auto j = 0; j < MATRIX_SIZE; j++) {
            a[i * MATRIX_SIZE + j] = 1.0;
            b[i * MATRIX_SIZE + j] = static_cast<double>(i + 1);
        }
    }

    auto start = std::chrono::steady_clock::now();
    matrix_type c = multiplication(a, b);
    auto end = std::chrono::steady_clock::now();

    delete[] a;
    delete[] b;
    delete[] c;

    papi_retval = PAPI_stop(papi_eventset, papi_values.data());
    if (papi_retval != PAPI_OK) {
        papi_handle_error("PAPI_stop");
    }

    const std::chrono::duration<double> elapsed = end - start;
    constexpr auto flops = 2 * MATRIX_SIZE * MATRIX_SIZE * MATRIX_SIZE;
    const auto capacity = flops / elapsed.count();

    std::cout << "size: " << MATRIX_SIZE << '\n'
              << "flops: " << flops << '\n'
              << "duration: " << elapsed.count() << '\n'
              << "capacity: " << capacity << std::endl;
       
    std::cout << "PAPI_L1_DCM: " << papi_values[0] << '\n'
              << "PAPI_L2_DCM: " << papi_values[1] << '\n'
              << "PAPI_TOT_INS: " << papi_values[2] << '\n'
              << "PAPI_TOT_CYC: " << papi_values[3] << std::endl;

    papi_retval = PAPI_reset(papi_eventset);
    if (papi_retval != PAPI_OK) {
        papi_handle_error("PAPI_reset");
    }

    papi_retval = PAPI_remove_events(papi_eventset, papi_event_codes.data(), papi_event_codes.size());
    if (papi_retval != PAPI_OK) {
        papi_handle_error("PAPI_remove_events");
    }

    papi_retval = PAPI_destroy_eventset(&papi_eventset);
    if (papi_retval != PAPI_OK) {
        papi_handle_error("PAPI_destroy_eventset");
    }

    return 0;
}
