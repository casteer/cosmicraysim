//----------------
// Bar definitions
{
  name: "VARIABLE",
  index: "simconstants",
  world_box_width: "20.0*m",
  world_box_length: "20.0*m",
  world_box_depth: "6.0*m",
  surface_soil_depth: "3*m",
  target_pos_x: "3*mm", // <-!!!! I have absolutely no idea why this needs to be multiplied by mm to be in meters
  detector_height: "0.5*m"
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
}

// --------------------------------------------------
// Detector
{
  name: "DETECTOR",
  index: "neutron",
  type: "neutron"
}

{
  name: "GEO",
  index: "soil",
  type: "box",
  mother: "world",
  material: "SiO2_Air_H20_0p4",
  // material: "G4_AIR",
  size: ["world_box_length", "world_box_width", "surface_soil_depth"],
  position: ["0.0","0.0","-0.5*surface_soil_depth"],
  color: [0.2,0.9,0.2,0.8],
  drawstyle: "solid",
  force_auxedge: 1
}

{
  index: "det_outer",
  name: "GEO",
  material: "G4_AIR",
  mother: "world",
  position: ["0.0","0.0","1.0*m"],
  type: "cons",
  r_min1: "0.0",
  r_max1: "1*m",
  r_min2: "0.0",
  r_max2: "1*m",
  size_z: "2*m",
  color: [0.9,0.8,0.2,0.5],
  drawstyle: "solid",
  sensitive: "neutron"
}

{
  index: "det_inner",
  name: "GEO",
  material: "G4_AIR",
  mother: "det_outer",
  position: ["0.0","0.0","0.0*m"],
  type: "cons",
  r_min1: "0.0",
  r_max1: "0.5*m",
  r_min2: "0.0",
  r_max2: "0.5*m",
  size_z: "2*m",
  color: [0.9,0.8,0.2,0.5],
  drawstyle: "solid",
  sensitive: "neutron"
}

//--------------------------------------------
// Main mother tunnel and detector volume (for easy placement)
//

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
  size: ["1*m","1*m","0.001*m"],
  position: ["target_pos_x","0.0","0.5*world_box_depth"]
//  position: ["0.0","0.0", "0.5*world_box_depth"],
}

// Target for the main detector stack
{
  name: "FLUX",
  index: "target_box_0",
  size: ["target_pos_x","0.5*m","0.5*m"],
  position: ["0.0","0.0","0.0"]
}


{
  name:  "TRIGGER",
  index: "soil_trg",
  type: "coincidence",
  energy_threshold: "0",
  require_n: "1",
  efficiency: "1.0",
  processors: ["det_outer_neutron","det_inner_neutron"]
}
