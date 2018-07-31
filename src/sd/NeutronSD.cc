#include "NeutronSD.hh"
#include "analysis/Analysis.hh"
#include "db/DBTable.hh"

#include "G4EventManager.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4Square.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4Box.hh"
#include "db/ROOTHeaders.hh"
#include "G4Polyline.hh"

namespace COSMIC {

//------------------------------------------------------------------
NeutronSD::NeutronSD(DBTable tbl):
  VDetector(tbl.GetIndexName(), "neutron")
{
  std::cout << "DET: Creating new " << GetType()
            << " detector : " << GetID() << std::endl;

  // Set initial state
  ResetState();

  // By default also include the auto processor
  // std::cout << "TRUE Neutron PROCESSOR : " << tbl->GetI("processor") << std::endl;
  if (!tbl.Has("processor") or tbl.GetI("processor") > 0) {
    Analysis::Get()->RegisterProcessor(new NeutronProcessor(this));
  }
}

NeutronSD::NeutronSD(std::string name, std::string id, bool autoprocess, bool autosave):
  VDetector(name, id)
{
  std::cout << "DET: Creating new " << GetType()
            << " detector : " << GetID() << std::endl;

  // Set initial state
  ResetState();

  // By default also include the auto processor
  if (autoprocess) {
    Analysis::Get()->RegisterProcessor(new NeutronProcessor(this, autosave));
  }
}

void NeutronSD::ResetState() {

  VDetector::ResetState();

  fHits = 0;
  fNeutronEventID.clear();
  fNeutronTrackID.clear();
  fNeutronParentID.clear();
  fNeutronPDG.clear();
  fNeutronPos.clear();
  fNeutronMom.clear();
  fNeutronKE.clear();
  fNeutronEnergyDeposited.clear();
  fNeutronTime.clear();

}

G4bool NeutronSD::ProcessHits(G4Step* step, G4TouchableHistory* /*touch*/) {

  // Don't save tracks if no energy left in the detector
  G4double edep = step->GetTotalEnergyDeposit();
  if (edep <= 0.) return false;

  // Get only Neutrons
  G4Track* track = step->GetTrack();
  int steppdg = track->GetParticleDefinition()->GetPDGEncoding();
  // G4ThreeVector steppos = steppoint->GetPosition();
  // G4ThreeVector stepmom =  track->GetMomentum();



  // FOR DEBUG :
  // bool is_Neutron = (steppdg == 2112);
  // bool is_Alpha = (steppdg == 1000020040);

  // if ( !(is_Neutron||is_Alpha) ) return false;
  // if ( !is_Neutron ) return false;

  // We only want secondary particles in the detector
  // if(step->GetTrack()->GetParentID() == 0) return false;

  // if(is_Neutron) if(edep>0) std::cout << " Neutron : " << edep << std::endl;
  // if(is_Alpha) if(edep>0) std::cout << " Alpha : " << edep << std::endl;

  G4StepPoint* steppoint = step->GetPostStepPoint();
  G4double steptime = steppoint->GetGlobalTime();

  fNeutronPDG.push_back(steppdg);
  fNeutronEventID.push_back(G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID());
  fNeutronTrackID.push_back(track->GetTrackID());
  fNeutronParentID.push_back(track->GetParentID());
  fNeutronPos.push_back(steppoint->GetPosition());
  fNeutronMom.push_back(steppoint->GetMomentum());
  fNeutronKE.push_back(steppoint->GetKineticEnergy());
  fNeutronEnergyDeposited.push_back(edep);
  fNeutronTime.push_back(steppoint->GetGlobalTime());
  fHits++;
  // Add to the triggers?

  // // Get the unique id of this particle
  // std::pair<G4int, G4int> this_particle_ids = std::make_pair( track->GetTrackID(), track->GetParentID() );
  //
  // // Check whether this particle already contributed to the energy deposited
  // std::map< std::pair<G4int, G4int> , double >::iterator it = fNeutronEnergyMapped.find(this_particle_ids);
  //
  // bool already_exists = ( it != fNeutronEnergyMapped.end() );
  //
  // if(already_exists){
  //   // if it already exists then add the current energy deposited to this
  //   // - get the new value and reassign it to the current particle id
  //   fNeutronEnergyMapped[this_particle_ids] += edep;
  //
  //   // Average the time of the hits by track and parent id
  //   fNeutronKEMapped[this_particle_ids] *= fHits;
  //   fNeutronTimeMapped[this_particle_ids] *= fHits;
  //   fNeutronMomMapped[this_particle_ids] *= fHits;
  //   fNeutronPosMapped[this_particle_ids] *= fHits;
  //
  //   fNeutronKEMapped[this_particle_ids] += steppoint->GetKineticEnergy();
  //   fNeutronMomMapped[this_particle_ids] += track->GetMomentum();
  //   fNeutronPosMapped[this_particle_ids] += steppoint->GetPosition();
  //   fNeutronTimeMapped[this_particle_ids] += steppoint->GetGlobalTime();
  //
  //   fHits++;
  //   fNeutronTimeMapped[this_particle_ids] /= fHits;
  //   fNeutronKEMapped[this_particle_ids] /= fHits;
  //   fNeutronMomMapped[this_particle_ids] /= fHits;
  //   fNeutronPosMapped[this_particle_ids] /= fHits;
  //
  // } else {
  //   fHits++;
  //
  //   // if not add the ids to the map and initialize the value with the deposited energy
  //   fNeutronEnergyMapped[this_particle_ids] = edep;
  //   fNeutronKEMapped[this_particle_ids] = steppoint->GetKineticEnergy();
  //   fNeutronMomMapped[this_particle_ids] = steppoint->GetMomentumDirection();
  //   fNeutronPosMapped[this_particle_ids] = steppoint->GetPosition();
  //   fNeutronTimeMapped[this_particle_ids] = steppoint->GetGlobalTime();
  //
  // }
  //
  // // For DEBUG...
  // // std::cout << std::endl << "StepPDG : " << steppdg << " Edep : " << edep << std::endl;
  // // std::cout << "is_Neutron : " << is_Neutron << " is_Alpha : " << is_Alpha << std::endl;
  // // std::cout << "StepPos : " << steppos  << std::endl << std::endl;

  return true;
}


//------------------------------------------------------------------
NeutronProcessor::NeutronProcessor(NeutronSD* trkr, bool autosave) :
  VProcessor(trkr->GetID()), fSave(autosave)
{
  fTracker = trkr;
}

bool NeutronProcessor::BeginOfRunAction(const G4Run* /*run*/) {

  std::string tableindex = GetID();
  std::cout << "DET: Registering NeutronProcessor NTuples " << tableindex << std::endl;

  G4AnalysisManager* man = G4AnalysisManager::Instance();

  // Fill index energy
  fNeutronTimeIndex = man ->CreateNtupleDColumn(tableindex + "_t");
  fNeutronEdepIndex = man ->CreateNtupleDColumn(tableindex + "_edep");
  // fNeutronMultIndex = man ->CreateNtupleDColumn(tableindex + "_mult");
  fNeutronPosRIndex = man ->CreateNtupleDColumn(tableindex + "_r");
  fNeutronPosThetaIndex = man ->CreateNtupleDColumn(tableindex + "_theta");

  fNeutronPosXIndex = man ->CreateNtupleDColumn(tableindex + "_x");
  fNeutronPosYIndex = man ->CreateNtupleDColumn(tableindex + "_y");
  fNeutronPosZIndex = man ->CreateNtupleDColumn(tableindex + "_z");

  fNeutronMomXIndex = man ->CreateNtupleDColumn(tableindex + "_px");
  fNeutronMomYIndex = man ->CreateNtupleDColumn(tableindex + "_py");
  fNeutronMomZIndex = man ->CreateNtupleDColumn(tableindex + "_pz");

  fNeutronKEIndex = man ->CreateNtupleDColumn(tableindex + "_ke");

  fNeutronPDGIndex = man ->CreateNtupleIColumn(tableindex + "_pdg");
  fNeutronEventIDIndex = man ->CreateNtupleIColumn(tableindex + "_eventid");
  fNeutronParentIDIndex = man ->CreateNtupleIColumn(tableindex + "_parentid");
  fNeutronTrackIDIndex = man ->CreateNtupleIColumn(tableindex + "_trackid");

  return true;
}

bool NeutronProcessor::ProcessEvent(const G4Event* /*event*/) {

  // Loop over all of the neutron events saved
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  std::vector<int> parent_ids = fTracker->GetParentID();

  double total_edep = 0;
  std::vector<G4double> edeps = fTracker->GetEnergyDeposited();
  for(double e : edeps) total_edep+=e;

  // std::cout << " - Neutron Events: " << (int) parent_ids.size() << std::endl;
  // std::cout << " - Neutron EDep: " << total_edep << std::endl;

  if((parent_ids.size()>0)&&(total_edep>0))
  {
    fHasInfo = true;

    // Loop over all of the neutron events saved
    std::vector<int> track_ids = fTracker->GetTrackID();
    std::vector<int> event_ids = fTracker->GetEventID();
    std::vector<int> event_pdgs = fTracker->GetPDGs();

    std::vector<G4double> kes  = fTracker->GetKineticEnergy();
    std::vector<G4double> times  = fTracker->GetTimes();
    std::vector<G4ThreeVector> pos  = fTracker->GetPosition();
    std::vector<G4ThreeVector> mom  = fTracker->GetMomentum();

    for(int id=0;id<(int) parent_ids.size(); id++)
    {

      man->FillNtupleDColumn(fNeutronTimeIndex, times.at(id));
      man->FillNtupleDColumn(fNeutronEdepIndex, edeps.at(id) / MeV);
      man->FillNtupleDColumn(fNeutronPosRIndex, (pos.at(id)).perp() );
      man->FillNtupleDColumn(fNeutronPosThetaIndex, (pos.at(id)).phi());
      man->FillNtupleDColumn(fNeutronPosXIndex, (pos.at(id)).x() );
      man->FillNtupleDColumn(fNeutronPosYIndex, (pos.at(id)).y() );
      man->FillNtupleDColumn(fNeutronPosZIndex, (pos.at(id)).z() );
      man->FillNtupleDColumn(fNeutronMomXIndex, (mom.at(id)).x() );
      man->FillNtupleDColumn(fNeutronMomYIndex, (mom.at(id)).y() );
      man->FillNtupleDColumn(fNeutronMomZIndex, (mom.at(id)).z() );
      man->FillNtupleDColumn(fNeutronKEIndex, kes.at(id)/MeV );
      man->FillNtupleIColumn(fNeutronPDGIndex, event_pdgs.at(id));
      man->FillNtupleIColumn(fNeutronEventIDIndex, event_ids.at(id));
      man->FillNtupleIColumn(fNeutronParentIDIndex, parent_ids.at(id));
      man->FillNtupleIColumn(fNeutronTrackIDIndex, track_ids.at(id));
      man->AddNtupleRow();
    }

  } else {

    man->FillNtupleDColumn(fNeutronTimeIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronEdepIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronPosRIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronPosThetaIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronPosXIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronPosYIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronPosZIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronMomXIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronMomYIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronMomZIndex, kInfinity);
    man->FillNtupleDColumn(fNeutronKEIndex, kInfinity);
    man->FillNtupleIColumn(fNeutronPDGIndex, kInfinity);
    man->FillNtupleIColumn(fNeutronEventIDIndex, kInfinity);
    man->FillNtupleIColumn(fNeutronParentIDIndex, kInfinity);
    man->FillNtupleIColumn(fNeutronTrackIDIndex, kInfinity);
    man->AddNtupleRow();

  }

  return fHasInfo;

}

void NeutronProcessor::DrawEvent(){
  // Draw Track if in interactive
  // G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  // if (pVVisManager)
  // {
  //
  //     G4ThreeVector Neutronpos = fTracker->GetAveragePosition();
  //
  //       G4Circle NeutronMarker(Neutronpos);
  //
  //       G4Colour colour(1., 0., 0.);
  //       G4VisAttributes attribs(colour);
  //       NeutronMarker.SetVisAttributes(attribs);
  //
  //       pVVisManager->Draw(NeutronMarker);
  //
  // }
}

} // - namespace COSMIC
