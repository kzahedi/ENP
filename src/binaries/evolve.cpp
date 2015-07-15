#include "base/Configuration.h"
#include "base/data/Data.h"
#include "evo/Population.h"
#include "evo/ModuleMutationOperator.h"
#include "evo/Exporter.h"
#include "base/Random.h"

#include <glog/logging.h>

#include <iostream>
#include <fstream>

using namespace std;

string prefix(int i)
{
  stringstream sst;
  sst << i;
  string s = sst.str();

  while(s.length() < 4)
  {
    s = "0" + s;
  }
  return s;
}

int main(int argc, char** argv)
{
  google::InitGoogleLogging(argv[0]);
  Configuration *configuration = new Configuration(argc, argv, true);
  Random::initialise();
  stringstream sst;
  sst << "Random:";
  for(int i = 0; i < 10; i++)
  {
    sst << " " << Random::rand(0, 100);
  }
  VLOG(10) << sst.str();
  sst.str("");
  Data *data = Data::instance();

  LOG_IF(INFO, configuration->input().size() > 0)
    << "Input file given " << configuration->input();
  LOG_IF(INFO, configuration->output().size() > 0)
    << "Output file given " << configuration->output();
  LOG_IF(INFO, configuration->cfg().size() > 0)
    << "Configuration given " << configuration->cfg();

  VLOG(5) << "reading file " << configuration->cfg();
  data->read(configuration->cfg());

  Population *pop = new Population();
  pop->initialise();

  Individual *ind = pop->individual(0);
  Module     *mod = ind->module(0);

  DataEvolutionEdge *dee = data->specification()->evolution()->edge();
  DataEvolutionNode *den = data->specification()->evolution()->node();

  for(int i = 0; i < 200; i++)
  {
    VLOG(50) << " generation " << i;
    sst.str("");
    sst << "generation_" << prefix(i) << ".xml";
    cout << "opening " << sst.str() << endl;

    ModuleMutationOperator::mutate(mod, den, dee);

    std::ofstream ofs;
    ofs.open (sst.str(), std::ofstream::out);
    sst.str("");
    sst << data->header();
    sst << Exporter::toXml(pop);
    sst << data->footer();
    ofs << sst.str();
    ofs.close();
  }

  VLOG(5) << "done.";

  return 0;
}
