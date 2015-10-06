#include "Exporter.h"

#include <sstream>
#include <math.h>

#include "base/macros.h"
#include "base/Individual.h"
#include "glog/logging.h"

#define XML_BOOL(a) (a?"true":"false")
#define ZERO(a)     ((fabs(a)<0.0000000000001)?0:a)


string Exporter::toXml(Module *m)
{
  stringstream sst;
  sst << "      <module name=\"" << m->name() << "\">" << endl;
  if(m->isCopy())
  {
    sst << "        <copy      name=\"" << m->ref() << "\"/>" << endl;
    MirrorAxes ma = m->mirrorAxes();
    Quaternion q = m->rotation();
    P3D        r;
    r << q;
    P3D        p = m->translation();
    sst << "        <mirror    x=\"" << XML_BOOL(ma.x)
                     << "\" y=\"" << XML_BOOL(ma.y)
                     << "\" z=\"" << XML_BOOL(ma.z)
                     << "\"/>" << endl;
    sst << "        <rotate    x=\"" << RAD_TO_DEG(r.x)
                     << "\" y=\"" << RAD_TO_DEG(r.y)
                     << "\" z=\"" << RAD_TO_DEG(r.z)
                     << "\"/>" << endl;
    sst << "        <translate x=\"" << p.x
                        << "\" y=\"" << p.y
                        << "\" z=\"" << p.z
                        << "\"/>" << endl;
  }
  else
  {
    for(Nodes::const_iterator n = m->n_begin(); n != m->n_end(); n++)
    {
      sst << "        <node type=\"" << (*n)->type()
        << "\" label=\"" << (*n)->label() << "\">" << endl;
      sst << "          <position x=\"" << (*n)->position().x
        << "\" y=\"" << (*n)->position().y
        << "\" z=\"" << (*n)->position().z
        << "\"/>" << endl;
      sst << "          <transferfunction name=\"" << (*n)->transferfunction()
        << "\"/>" << endl;
      sst << "          <bias value=\"" << ZERO((*n)->bias()) << "\"/>" << endl;
      sst << "        </node>" << endl;
    }
    for(Edges::const_iterator e = m->e_begin(); e != m->e_end(); e++)
    {
      sst << "        <edge source=\"" << (*e)->sourceNode()->label()
        << "\" destination=\"" << (*e)->destinationNode()->label() << "\" weight=\""
        << (*e)->weight()<< "\"/>" << endl;
    }
  }
  sst << "      </module>" << endl;
  return sst.str();
}

string Exporter::toXml(Individual *i)
{
  stringstream sst;
  sst << "    <individual"
    << " id=\""      << i->id()      << "\""
    << " fitness=\"" << i->fitness() << "\""
    << ">" << endl;

  for(Modules::const_iterator m = i->m_begin(); m != i->m_end(); m++)
  {
    sst << toXml(*m);
  }
  sst << "    </individual>" << endl;
  return sst.str();
}

string Exporter::toXml(Population *pop)
{
  stringstream sst;
  sst <<"  <population generation=\"" << pop->generation() << "\">" << endl;

  for(Individuals::const_iterator i  = pop->i_begin(); i != pop->i_end(); i++)
  {
    sst << toXml(*i);
  }
  sst <<"  </population>" << endl;

  return sst.str();
}

string Exporter::__x3dHeader()
{
  stringstream sst;
  sst << endl;
  sst << "<html> " << endl;
  sst << "  <head> " << endl;
  sst << "    <title>My first X3DOM page</title>      " << endl;
  sst << "    <script type='text/javascript' src='x3dom.js'> </script> " << endl;
  sst << "    <link rel='stylesheet' type='text/css' href='x3dom.css'></link> " << endl;
  sst << "  </head> " << endl;
  sst << "  <body> " << endl;
  sst << "    <center>" << endl;
  return sst.str();
}

string Exporter::__x3dFooter()
{
  stringstream sst;
  sst << "      </x3d> " << endl;
  sst << "    </center>" << endl;
  sst << "  </body> " << endl;
  sst << "</html>    " << endl;
  return sst.str();
}

string Exporter::toX3d(Individual *i)
{
  stringstream sst;
  sst << __x3dHeader();
  sst << "      <p> " << endl;
  sst << "        Individual " << i->id() << " with fitness " << i->fitness() << endl;
  sst << "      </p> " << endl;
  sst << "      <x3d width='900px' height='700px'> " << endl;
  sst << "      <scene> " << endl;

  Individual *ir = i->getRealisation();

  for(Modules::const_iterator m = ir->m_begin(); m != ir->m_end(); m++)
  {
    VLOG(10) << "  exporting module " << (*m)->name();
    sst << toX3d(*m);
  }
  sst << "      </scene> " << endl;
  sst << __x3dFooter();
  return sst.str();
}

