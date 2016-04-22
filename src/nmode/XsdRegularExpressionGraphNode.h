#ifndef __XSD_REGULAR_EXPRESSION_GRAPH_NODE_H__
#define __XSD_REGULAR_EXPRESSION_GRAPH_NODE_H__

#include <nmode/XsdGraphNode.h>
#include <nmode/XsdRegularExpression.h>

#include <string>
#include <sstream>

using namespace std;

class XsdRegularExpressionGraphNode : public XsdGraphNode
{
  public:
    XsdRegularExpressionGraphNode(XsdRegularExpression *spec);
    string customLabel(string label);
    string name();
    XsdRegularExpression* spec();

  private:
    stringstream          _oss;
    XsdRegularExpression *_spec;
    string                _specification;
    string                _type;
};

#endif // __XSD_REGULAR_EXPRESSION_GRAPH_NODE_H__
