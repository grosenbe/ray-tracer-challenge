#include "Canvas.h"

#include <bits/stdint-uintn.h>

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "Color.h"

using namespace RTC;

using std::endl;
using std::max;
using std::min;
using std::round;
using std::string;
using std::vector;

Canvas::Canvas(const uint32_t width, const uint32_t height) : lineLength(0) {
  data = vector<vector<Color>>(width, vector<Color>(height, Color(0, 0, 0)));
}

const Color&
Canvas::Data(const uint32_t Column, const uint32_t Row) const {
  return data[Column][Row];
}

void
Canvas::WritePixel(const uint32_t Column, const uint32_t Row, const Color& Color) {
  if (Row + 1 > Height() || Column + 1 > Width())
    throw std::runtime_error("Cannot write to a pixel that is off the canvas");

  data[Column][Row] = Color;
}

void
Canvas::PrintPixel(std::ofstream& Output, const double Value, bool LastChar) {
  int numChars = 1;
  if (Value > 99) {
    numChars = 3;
  } else if (Value > 9) {
    numChars = 2;
  }

  if (numChars + lineLength > MAXLINELENGTH) {
    Output << endl;
    lineLength = 0;
  }

  lineLength += numChars;
  Output << round(max(min(Value * 255, 255.), 0.));

  if (lineLength == MAXLINELENGTH || LastChar) {
    lineLength = 0;
    Output << endl;
  } else {
    lineLength += 1;
    Output << " ";
  }
}

void
Canvas::PrintToOutput(std::ofstream& Output, const RTC::Color& Pixel, const bool RowEnd) {
  PrintPixel(Output, Pixel.red());
  PrintPixel(Output, Pixel.green());
  PrintPixel(Output, Pixel.blue(), RowEnd);
}

int
Canvas::CanvasToPPM(const string& FileName) {
  std::ofstream output(FileName);
  output << "P3" << endl;
  output << std::to_string(Width()) + " " + std::to_string(Height()) << endl;
  output << "255" << endl;

  for (auto r = 0u; r < data[0].size(); ++r) {
    for (auto c = 0u; c < data.size(); ++c) {
      PrintToOutput(output, data[c][r], c == data.size() - 1);
    }
  }
  return 0;
}
