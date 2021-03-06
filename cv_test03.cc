// -------------------------------------------------------------------------- //
//! @file   cv_test02.cc
//! @brief  
//! @author vim.ito
//! @since  2016-07-06
//!
//! COPYRIGHT (C) 2016 1PAC ALL RIGHTS RESERVED
// -------------------------------------------------------------------------- //
/* ====< Include >=========================================================== */
#include <opencv2/highgui/highgui.hpp>

/* ====< Define >============================================================ */
int main() {
  auto base = cv::imread("naoki.png", cv::IMREAD_UNCHANGED);
  cv::imwrite("naoki_out.png", base);
  return 0;
}


/* ========================================================================== */
/*      EOF                                                                   */
/* ========================================================================== */
