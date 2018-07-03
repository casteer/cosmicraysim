//----------------
// Bar definitions
{
  name: "VARIABLE",
  index: "simconstants",
  world_box_width: "1000.0*m",
  world_box_length: "1000.0*m",
  world_box_depth: "10.0*m",
  surface_soil_depth: "5*m",
  detector_height: "0.5*m",
  sampling_target_box_size: "2*m"
}

// z Heights
//
//  -100m
//  +50m    bedrock
//  +53m    surface soil
//


// ---------------------------------------------------
// World Geometry
// Then air and carbon base
{
  name: "GEO",
  index: "world",
  material: "G4_AIR",
  size: ["world_box_length", "world_box_width", "world_box_depth"],
  type: "box",
  color: [0.9,0.9,0.99,0.9],
  drawstyle: "solid"
  force_auxedge: 1
  sensitive: "neutron_det"
}

// --------------------------------------------------
// Detector
{
  name: "DETECTOR",
  index: "neutron_det",
  type: "neutron"
}

{
  name: "GEO",
  index: "surface_soil",
  type: "box",
  mother: "world",
  material: "SiO2_Air_H20_0p4",
  size: ["world_box_length", "world_box_width", "surface_soil_depth"],
  position: ["0.0","0.0","-0.5*surface_soil_depth"],
  color: [0.2,0.9,0.2,0.8],
  drawstyle: "solid",
  force_auxedge: 1,
  sensitive: "neutron_det"
}


//--------------------------------------------
// Main mother tunnel and detector volume (for easy placement)
//
/*
{
  name: "GEO",
  index: "detector_moderator",
  type: "box",
  mother: "world",
  material: "G4_PLASTIC_SC_VINYLTOLUENE",
  size: ["25*cm","25*cm","120*cm"],
  position: ["0.0","0.0","-0.5*world_box_depth + bedrock_depth + 0.5*surface_soil_depth + subsurface_soil_depth + 50*cm"],
  color: [0.8,0.8,0.8,0.8],
  drawstyle: "solid",
  force_auxedge: 1
}
*/

/*
{
  name: "GEO",
  index: "detector",
  type: "box",
  mother: "detector_moderator",
  material: "G4_PLASTIC_SC_VINYLTOLUENE",
  size: ["5*cm","5*cm","100*cm"],
  position: ["0.0","0.0","0.0"],
  color: [1.0,1.0,1.0,1.0],
  drawstyle: "solid",
  force_auxedge: 1,
  sensitive: "neutron_det"
}
*/

// ---------------------------------------------------
// Flux Generator Source Location : Default is Shukla
// Shukla default values
// CRY default values

// CRY default values
{
  name: "CRY",
  index: "config",
  min_particles: 1.,
  max_particles: -1.,
  gen_neutrons: 1.,
  gen_protons: 0.,
  gen_gammas: 0.,
  gen_electrons: 0.,
  gen_muons: 0.,
  gen_pions: 0.,
  latitude: 0.0,
  altitude: 0.0,
  date: "1-1-2007",
}

{
  name: "GLOBAL",
  index: "config",
  flux: "cry",
  physics: "QGSP_BERT_HP",
  batchcommands: "",
}

/*
 {
  name: "GLOBAL",
  index: "config",
  flux: "root",
  physics: "shielding",
  batchcommands: "",
}

{
  name: "ROOT",
  index: "config",
  I0: "8.0",
  spectrum_file: "IncomingSpectrum.root"
  histogram: "cosmicSpectrum"
}
*/

{
  name: "FLUX",
  index: "source_box",
  size: ["world_box_length", "world_box_width", "1.*mm"],
  position: ["0.0","0.0", "0.5*world_box_depth - 2*mm"],
}

// Target for the main detector stack
{
  name: "FLUX",
  index: "target_box_0",
  size: ["world_box_length","world_box_width","1*mm"],
  position: ["0.0","0.0","0.0"]
}
