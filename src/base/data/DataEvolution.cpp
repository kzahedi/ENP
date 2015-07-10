#include "DataEvolution.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

DataEvolution::DataEvolution(DataNode *parent)
  : DataNode(parent)
{ }

DataEvolution::~DataEvolution()
{
  delete _node;
  delete _edge;
}


void DataEvolution::add(DataParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_EVOLUTION))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_EVOLUTION))
  {
    return;
  }

  if(element->opening(TAG_EVOLUTION_NODE))
  {
    _node = new DataEvolutionNode(this);
    current = _node;
    current->add(element);
  }

  if(element->opening(TAG_EVOLUTION_EDGE))
  {
    _edge = new DataEvolutionEdge(this);
    current  = _edge;
    current->add(element);
  }

}

void DataEvolution::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_EVOLUTION_DEFINITION);
  root->add(NE(TAG_EVOLUTION_NODE,  TAG_EVOLUTION_NODE_DEFINITION,  1, 1));
  root->add(NE(TAG_EVOLUTION_EDGE, TAG_EVOLUTION_EDGE_DEFINITION, 1, 1));
  spec->add(root);

  DataEvolutionNode::createXsd(spec);
  DataEvolutionEdge::createXsd(spec);
}

DataEvolutionNode* DataEvolution::node()
{
  return _node;
}

DataEvolutionEdge* DataEvolution::edge()
{
  return _edge;
}

