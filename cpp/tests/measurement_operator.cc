#include "catch.hpp"
#include "MeasurementOperator.h"
#include <iostream>

using namespace purify;

TEST_CASE("Measurement Operator", "[Gridding]") {
  MeasurementOperator op;
  MeasurementOperator::vis_params uv_vis1;
  MeasurementOperator::vis_params uv_vis;
  t_real max;
  t_real max_diff;
  t_int over_sample;
  t_real cellsize;
  std::string kernel;
  MeasurementOperator::operator_params st;
  

  //Gridding example
  over_sample = 2;
  t_int J = 6;
  uv_vis = op.read_visibility("../data/vla/at166B.3C129.c0.vis");
  cellsize = 0.3;
  uv_vis = op.set_cell_size(uv_vis, cellsize);
  uv_vis = op.uv_scale(uv_vis, 1024 * over_sample, 1024 * over_sample);
  uv_vis = op.uv_symmetry(uv_vis);
  

  SECTION("Kaiser Bessel Gridding") {
    kernel = "kb";
    st = op.init_nufft2d(uv_vis.u, uv_vis.v, J, J, kernel, 1024, 1024, over_sample);
    Image<t_real> kb_img = op.grid(uv_vis.vis, st).real();
    max = kb_img.maxCoeff();
    kb_img = kb_img / max;

    Image<t_real> kb_test_image = op.readfits2d("../data/expected/gridding/at166BtestJ6kb.fits").real();
    Image<t_real> kb_difference = kb_img - kb_test_image;
    max_diff = kb_difference.abs().maxCoeff();
    std::cout << "Percentage max difference in Kaiser Bessel gridding: " << max_diff * 100 << "%" << '\n';
    for (t_int i = 0; i < kb_test_image.cols(); ++i)
    {
      for (t_int j = 0; j < kb_test_image.rows(); ++j)
      {
        if (std::abs(kb_difference(j, i)) >= 0.03)
        {
          std::cout << i << " " << j << '\n';
        }
        CHECK( std::abs(kb_difference(j, i)) < 0.005 );
      }
    }
  }
  SECTION("Prolate Spheroidal Wave Functon Gridding") {
    kernel = "pswf";
    st = op.init_nufft2d(uv_vis.u, uv_vis.v, J, J, kernel, 1024, 1024, over_sample);
    Image<t_real> pswf_img = op.grid(uv_vis.vis, st).real();
    max = pswf_img.maxCoeff();
    pswf_img = pswf_img / max;

    Image<t_real> pswf_test_image = op.readfits2d("../data/expected/gridding/at166BtestJ6pswf.fits").real();
    Image<t_real> pswf_difference = pswf_img - pswf_test_image;
    max_diff = pswf_difference.abs().maxCoeff();
    std::cout << "Percentage max difference in Prolate Spheroidal Wave Functon gridding: " << max_diff * 100 << "%" << '\n';
    for (t_int i = 0; i < pswf_test_image.cols(); ++i)
    {
      for (t_int j = 0; j < pswf_test_image.rows(); ++j)
      {
        if (std::abs(pswf_difference(j, i)) >= 0.03)
        {
          std::cout << i << " " << j << '\n';
        }
        CHECK( std::abs(pswf_difference(j, i)) < 0.005 );

      }
    }
  }
  SECTION("Guassian Gridding") {
    kernel = "gauss";
    st = op.init_nufft2d(uv_vis.u, uv_vis.v, J, J, kernel, 1024, 1024, over_sample);
    Image<t_real> gauss_img = op.grid(uv_vis.vis, st).real();
    max = gauss_img.maxCoeff();
    gauss_img = gauss_img / max;

    Image<t_real> gauss_test_image = op.readfits2d("../data/expected/gridding/at166BtestJ6gauss.fits").real();
    Image<t_real> gauss_difference = gauss_img - gauss_test_image;
    max_diff = gauss_difference.abs().maxCoeff();
    std::cout << "Percentage max difference in Guassian gridding: " << max_diff * 100 << "%" << '\n';
    for (t_int i = 0; i < gauss_test_image.cols(); ++i)
    {
      for (t_int j = 0; j < gauss_test_image.rows(); ++j)
      {
        if (std::abs(gauss_difference(j, i)) >= 0.03)
        {
          std::cout << i << " " << j << '\n';
        }
        CHECK( std::abs(gauss_difference(j, i)) < 0.005 );

      }
    }
  }  

}

TEST_CASE("Measurement Operator", "[Degridding]") {
  MeasurementOperator op;
  MeasurementOperator::vis_params uv_vis1;
  MeasurementOperator::vis_params uv_vis;
  t_real max;
  t_real max_diff;
  t_int over_sample;
  t_real cellsize;
  std::string kernel;
  MeasurementOperator::operator_params st;
  Image<t_complex> img;

  //Gridding example
  over_sample = 2;
  t_int J = 6;
  uv_vis = op.read_visibility("../data/vla/at166B.3C129.c0.vis");
  cellsize = 0.3;
  uv_vis = op.set_cell_size(uv_vis, cellsize);
  uv_vis = op.uv_scale(uv_vis, 1024 * over_sample, 1024 * over_sample);
  uv_vis = op.uv_symmetry(uv_vis);
  

  SECTION("Kaiser Bessel Gridding") {
    kernel = "kb";
    st = op.init_nufft2d(uv_vis.u, uv_vis.v, J, J, kernel, 1024, 1024, over_sample);
    img = op.readfits2d("../data/images/M31.fits");
    max = img.real().maxCoeff();
    img = img / max;
    Vector<t_complex> kb_vis = op.degrid(img, st);
    Vector<t_complex> kb_test_vis = op.read_visibility("../data/expected/degridding/M31J6kb.vis").vis;
    Vector<t_complex> kb_vis_difference = kb_vis - kb_test_vis;
    max_diff = kb_vis_difference.cwiseAbs().maxCoeff();
    std::cout << "Percentage max difference in Kaiser Bessel degridding: " << max_diff * 100 << "%" << '\n';
  }
}