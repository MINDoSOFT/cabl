/*
        ##########    Copyright (C) 2015 Vincenzo Pacella
        ##      ##    Distributed under MIT license, see file LICENSE
        ##      ##    or <http://opensource.org/licenses/MIT>
        ##      ##
##########      ############################################################# shaduzlabs.com #####*/

#include <catch.hpp>
#include <gfx/displays/LedMatrixMaschineJam.h>

#include "gfx/CanvasTestFunctions.h"
#include "gfx/CanvasTestHelpers.h"

//--------------------------------------------------------------------------------------------------

namespace sl
{
namespace cabl
{
namespace test
{

//--------------------------------------------------------------------------------------------------

TEST_CASE("LedMatrixMaschineJam: constructor", "[gfx][displays][LedMatrixMaschineJam]")
{
  LedMatrixMaschineJam display;

  CHECK(display.width() == 8);
  CHECK(display.height() == 8);
  CHECK(display.numberOfChunks() == 1);

  CHECK(display.pixel(8, 8) == Color());

  Color testColor = Color(48, 88, 255);
  display.setPixel(0, 0, testColor);
  auto color = display.pixel(0, 0);
  display.setPixel(0, 0, color);
  CHECK(color == display.pixel(0, 0));
  CHECK(color == testColor);
}

//--------------------------------------------------------------------------------------------------

} // namespace test
} // namespace cabl
} // namespace sl
