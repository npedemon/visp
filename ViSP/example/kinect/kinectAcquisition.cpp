/****************************************************************************
 *
 * $Id$
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2011 by INRIA. All rights reserved.
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact INRIA about acquiring a ViSP Professional
 * Edition License.
 *
 * See http://www.irisa.fr/lagadic/visp/visp.html for more information.
 *
 * This software was developed at:
 * INRIA Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 * http://www.irisa.fr/lagadic
 *
 * If you have questions regarding the use of this file, please contact
 * INRIA at visp@inria.fr
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 * Description:
 * Kinect example.
 *
 * Authors:
 * C�line Teuli�re
 *
 *****************************************************************************/


/*!
  \example kinectAcquisition.cpp

  \brief Example that shows how to acquire depth map and RGB images from a kinect device.

*/

#include <iostream>
#include <visp/vpConfig.h>

#ifdef VISP_HAVE_LIBFREENECT

#if (defined (VISP_HAVE_X11) || defined(VISP_HAVE_GTK) || defined(VISP_HAVE_OPENCV) || defined(VISP_HAVE_GDI))	


#include <visp/vpImage.h>
#include <visp/vpDisplayX.h>
#include <visp/vpDisplayGTK.h>
#include <visp/vpDisplayOpenCV.h>
#include <visp/vpDisplayGDI.h>
#include <visp/vpKinect.h>

int main() {
  // Init Kinect
  Freenect::Freenect<vpKinect> freenect;
  vpKinect & kinect = freenect.createDevice(0);
  kinect.start(); // Start acquisition thread

  // Set tilt angle
  float angle = -5;
  kinect.setTiltAngle(angle);

  // Init display
  vpImage<unsigned char> I(480,640);
  vpImage<vpRGBa> Irgb(480,640);
  vpImage<float> dmap(480,640);

#if defined VISP_HAVE_X11
  vpDisplayX display;
  vpDisplayX displayRgb;
#elif defined VISP_HAVE_GTK
  vpDisplayGTK display;
  vpDisplayGTK displayRgb;
#elif defined VISP_HAVE_OPENCV
  vpDisplayOpenCV display;
  vpDisplayOpenCV displayRgb;
#elif defined VISP_HAVE_GDI
  vpDisplayGDI display;
  vpDisplayGDI displayRgb;
#endif

  display.init(I, 100, 200,"Depth map");
  displayRgb.init(Irgb, 900, 200,"Color Image");

  // A click to stop acquisition
  while(!vpDisplay::getClick(I,false))
    {
      kinect.updateState();
      kinect.getDepthMap(dmap,I);
      kinect.getRGB(Irgb);

      vpDisplay::display(I);
      vpDisplay::flush(I);
      vpDisplay::display(Irgb);
      vpDisplay::flush(Irgb);
    }
  kinect.stop(); // Stop acquisition thread
  return 0;
}

#else

int
main()
{
  std::cout << "You should install a vide device (X11, GTK, OpenCV, GDI) to run this example" << std::endl;
}
#endif

#else
int
main()
{
  std::cout << "You should install libfreenect to run this example" << std::endl;
}

#endif