string Exporter::toX3d(Module *m)
{
  stringstream sst;
  for(Nodes::const_iterator n = m->n_begin(); n != m->n_end(); n++) sst << toX3d(*n);
  for(Edges::const_iterator e = m->e_begin(); e != m->e_end(); e++) sst << toX3d(*e);
  // for(Edges::const_iterator e = m->e_begin(); e != m->e_end(); e++)
  // {
    // sst << "        <edge source=\"" << (*e)->source()->label()
      // << "\" destination=\"" << (*e)->destination()->label() << "\" weight=\""
      // << (*e)->weight()<< "\"/>" << endl;
  // }
  // sst << "      </module>" << endl;
  return sst.str();
}

# define NODE(p, color)\
  sst << "    <transform translation='" << p.x << " " << p.y << " " << p.z << "'>" << endl;\
  sst << "      <shape> " << endl;\
  sst << "        <appearance> " << endl;\
  sst << "        <material diffuseColor='" << color << "'></material> " << endl;\
  sst << "        </appearance> " << endl;\
  sst << "        <sphere radius='0.1'></sphere> " << endl;\
  sst << "      </shape> " << endl;\
  sst << "    </transform> " << endl;

string Exporter::toX3d(Node *n)
{
  stringstream sst;
  P3D p = n->position();

  if(n->type() == TAG_SENSOR)
  {
    NODE(p, "1 0 0");
  }
  else if(n->type() == TAG_ACTUATOR)
  {
    NODE(p, "0 1 0");
  }
  else if(n->type() == TAG_HIDDEN)
  {
    NODE(p, "0 0 1");
  }
  else if(n->type() == TAG_INPUT)
  {
    NODE(p, "0.98 0.81 0");
  }
  else if(n->type() == TAG_OUTPUT)
  {
    NODE(p, "0.98 0 0.81");
  }
  else if(n->type() == TAG_CONNECTOR)
  {
    // NODE(p, "0 0 0");
  }
  else
  {
    throw ENPException("unknown node type in Exporter::toX3d(Node *node, ...");
  }

  return sst.str();
}

string Exporter::toX3d(Edge *e)
{
  stringstream sst;

  Node *src     = e->sourceNode();
  Node *dst     = e->destinationNode();

  // TODO self-connection
  if(src == dst) return "";

  P3D psrc      = src->position();
  P3D pdst      = dst->position();
  P3D centre    = (psrc + pdst) * 0.5;

  P3D dir       = pdst - centre;

  dir.x = dir.x * sin(2.0 / 180.0 * M_PI_2);
  dir.y = dir.y * cos(2.0 / 180.0 * M_PI_2);

  P3D centre1 = centre + dir;

  dir       = centre - psrc;

  dir.x = dir.x * sin(2.0 / 180.0 * M_PI_2);
  dir.y = dir.y * cos(2.0 / 180.0 * M_PI_2);

  P3D centre2 = psrc + dir;

  string color = string("1 0 0");
  if(e->weight() > 0.0)
  {
    color = string("0 0 1");
  }

  sst << __cylinder(psrc,    centre2, "1 0 0");
  sst << __cylinder(centre1, centre2, "1 0 0");
  sst << __cylinder(centre1, pdst,    "1 0 0");

  return sst.str();
}


string Exporter::__cylinder(P3D start, P3D end, string color)
{
  stringstream sst;
  P3D dir       = end - start;
  double length = DIST(start, end);

  if(dir.length() < 0.00001) return "";

  P3D v(0.0, 1.0, 0.0);
  P3D cross  = v * dir;
  double dot = v.dot(dir);
  double angle = acos(dot / (v.length() * dir.length()));

  P3D centre = (start + end) * 0.5;

  sst << "      <transform translation='" << centre.x << " " << centre.y << " " << centre.z << "'>"
      << endl;
  sst << "        <transform rotation='" << cross.x << " " << cross.y << " " << cross.z << " "
      << angle << "'>" << endl;
  sst << "          <shape> " << endl;
  sst << "              <appearance> " << endl;
  sst << "                <material diffuseColor='" << color << "'></material> " << endl;
  sst << "              </appearance> " << endl;
  sst << "            <cylinder radius='0.0125' height='" << length << "'></cylinder> " << endl;
  sst << "          <shape> " << endl;
  sst << "        </transform>" << endl;
  sst << "      </transform>" << endl;
  return sst.str();

}
