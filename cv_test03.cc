// -------------------------------------------------------------------------- //
//! @file   cv_test02.cc
//! @brief  
//! @author vim.ito
//! @since  2016-07-06
//!
//! COPYRIGHT (C) 2016 1PAC ALL RIGHTS RESERVED
// -------------------------------------------------------------------------- //
/* ====< Include >=========================================================== */
#include <iostream>
#include <iomanip>
#include <sstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/* ====< Define >============================================================ */
int main() {
  auto base = cv::imread("out_000238.png", cv::IMREAD_UNCHANGED);

  cv::imwrite("test.png", base);

  return 0;
}


/* ========================================================================== */
/*      EOF                                                                   */
/* ========================================================================== */
