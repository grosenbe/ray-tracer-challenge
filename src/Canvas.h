#ifndef CANVAS_H
#define CANVAS_H
#include <bits/stdint-uintn.h>

#include <fstream>
#include <vector>

#include "Color.h"
namespace RTC {
constexpr int MAXLINELENGTH = 70;
class Canvas {
 public:
  Canvas(const uint32_t, const uint32_t);

  size_t
  Width() const { return data.size(); }

  size_t
  Height() const { return data[0].size(); }

  const Color&
  Data(const uint32_t, const uint32_t) const;

  void WritePixel(const uint32_t, const uint32_t, const Color&);

  int CanvasToPPM(const std::string&);

 private:
  void PrintToOutput(std::ofstream&, const RTC::Color&, const bool RowEnd);
  void PrintPixel(std::ofstream&, const double, const bool LastChar = false);

  std::vector<std::vector<RTC::Color>> data;
  int lineLength;
};
}  // namespace RTC
#endif
