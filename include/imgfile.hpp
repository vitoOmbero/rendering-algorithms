#ifndef IMGFILE_HXX_
#define IMGFILE_HXX_

#include <array>
#include <fstream>

#include "rgb888.h"

namespace data_export
{
class imgFile {
  std::string const fileName_;

 public:
  imgFile() = delete;
  imgFile(std::string fileName)
      : fileName_(fileName)
  {
  }

  public:
  template <size_t N>
  void save_p6(const std::array<ra_types::Rgb888, N>& image, size_t width,
               size_t height)
  {
      std::ofstream out_file;
      out_file.exceptions(std::ios_base::failbit);

      out_file.open(fileName_, std::ios_base::binary);

      out_file << "P6\n" << width << ' ' << height << ' ' << 255 << '\n';
      out_file.write(reinterpret_cast<const char*>(&image),
                     sizeof(ra_types::Rgb888) * N);
  }
};
} // namespace data_export

#endif /* IMGFILE_HXX_ */
