/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013-2020 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 */

#define BOOST_TEST_MODULE ndn-cxx
#include "tests/boost-test.hpp"

#ifdef _WIN32
#include <windows.h>

// Speed up tests by reducing the mininum sleep time to 1ms.
// By default, Windows has a very coarse scheduling policy, which
// makes it very slow to run the unit tests. The following call
// changes the policy to use finer resolution in time.
// https://docs.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod
//
struct InitializeFixture {
  InitializeFixture()   {
      timeBeginPeriod(1);

      // This initial sleep call gives the scheduler time to switch resolution.
      // Without this call, short Sleep calls called too early get ignored
      // intermittently, causing tests to fail unpredictably.
      Sleep(1000);
  }
  ~InitializeFixture()  {
      timeEndPeriod(1);
  }
};

BOOST_TEST_GLOBAL_FIXTURE(InitializeFixture);
#endif // ifdef _WIN32
