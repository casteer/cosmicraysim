#ifndef __AWEMuonTomographyDetector_HH__
#define __AWEMuonTomographyDetector_HH__

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "GeoObject.hh"
#include "GeoUtils.hh"
#include "analysis/VProcessor.hh"
#include "analysis/Analysis.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace COSMIC {

// double inheritance, super dodgy!
class AWEMuonTomographyDetector : public GeoObject {
public:
  inline AWEMuonTomographyDetector() {};
  inline AWEMuonTomographyDetector(DBLink* table) {Construct(table);};
  void Construct(DBLink* table);

  std::vector<GeoObject*> GetDriftObjects() { return fDriftObjects; };
  GeoObject* GetScintillatorObject() { return fScintObject; };

protected:
  std::vector<GeoObject*> fSubObjects;
  std::vector<GeoObject*> fDriftObjects;
  GeoObject* fScintObject;

};


/// True Muon Processor Object :
/// By default this is created alongside the true muon
/// tracker object, so the info is automatically added
/// to the TTree.
class AWEMuonTomographyProcessor : public VProcessor {
public:

  /// Processor can only be created with an associated
  /// tracker object.
  AWEMuonTomographyProcessor(AWEMuonTomographyDetector* trkr);
  /// Destructor
  ~AWEMuonTomographyProcessor(){};

  /// Setup Ntuple entries
  bool BeginOfRunAction(const G4Run* run);

  /// Process the information the tracker recieved for this event
  bool ProcessEvent(const G4Event* event);

protected:

  AWEMuonTomographyDetector* fAWEDetector; ///< Pointer to associated detector medium

  int fMuonTimeIndex; ///< Time Ntuple Index
  int fMuonMomXIndex; ///< MomX Ntuple Index
  int fMuonMomYIndex; ///< MomY Ntuple Index
  int fMuonMomZIndex; ///< MomZ Ntuple Index
  int fMuonPosXIndex; ///< PosX Ntuple Index
  int fMuonPosYIndex; ///< PosY Ntuple Index
  int fMuonPosZIndex; ///< PosZ Ntuple Index
  int fMuonPDGIndex;  ///< MPDG Ntuple Index

};



} // namespace COSMIC
#endif