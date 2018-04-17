#include <iomanip>
#include "catch.hpp"


#include "purify/kernels.h"
#include "purify/pfitsio.h"
#include "purify/utilities.h"

#include "purify/test_data.h"
using namespace purify;
using namespace purify::notinstalled;


TEST_CASE("kernels") {
  const t_uint number_of_samples = kernels_test::kernel_x_values.size();
  for(t_uint i = 0; i < number_of_samples; ++i) {
    // Test that pswf is the same as matlab calculations
    const t_real pswf_difference = std::abs(kernels::pswf(kernels_test::kernel_x_values.at(i), 6) - kernels_test::kernel_pswf_values.at(i));
    CHECK(pswf_difference < 1e-13);
    // Test that kaiser_bessel is the same as matlab calculations
    const t_real kb_difference = std::abs(kernels::kaiser_bessel(kernels_test::kernel_x_values.at(i), 6) - kernels_test::kernel_kb_values.at(i));
    CHECK(kb_difference < 1e-13);
    // Test that gaussian is the same as matlab calculations
    const t_real gauss_difference = std::abs(kernels::gaussian(kernels_test::kernel_x_values.at(i), 6) - kernels_test::kernel_gauss_values.at(i));
    CHECK(gauss_difference < 1e-13);
  }
}


TEST_CASE("kernel_correction"){
 const t_uint number_of_samples = kernels_test::correction_x_values.size();
  for(t_uint i = 0; i < number_of_samples; ++i) {

   const t_real pswf_difference = std::abs(kernels::ft_pswf(kernels_test::correction_x_values.at(i), 6) - kernels_test::correction_pswf_values.at(i));
    CHECK(pswf_difference < 1e-13); // Test that pswf is the same as matlab calculations

   const t_real kb_difference = std::abs(kernels::ft_kaiser_bessel(kernels_test::correction_x_values.at(i), 6) - kernels_test::correction_kb_values.at(i));
    CHECK(kb_difference < 1e-13); // Test that kaiser_bessel is the same as matlab calculations

    const t_real gauss_difference = std::abs(kernels::ft_gaussian(kernels_test::correction_x_values.at(i), 6) - kernels_test::correction_gauss_values.at(i));
    CHECK(gauss_difference < 1e-13); // Test that gaussian is the same as matlab calculations
  }
}

