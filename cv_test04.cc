// -------------------------------------------------------------------------- //
//! @file   cv_test04.cc
//! @brief  
//! @author vim.ito
//! @since  2016-07-11
//!
//! COPYRIGHT (C) 2016 1PAC ALL RIGHTS RESERVED
// -------------------------------------------------------------------------- //
/* ====< Include >=========================================================== */
#include <iostream>
#include <sstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/* ====< Define >============================================================ */
cv::Mat create_text_image(const std::string& text, int font_size) {
  std::stringstream ss;
  ss << "convert"
     << " -format PNG32"
     << " -depth 8"
     << " -background transparent"
     << " -fill '#123456'"
     << " -pointsize " << font_size
     << " label:'" << text << "'"
     << " tmp.png";
  std::string cmd = ss.str();
  system(cmd.c_str());
  auto base = cv::imread("tmp.png", cv::IMREAD_UNCHANGED);
  system("rm tmp.png");

  std::vector<cv::Mat>planes_rgba;
  cv::split(base, planes_rgba);
  // int max_val = pow(2, 8 * base.elemSize1()) - 1;
  planes_rgba[0] *= 0.01;
  planes_rgba[1] *= 0.01;
  planes_rgba[2] *= 0.01;
  cv::Mat img(base.cols, base.rows, CV_8UC4);
  merge(planes_rgba, img);
  return img;
}

int main() {
  auto img = create_text_image("Naoki", 90);
  cv::imwrite("naoki_out.png", img);
  return 0;
}
/* ========================================================================== */
/*      EOF                                                                   */
/* ========================================================================== */
