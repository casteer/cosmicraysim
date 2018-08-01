#include "CoincidenceTrigger.hh"

#include "G4Event.hh"

#include "db/DB.hh"
#include "db/DBTable.hh"
#include "analysis/VTrigger.hh"
#include "analysis/VProcessor.hh"
#include "analysis/Analysis.hh"

namespace COSMIC {

CoincidenceTrigger::CoincidenceTrigger(DBTable tbl)
  : VTrigger(tbl.GetIndexName())
{
  std::cout << "TRG: Loading Coincidence Trigger : " << tbl.GetIndexName() << std::endl;

  // Get list of detector objects
  if (tbl.Has("processors")){
    SetupProcessors(tbl.GetVecS("processors"));
  }

  // Get thresholds
  fEnergyThreshold = -1.0;
  if (tbl.Has("energy_threshold")) {
    fEnergyThreshold = tbl.GetD("energy_threshold") * MeV;
    std::cout << "TRG: Setting Energy Threshold : " << fEnergyThreshold << std::endl;
  }

  // if (tbl.Has("require_n")){
  //   fRequireN = tbl.GetI("require_n");
  //   std::cout << "TRG: Setting Coincident Detectors : " << fRequireN << std::endl;
  // }

  fEfficiency=1.0;
  if (tbl.Has("efficiency")){
    fEfficiency = tbl.GetD("efficiency");
    std::cout << "TRG: Setting Overall Efficiency : " << fEfficiency << std::endl;
  }

  if (tbl.Has("trigger_values")){
    fTriggerMask = tbl.GetVecI("trigger_values");
    // std::cout << "TRG: Setting  : " << fEfficiency << std::endl;
  }


  for(int i=0;i<(int) fProcessors.size();i++) fTriggerEffs.push_back(1.0);

  if (tbl.Has("trigger_efficiencies")){
    fTriggerEffs = tbl.GetVecG4D("trigger_efficiencies");
    // std::cout << "TRG: Setting  : " << fEfficiency << std::endl;
  }

}

CoincidenceTrigger::CoincidenceTrigger(std::string name,
                             std::vector<std::string> processors,
                             G4double energy_thresh) : VTrigger(name)
{

  SetupProcessors(processors);

  fEnergyThreshold = energy_thresh;

}

void CoincidenceTrigger::SetupProcessors(std::vector<std::string> det) {
  for (uint i = 0; i < det.size(); i++) {
    VProcessor* detobj = Analysis::Get()->GetProcessor(det[i]);
    fProcessors.push_back(detobj);
    std::cout << " --> Processor Input " << i << " : " << det[i] << std::endl;
  }
}

bool CoincidenceTrigger::ProcessTrigger(const G4Event* /*event*/) {

  // Trigger requires all detectors to be triggered within a certain time window
  bool complete_trig = true;

  // Check for the fEfficiency at each hit
  if(fEfficiency!=1.0){
    G4double r = G4UniformRand();
    if(r>fEfficiency) return false;
  }

  int triggers = 0;

  // Loop over each trigger and check if it matches the trigger mask
  for (uint i = 0; i < fProcessors.size(); i++){

    bool trig = fProcessors[i]->HasInfo();

    if(fTriggerEffs.at(i)!=1.0){
      G4double r = G4UniformRand();
      if(r>fTriggerEffs.at(i)) trig=false;
    }

    if(fEnergyThreshold==0){

      if(trig != (bool) fTriggerMask.at(i)) complete_trig = false;

    } else {

      G4double ener = fProcessors[i]->GetEnergy();
      if((trig != (bool) fTriggerMask.at(i)) || (ener < fEnergyThreshold) ) complete_trig = false;

    }

  }

  // std::cout << "Returning True Trigger : " << complete_trig << std::endl;

  // DEBUG
  // std::cout << "Returning Trigger : " << complete_trig << std::endl;
  // std::cout << "Returning Triggers : " << triggers << std::endl;

  fTriggered = complete_trig;

  return complete_trig;
}




} // - namespace COSMIC
