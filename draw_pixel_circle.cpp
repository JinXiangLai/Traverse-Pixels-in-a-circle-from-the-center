// http://cimg.eu/reference/group__cimg__tutorial.html

#include <iostream>
#include <string>
#include "CImg/CImg.h"

using namespace cimg_library;
using namespace std;

constexpr uint8_t kColor[3][3] = {
    {255, 0, 0}, {0, 255, 0}, {0, 0, 255}};  // red, blue, green

float cal_distance(const float center_x, const float center_y, const float x,
                   const float y) {
  return sqrt(pow(x - center_x, 2.) + pow(y - center_y, 2.));
}

void set_pixel(const int x, const int y, CImg<uint8_t>* img) {
  if (x < 0 || x >= img->_width || y < 0 || y >= img->_height) {
    return;
  } else {
    const uint8_t* color = kColor[rand()%3];
    for (int c = 0; c < 3; ++c) {
      (*img)(x, y, c) = color[c];
    }
  }
}

void set_pixel_and_display(const int x, const int y, CImgDisplay& main_window,
                           CImg<uint8_t>* img) {
  if (x < 0 || x >= img->_width || y < 0 || y >= img->_height) {
    return;
  } else {
    const uint8_t* color = kColor[rand()%3];
    for (int c = 0; c < 3; ++c) {
      (*img)(x, y, c) = color[c];
    }
  }
  main_window.display(*img);
  main_window.resize();
  // sleep(0.01);
}

int main(int argc, char** argv) {
  // image config
  const int width = 320;
  const int height = 240;
  const int center_x = 320 / 2;
  const int center_y = 240 / 2;
  const float radius = 50;

  // for avoidding unnecessary distance calculations
  const int test_loop = radius * cos(45. / 180. * M_PI);

  // Create 3-channel RGB image
  CImg<uint8_t> img(width, height, 1, 3);

  // Create main window
  CImgDisplay main_window(img, "Random Data", 1);
  int frame = 0;

  while (!main_window.is_closed()) {
    img.rand(0, 0);
    int ring_num = 0;
    while (ring_num < int(radius)) {
      ++ring_num;
      int boundary[4] = {center_x - ring_num, center_y - ring_num,
                         center_x + ring_num, center_y + ring_num};
      // for loop top row
      for (int i = boundary[0]; i <= boundary[2]; ++i) {
        int x = i;
        const int y = boundary[1];
        if (ring_num > test_loop &&
            cal_distance(center_x, center_y, x, y) > radius)
          continue;
        // set_pixel(x, y, &img);
        set_pixel_and_display(x, y, main_window, &img);
      }
      // for loop right column
      for (int i = boundary[1] + 1; i <= boundary[3]; ++i) {
        const int x = boundary[2];
        int y = i;
        if (ring_num > test_loop &&
            cal_distance(center_x, center_y, x, y) > radius)
          continue;
        // set_pixel(x, y, &img);
        set_pixel_and_display(x, y, main_window, &img);
      }
      // for loop down row
      for (int i = boundary[2] - 1; i >= boundary[0]; --i) {
        int x = i;
        const int y = boundary[3];
        if (ring_num > test_loop &&
            cal_distance(center_x, center_y, x, y) > radius)
          continue;
        // set_pixel(x, y, &img);
        set_pixel_and_display(x, y, main_window, &img);
      }
      // for loop left column
      for (int i = boundary[3] - 1; i > boundary[1]; --i) {
        const int x = boundary[0];
        int y = i;
        if (ring_num > test_loop &&
            cal_distance(center_x, center_y, x, y) > radius)
          continue;
        // set_pixel(x, y, &img);
        set_pixel_and_display(x, y, main_window, &img);
      }
    }

    // display image
    main_window.display(img);
    main_window.resize();  // allow image adaptive window size
    frame++;
    std::cout << "Frame: " << frame << std::endl;
    sleep(1.);
  }
  return 0;
}