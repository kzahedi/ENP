#include <nmode/Evaluate.h>

#include <nmode/RNN.h>
#include <nmode/Population.h>

#include <yars/cppClientCom/YarsClientCom.h>

#include <sstream>

class Braitenberg : public Evaluate
{
  public:
    Braitenberg();

    void updateController();
    void updateFitnessFunction();
    bool abort();
    void newIndividual();
    void evaluationCompleted();

};
