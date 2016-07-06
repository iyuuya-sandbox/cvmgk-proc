// -------------------------------------------------------------------------- //
//! @file   cv_test01.cc
//! @brief  
//! @author vim.ito
//! @since  2016-06-30
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
void DrawTransPinP(cv::Mat& img_dst,
    const cv::Mat trans_img,
    const cv::Mat base_img,
    std::vector<cv::Point2f> tgt_pt,
    double alpha) {
  cv::Mat img_rgb, img_aaa, img_1ma;
  std::vector<cv::Mat>planes_rgba, planes_rgb, planes_aaa, planes_1ma;
  int max_val = pow(2, 8 * base_img.elemSize1()) - 1;

  // 透過画像はRGBA, 背景画像はRGBのみ許容。ビット深度が同じ画像のみ許容
  if (trans_img.data == NULL || base_img.data == NULL) {
    std::cout << "data is NULL";
  } else if (trans_img.channels() < 4 || base_img.channels() < 3) {
    std::cout << "invalid channel: t = " << trans_img.channels()
                              << " b = " << base_img.channels();
  } else if (trans_img.elemSize1() != base_img.elemSize1()) {
    img_dst = cv::Mat(100, 100, CV_8UC3);
    img_dst = cv::Scalar::all(max_val);
    std::cout << "Not match elem size: t = " << trans_img.elemSize1()
                                  << " b = " << base_img.elemSize1();
  }

  // 書き出し先座標が指定されていない場合は背景画像の中央に配置する
  if (tgt_pt.size() < 4) {
    // 座標指定(背景画像の中心に表示する）
    int ltx = (base_img.cols - trans_img.cols) / 2;
    int lty = (base_img.rows - trans_img.rows) / 2;
    int ww  = trans_img.cols;
    int hh  = trans_img.rows;

    tgt_pt.push_back(cv::Point2f(ltx, lty));
    tgt_pt.push_back(cv::Point2f(ltx + ww, lty));
    tgt_pt.push_back(cv::Point2f(ltx + ww, lty + hh));
    tgt_pt.push_back(cv::Point2f(ltx, lty + hh));
  }

  // 変形行列を作成
  std::vector<cv::Point2f> src_pt;
  src_pt.push_back(cv::Point2f(0, 0));
  src_pt.push_back(cv::Point2f(trans_img.cols - 1, 0));
  src_pt.push_back(cv::Point2f(trans_img.cols - 1, trans_img.rows - 1));
  src_pt.push_back(cv::Point2f(0, trans_img.rows - 1));
  cv::Mat mat = cv::getPerspectiveTransform(src_pt, tgt_pt);

  // 出力画像と同じ幅・高さのアルファ付き画像を作成
  cv::Mat alpha0(base_img.rows, base_img.cols, trans_img.type());
  alpha0 = cv::Scalar::all(0);
  cv::warpPerspective(trans_img, alpha0, mat, alpha0.size(),
      cv::INTER_LANCZOS4, cv::BORDER_TRANSPARENT);
  // チャンネルに分解
  cv::split(alpha0, planes_rgba);

  // RGBA画像をRGBに変換
  planes_rgb.push_back(planes_rgba[0]);
  planes_rgb.push_back(planes_rgba[1]);
  planes_rgb.push_back(planes_rgba[2]);
  merge(planes_rgb, img_rgb);

  // RGBA画像からアルファチャンネル抽出
  planes_aaa.push_back(planes_rgba[3] * alpha);
  planes_aaa.push_back(planes_rgba[3] * alpha);
  planes_aaa.push_back(planes_rgba[3] * alpha);
  merge(planes_aaa, img_aaa);

  // 背景用アルファチャンネル
  planes_1ma.push_back(max_val - planes_rgba[3] * alpha);
  planes_1ma.push_back(max_val - planes_rgba[3] * alpha);
  planes_1ma.push_back(max_val - planes_rgba[3] * alpha);
  merge(planes_1ma, img_1ma);

  img_dst = img_rgb.mul(img_aaa, 1.0 / static_cast<double>(max_val)) +
            base_img.mul(img_1ma, 1.0 / static_cast<double>(max_val));
}

cv::Mat composite(cv::Mat fg, cv::Mat bg, float scale, int x, int y, float alpha) {
  int width = fg.cols * scale;
  int height = fg.rows * scale;
  std::vector<cv::Point2f>tgt_pt;

  tgt_pt.push_back(cv::Point2f(x, y));
  tgt_pt.push_back(cv::Point2f(x + width, y));
  tgt_pt.push_back(cv::Point2f(x + width, y + height));
  tgt_pt.push_back(cv::Point2f(x, y + height));

  cv::Mat dst_img;
  DrawTransPinP(dst_img, fg, bg, tgt_pt, alpha);

  return dst_img;
}

int main() {
  auto base = cv::imread("out_000001.png", cv::IMREAD_UNCHANGED);
  auto avatar = cv::imread("avatar_a.png", cv::IMREAD_UNCHANGED);

  auto output = composite(avatar, base, 0.5, 0, 0, 1.0);
  output = composite(avatar, output, 0.25, 768, 0, 1.0);
  output = composite(avatar, output, 0.125, 0, 768, 1.0);
  cv::imwrite("test.png", output);

  /*
  auto overlay = base.clone();
  auto output = base.clone();

  int width = 160;
  int height = 160;
  int x = 32;
  int y = 32;
  double alpha = 0.25;
  // std::string color = "#FF0000";

  cv::rectangle(overlay, cv::Point(x, y), cv::Point(x+width, y+height), hex2scalar("#ff0000"), -1, CV_AA);

  cv::addWeighted(overlay, alpha, output, 1 - alpha, 0, output);
  */


  return 0;
}


/* ========================================================================== */
/*      EOF                                                                   */
/* ========================================================================== */
