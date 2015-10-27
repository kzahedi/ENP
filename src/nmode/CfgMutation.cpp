#include "CfgMutation.h"

#include <iostream>
#include <glog/logging.h>

using namespace std;

CfgMutation::CfgMutation(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _node = NULL;
  _edge = NULL;
}

CfgMutation::~CfgMutation()
{
  if(_node != NULL) delete _node;
  if(_edge != NULL) delete _edge;
}

void CfgMutation::add(ParseElement *element)
{
  VLOG(100) << "parsing: " << element->name();
  if(element->closing(TAG_MUTATION))
  {
    current = parent;
    return;
  }

  if(element->opening(TAG_MUTATION))
  {
    if(_node != NULL) delete _node;
    if(_edge != NULL) delete _edge;
  }

  if(element->opening(TAG_MUTATION_NODE))
  {
    _node = new CfgMutationNode(this);
    current = _node;
    current->add(element);
  }

  if(element->opening(TAG_MUTATION_EDGE))
  {
    _edge = new CfgMutationEdge(this);
    current  = _edge;
    current->add(element);
  }
}

void CfgMutation::createXsd(XsdSpecification *spec)
{
  XsdSequence *root = new XsdSequence(TAG_MUTATION_DEFINITION);
  root->add(NE(TAG_MUTATION_NODE, TAG_MUTATION_NODE_DEFINITION, 1, 1));
  root->add(NE(TAG_MUTATION_EDGE, TAG_MUTATION_EDGE_DEFINITION, 1, 1));
  spec->add(root);

  CfgMutationNode::createXsd(spec);
  CfgMutationEdge::createXsd(spec);
}

CfgMutationNode* CfgMutation::node()
{
  return _node;
}

CfgMutationEdge* CfgMutation::edge()
{
  return _edge;
}

