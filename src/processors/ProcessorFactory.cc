#include "ProcessorFactory.hh"
#include "G4LogicalVolume.hh"
#include "db/DBLink.hh"
#include "TrueMuonPoCAProcessor.hh"
#include "analysis/Analysis.hh"
#include "db/DB.hh"

namespace COSMIC {

VProcessor* ProcessorFactory::Construct(DBLink* tbl) {

  // Retrieve the table that matches this sensitive
  std::string type = tbl->GetS("type");

  // Now Search for different types
  if (type.compare("truemuonpoca") == 0) return new TrueMuonPoCAProcessor(tbl);

  // Check we didn't get to here
  std::cout << "Failed to Create Processor : " << type << " NOW" << std::endl;
  throw;  
  return 0;
}


void ProcessorFactory::ConstructProcessors() {

  /// Get the DB Table Set
  std::cout << "===============================" << std::endl;
  std::cout << "PRC: Building PROCESSORS " << std::endl;
  std::vector<DBLink*> tables_clone = DB::Get()->GetLinkGroup("PROCESSOR");
  std::vector<DBLink*>::iterator trg_iter = tables_clone.begin();

  int count = 0;
  for (trg_iter = tables_clone.begin(); trg_iter != tables_clone.end(); trg_iter++) {

    DBLink* trg_tab = (*trg_iter);
    std::string trg_id = trg_tab->GetIndexName();

    // Create and register to analysis manager
    VProcessor* trg_obj = ProcessorFactory::Construct(trg_tab);
    Analysis::Get()->RegisterProcessor(trg_obj);
  }

  return;
}


} // - namespace COSMIC
