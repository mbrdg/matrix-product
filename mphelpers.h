/**
    papihelper.h - helpers for PAPI
    CPA, 2023
    Authors: Miguel Rodrigues & Sérgio Estêvão
*/
#ifndef MPHELPERS_H
#define MPHELPERS_H

#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <papi.h>


namespace cpa::matrix_product {

using matrix_t = double[];
using matrix_size_t = std::size_t;
using duration_t = std::chrono::duration<double>;


struct PAPI_helper {
public:
    PAPI_helper()
    {
        retval = PAPI_library_init(PAPI_VER_CURRENT);
        if (retval != PAPI_VER_CURRENT && retval > 0)
            handle_error("PAPI_library_init");

        retval = PAPI_create_eventset(&eventset);
        if (retval != PAPI_OK)
            handle_error("PAPI_create_eventset");

        retval = PAPI_add_events(eventset, event_codes.data(), event_codes.size());
        if (retval != PAPI_OK)
            handle_error("PAPI_add_events");
    }

    void start()
    {
        retval = PAPI_start(eventset);
        if (retval != PAPI_OK)
            handle_error("PAPI_start");
    }

    void stop()
    {
        retval = PAPI_stop(eventset, values.data());
        if (retval != PAPI_OK)
            handle_error("PAPI_stop");
    }

    void report() const
    {
        std::cout << "PAPI_L1_DCM: " << values[0] << '\n'
                  << "PAPI_L2_DCM: " << values[1] << '\n'
                  << "PAPI_TOT_INS: " << values[2] << '\n'
                  << "PAPI_TOT_CYC: " << values[3] << std::endl;
    }

    ~PAPI_helper()
    {
        retval = PAPI_reset(eventset);
        if (retval != PAPI_OK)
            handle_error("PAPI_reset");

        retval = PAPI_remove_events(eventset, event_codes.data(), event_codes.size());
        if (retval != PAPI_OK)
            handle_error("PAPI_remove_events");

        retval = PAPI_destroy_eventset(&eventset);
        if (retval != PAPI_OK)
            handle_error("PAPI_destroy_eventeset");
    }

private:
    void handle_error(std::string_view callable) const
    {
        std::cerr << callable << " failed with error "
                  << retval << ' '
                  << '(' << PAPI_strerror(retval) << ')' << std::endl;
        std::exit(1);
    }

private:
    std::array<int, 4> event_codes = { PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TOT_INS, PAPI_TOT_CYC };
    std::array<long long, 4> values = { 0, 0, 0, 0 };
    int eventset = PAPI_NULL;
    int retval = 0;
};


constexpr void
fill(matrix_t a, matrix_t b, const matrix_size_t N)
{
    for (matrix_size_t i = 0; i < N; i++) {
        for (matrix_size_t j = 0; j < N; j++) {
            a[i * N + j] = 1.0;
            b[i * N + j] = static_cast<double>(i + 1);
        }
    }
}

void
report(const cpa::matrix_product::PAPI_helper& helper,
       const duration_t& elapsed,
       const matrix_size_t N)
{
    const auto flops = 2 * N * N * N;
    const auto capacity = flops / elapsed.count();
    std::cout << "size: " << N << '\n'
              << "flops: " << flops << '\n'
              << "duration: " << elapsed.count() << '\n'
              << "capacity: " << capacity << std::endl;

    helper.report();
}
}

#endif /* MPHELPERS_H */