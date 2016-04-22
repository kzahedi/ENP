/*************************************************************************
 *                                                                       *
 * This file is part of Yet Another Robot Simulator (YARS).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/YARS                                  *
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


#ifndef __NMODE_YARS_XSD_SAX_PARSER_H__
#define __NMODE_YARS_XSD_SAX_PARSER_H__

#include <vector>
#include <string>

using namespace std;

/**
 * @brief This class reads an XML file, validates it against the XML Schema
 * Grammar generated by YarsXSDGenerator, which was specified in
 * XsdSpecification, and stores the content of the XML file in
 * DataRobotSimulationDescription (singleton)
 * @sa YarsXSDGenerator
 * @sa XsdSpecification
 * @sa DataRobotSimulationDescription
 */
class YarsXSDSaxParser
{
  public:
    /**
     * @brief Read xml file.
     *
     * @param filename
     *
     * @return true/false if parse has failed or was successful
     */
    bool read(string filename);

    bool parse(string xml);

    std::vector<string>::iterator e_begin();
    std::vector<string>::iterator e_end();
    int e_size();

    std::vector<string>::iterator f_begin();
    std::vector<string>::iterator f_end();
    int f_size();

    std::vector<string>::iterator w_begin();
    std::vector<string>::iterator w_end();
    int w_size();

    int errors();

  private:
    std::vector<string> _errors;
    std::vector<string> _warnings;
    std::vector<string> _fatals;
};

#endif // __YARS_XSD_SAX_PARSER_H__


