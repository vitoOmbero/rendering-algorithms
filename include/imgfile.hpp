/*
 * imgFleMan.hxx
 *
 *  Created on: Oct 4, 2018
 *      Author: vito
 */

#ifndef IMGFILE_HXX_
#define IMGFILE_HXX_

#include <array>
#include <fstream>

#include "rgb_color.hpp"

namespace simple_drawing {
class imgFile {
  std::string const fileName_;

 public:
  imgFile() = delete;
  imgFile(std::string fileName) : fileName_(fileName) {}

 public:
  // NOTE: this is the reason of template virus in tests
  template <size_t N>
  void save_p6(const std::array<rgb_color, N>& image, size_t width, size_t height) {
    std::ofstream out_file;
    out_file.exceptions(std::ios_base::failbit);

    out_file.open(fileName_, std::ios_base::binary);

    out_file << "P6\n" << width << ' ' << height << ' ' << 255 << '\n';
    out_file.write(reinterpret_cast<const char*>(&image), sizeof(rgb_color) * N);
  }
};
}  // namespace simple_drawing

#endif /* IMGFILE_HXX_ */
