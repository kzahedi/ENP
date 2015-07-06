/*************************************************************************
 *                                                                       *
 * This file is part of Evolution of Neural Pathways (ENP).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/ENP                                   *
 *                                                                       *
 * For a list of contributors see the file AUTHORS.                      *
 *                                                                       *
 * YARS is free software; you can redistribute it and/or modify it under *
 * the terms of the GNU General Public License as published by the Free  *
 * Software Foundation; either version 2 of the License, or (at your     *
 * option) any later version.                                            *
 *                                                                       *
 * YARS is distributed in the hope that it will be useful, but WITHOUT   *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE.                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with YARS in the file COPYING; if not, write to the Free        *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor,               *
 * Boston, MA 02110-1301, USA                                            *
 *                                                                       *
 *************************************************************************/



#include "xml_test.h"

#include "data/Data.h"

#include <iostream>
#include <string>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( xmlTest );


void xmlTest::testXml()
{
  string file = "../bin/test.xml";
  Data *d = Data::instance();
  d->read(file);
  
  DataENP              *enp  = d->specification();
  DataEvolution        *evo  = enp->evolution();

  DataEvolutionNeuron  *evon = evo->neuron();
  DataEvolutionSynapse *evos = evo->synapse();
  
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.10, evon->cost(),              0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.11, evon->modifyProbability(), 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.12, evon->modifyMaxValue(),    0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.13, evon->modifyDelta(),       0.000001);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.20, evos->cost(),              0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.21, evos->modifyProbability(), 0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.22, evos->modifyMaxValue(),    0.000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.23, evos->modifyDelta(),       0.000001);
}
