#include <Magick++.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace Magick;

Magick::Image composite(const Magick::Image& _avatar, const Magick::Image& _video_image, double alpha);

int main() {
  Magick::Image video_image("out_000001.png");
  Magick::Image avatar("avatar_b.png");


  std::stringstream ss;
  composite(avatar, video_image, 0.0).write("hoge-0.0.png");
  composite(avatar, video_image, 0.1).write("hoge-0.1.png");
  composite(avatar, video_image, 0.2).write("hoge-0.2.png");
  composite(avatar, video_image, 0.3).write("hoge-0.3.png");
  composite(avatar, video_image, 0.4).write("hoge-0.4.png");
  composite(avatar, video_image, 0.5).write("hoge-0.5.png");
  composite(avatar, video_image, 0.6).write("hoge-0.6.png");
  composite(avatar, video_image, 0.7).write("hoge-0.7.png");
  composite(avatar, video_image, 0.8).write("hoge-0.8.png");
  composite(avatar, video_image, 0.9).write("hoge-0.9.png");
  composite(avatar, video_image, 1.0).write("hoge-1.0.png");

  return 0;
}

Magick::Image composite(const Magick::Image& _avatar, const Magick::Image& _video_image, double alpha) {
  Magick::Image avatar = _avatar;
  Magick::Image video_image = _video_image;
  double scale = 0.5;
  int x = 0, y = 0;

  int opacity = MaxRGB * (1-alpha);

  Magick::PixelPacket *pixels = avatar.getPixels(0, 0, avatar.columns(), avatar.rows());
  for (int j = 0; j < avatar.rows(); j++) {
    for (int i = 0; i < avatar.columns(); i++) {
      int ind = i*avatar.columns() + j;
      if (pixels[ind].opacity != MaxRGB)
        pixels[ind].opacity = opacity;
    }
  }
  avatar.syncPixels();

  video_image.composite(avatar, Magick::Geometry(0, 0, x, y), Magick::OverCompositeOp);
  video_image.magick("PNG");

  return video_image;
}
