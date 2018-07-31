#include "Analysis.hh"

#include "g4root.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

#include "db/DB.hh"
#include "VProcessor.hh"
#include "VTrigger.hh"
#include "VFluxProcessor.hh"
#include "VDetector.hh"

namespace COSMIC {

Analysis::Analysis() :
  fFluxProcessor(0),
  fSavedEventsLimit(-1),
  fGeneratedEventsLimit(-1),
  fSavedEvents(0),
  fGeneratedEvents(0),
  fExposureTimeLimit(-1.0),
  fNTuplesSetup(0),
  fChunkSize(10000)
{
}

Analysis::~Analysis() {
}

Analysis *Analysis::fPrimary(0);


void Analysis::BeginOfRunAction(const G4Run* run) {


  if (!fNTuplesSetup) {
    std::cout << "ANL: Setting up G4Manager" << std::endl;
    // Initialise G4 ROOT Manager
    fG4Manager = G4AnalysisManager::Instance();
    fG4Manager->SetVerboseLevel(1);
    fG4Manager->SetFirstNtupleId(0);
    fG4Manager->SetFirstHistoId(0);
    fG4Manager->CreateNtuple("detectorevents", "Dynamic Detector Saved Information");


    // Run event processors begin run action
    std::vector<VProcessor*>::iterator iter;
    for (iter = fProcessors.begin(); iter != fProcessors.end(); iter++) {
      (*iter)->BeginOfRunAction(run);
    }

    // Run Flux Processor begin run action
    if (fFluxProcessor) fFluxProcessor->BeginOfRunAction(run);

    // Finish Ntuple and open output
    fG4Manager->FinishNtuple();
  }

  // Make new output file
  std::string outputname = "";
  outputname += fOutputTag + ".";
  outputname += std::to_string(fRunID) + ".";
  outputname += std::to_string(fSubRunID) + ".root";

  //
  std::vector<VTrigger*>::iterator titer;
  for (titer = fTriggers.begin(); titer != fTriggers.end(); titer++) fSavedCounts.push_back(0);

  // Open new output
  fG4Manager->OpenFile(outputname);
  fNTuplesSetup = true;
}

void Analysis::EndOfRunAction(const G4Run* /*run*/) {
  std::cout << "Writing" << std::endl;
  fG4Manager->Write();
  fG4Manager->CloseFile();
  // delete  G4AnalysisManager::Instance();
}

void Analysis::BeginOfEventAction() {
  ResetState();
}

void Analysis::ProcessEvent(const G4Event* event) {

  // Run Flux Processor
  if (fFluxProcessor) fFluxProcessor->ProcessEvent(event);

  // Run Event processors
  std::vector<VProcessor*>::iterator piter;
  for (piter = fProcessors.begin(); piter != fProcessors.end(); piter++) {
    (*piter)->ProcessEvent(event);
  }

  // Run Trigger Processors
  std::vector<VTrigger*>::iterator titer;
  int i=0;
  for (titer = fTriggers.begin(); titer != fTriggers.end(); titer++) {

      (*titer)->ProcessTrigger(event);

      if ((*titer)->GetTrigger()) fSavedCounts[i]++;
      i++;
  }

  // Add one to total generated
  fGeneratedEvents++;

  // If we have at least one trigger record the event
  if (IsTriggered()) RecordEvent();

}

void Analysis::RecordEvent() {
  fG4Manager->AddNtupleRow();
  fSavedEvents++;
}

void Analysis::ResetState() {
  ResetTriggers();
  ResetProcessors();
  ResetDetectors();
}

void Analysis::RegisterTrigger(VTrigger* t) {
  fTriggers.push_back(t);
}

bool Analysis::IsTriggered() {

  // If no valid triggers loaded, save everything
  if (fTriggers.size() < 1) return true;

  // For now just find at least one true trigger
  std::vector<VTrigger*>::iterator iter;
  for (iter = fTriggers.begin(); iter != fTriggers.end(); iter++) {
    if ((*iter)->GetTrigger()) {
      return true;
    }
  }

  return false;
}

void Analysis::ResetTriggers() {
  std::vector<VTrigger*>::iterator iter;
  for (iter = fTriggers.begin(); iter != fTriggers.end(); iter++) {
    (*iter)->Reset();
  }
}

VTrigger* Analysis::GetTrigger(std::string id) {
  std::vector<VTrigger*>::iterator iter;
  for (iter = fTriggers.begin(); iter != fTriggers.end(); iter++) {
    std::string trigid = (*iter)->GetID();
    if (id.compare(trigid) == 0) return (*iter);
  }
  std::cout << "Cannot find Trigger : " << id << std::endl;
  throw;
  return 0;
}

std::vector<int> Analysis::GetCounts(){ return fSavedCounts;};

void Analysis::RegisterProcessor(VProcessor* p) {
  fProcessors.push_back(p);
}

void Analysis::ResetProcessors() {
  std::vector<VProcessor*>::iterator iter;
  for (iter = fProcessors.begin(); iter != fProcessors.end(); iter++) {
    (*iter)->Reset();
  }
}

VProcessor* Analysis::GetProcessor(std::string id) {
  std::vector<VProcessor*>::iterator iter;
  for (iter = fProcessors.begin(); iter != fProcessors.end(); iter++) {
    std::string procid = (*iter)->GetID();
    if (id.compare(procid) == 0) return (*iter);
  }
  std::cout << "Cannot find Processor : " << id << std::endl;
  throw;
  return 0;
}

void Analysis::RegisterDetector(VDetector* p) {
  fDetectors.push_back(p);
  G4SDManager::GetSDMpointer()->AddNewDetector(static_cast<G4VSensitiveDetector*>(p));
}

void Analysis::ResetDetectors() {
  std::vector<VDetector*>::iterator iter;
  for (iter = fDetectors.begin(); iter != fDetectors.end(); iter++) {
    (*iter)->ResetState();
  }
}

VDetector* Analysis::GetDetector(std::string id) {
  std::vector<VDetector*>::iterator iter;
  for (iter = fDetectors.begin(); iter != fDetectors.end(); iter++) {
    std::string detid = (*iter)->GetID();
    if (id.compare(detid) == 0) return (*iter);
  }
  std::cout << "Cannot find Detector : " << id << std::endl;
  throw;
  return 0;
}

void Analysis::SetFluxProcessor(VFluxProcessor* p) {
  fFluxProcessor = p;
}

} // - namespace COSMIC
