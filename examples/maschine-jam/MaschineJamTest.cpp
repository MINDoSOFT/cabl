/*
        ##########    Copyright (C) 2015 Vincenzo Pacella
        ##      ##    Distributed under MIT license, see file LICENSE
        ##      ##    or <http://opensource.org/licenses/MIT>
        ##      ##
##########      ############################################################# shaduzlabs.com #####*/

#include "MaschineJamTest.h"

#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>


#include <unmidify.hpp>

#include <cabl/gfx/TextDisplay.h>

//--------------------------------------------------------------------------------------------------

namespace
{
const sl::Color kColor_Black{0};
const sl::Color kColor_Red{0xff, 0, 0, 0xff};
const sl::Color kColor_Yellow{0xff, 0xff, 0, 0x55};
const sl::Color kColor_Blue{0xff, 0, 0, 0x77};
}

//--------------------------------------------------------------------------------------------------

namespace sl
{

using namespace midi;
using namespace cabl;
using namespace std::placeholders;

//--------------------------------------------------------------------------------------------------

void MaschineJamTest::initDevice()
{
  std::cout << "The device has "
            << std::to_string(device()->numOfLedArrays()) 
      << " led arrays."
      << std::endl;
  for(unsigned i  = 0; i< device()->numOfLedArrays(); i++)
  {
    device()->ledArray(i)->setValue(0.5, kColor_Blue);
  }

    std::cout << "The device has " << std::to_string(device()->numOfLedMatrices()) << " led matrices."
            << std::endl;
  device()->ledMatrix(0)->white();
  for (unsigned i = 0; i < device()->numOfLedMatrices(); i++)
  {
    Canvas* ledMatrix = device()->ledMatrix(i);
    unsigned int width = ledMatrix->width();
    unsigned int height = ledMatrix->height();
    std::cout << "LedMatrix " << std::to_string(i) << " Width = " << std::to_string(width) << " Height = " << std::to_string(height) << std::endl;

    
    for (unsigned x = 0; x < width; x++)
    {
      for (unsigned y = 0; y < height; y++)
      {
        //std::cout << "Trying to set pixel at x = " << std::to_string(x) << " y = " << std::to_string(y) << std::endl;
        ledMatrix->setPixel(x, y, kColor_Blue);
      }
    }
  }
  
      std::cout << "The device has " << std::to_string(device()->numOfGraphicDisplays())
            << " graphic displays."
            << std::endl;
  for(unsigned i  = 0; i< device()->numOfGraphicDisplays(); i++)
  {
    unsigned w = device()->graphicDisplay(i)->width();
    unsigned h = device()->graphicDisplay(i)->height();
    device()->graphicDisplay(i)->black();
    device()->graphicDisplay(i)->line(0, 0, w, h, {0xff});
    device()->graphicDisplay(i)->line(0, h, w, 0, {0xff});
    device()->graphicDisplay(i)->line(w/2, h, w/2, 0, {0xff});
    device()->graphicDisplay(i)->line(0, h/2, w, h/2, {0xff});
    device()->graphicDisplay(i)->rectangle(0, 0, w, h, {0xff});
    device()->graphicDisplay(i)->circle(w/2, h/2, w/2, {0xff});
    device()->graphicDisplay(i)->circle(w/2, h/2, h/2, {0xff});
  }

  
}

//--------------------------------------------------------------------------------------------------

void MaschineJamTest::render()
{
}

//--------------------------------------------------------------------------------------------------

void MaschineJamTest::buttonChanged(Device::Button button_, bool buttonState_, bool shiftState_)
{
  device()->setButtonLed(
    button_, buttonState_ ? (shiftState_ ? kColor_Red : kColor_Yellow) : kColor_Black);
}

//--------------------------------------------------------------------------------------------------

void MaschineJamTest::encoderChanged(unsigned encoder_, bool valueIncreased_, bool shiftPressed_)
{
  std::string value = "Enc#" + std::to_string(static_cast<int>(encoder_)) + ( valueIncreased_ ? " increased" : " decreased" );

  device()->textDisplay(0)->putText(value.c_str(), 0);

  device()->graphicDisplay(0)->black();
  device()->graphicDisplay(0)->putText(10, 10, value.c_str(), {0xff});

}

//--------------------------------------------------------------------------------------------------

void MaschineJamTest::keyChanged(unsigned index_, double value_, bool shiftPressed_)
{
  device()->setKeyLed(index_, {static_cast<uint8_t>(value_ * 0xff)});
}

//--------------------------------------------------------------------------------------------------

void MaschineJamTest::controlChanged(unsigned pot_, double value_, bool shiftPressed_)
{
  std::string value = "Pot#" + std::to_string(static_cast<int>(pot_)) + " " + std::to_string(static_cast<int>(value_ * 100));

  device()->textDisplay(0)->putText(value.c_str(), 0);

  device()->graphicDisplay(0)->black();
  device()->graphicDisplay(0)->putText(10, 10, value.c_str(), {0xff});
  
  device()->ledArray(pot_)->setValue(value_, kColor_Red);
}

//--------------------------------------------------------------------------------------------------

} // namespace sl
