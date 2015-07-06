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



#ifndef __DATA_EVOLUTION_NEURON_H__
#define __DATA_EVOLUTION_NEURON_H__

#include "DataNode.h"
#include "Version.h"

# define TAG_EVOLUTION_NEURON            (char*)"neuron"
# define TAG_EVOLUTION_NEURON_DEFINITION (char*)"neuron_evolution_definition"

class DataEvolutionNeuron : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataEvolutionNeuron(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataEvolutionNeuron();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

    double modifyProbability();
    double modifyMaxValue();
    double modifyDelta();
    double addProbability();
    double addMaxValue();
    double delProbability();
    double cost();

  private:

    double _modifyProbability;
    double _modifyMaxValue;
    double _modifyDelta;
    double _addProbability;
    double _addMaxValue;
    double _delProbability;
    double _cost;


};

#endif // ___DATA_EVOLUTION_NEURON_H__


