
// --------------------------------------------------
// Detector
{
  name: "DETECTOR",
  index: "scint",
  type: "scintillator"
}

//--------------------------------------------
// Main mother tunnel and detector volume (for easy placement)
//
{
  name: "GEO",
  index: "tunnel",
  type: "eliptunnel",
  mother: "world",
  material: "G4_AIR",
  size: ["11.630*m", "7.740*m", "world_box_width"],
  position: ["0.0","0.0","-0.5*det_tunnel_depth"],
  rotation: [90.0,0.0,90.0],
  color: [0.6,0.0.6,0.6,0.4],
  drawstyle: "solid"
}

{
  name: "GEO",
  index: "detector",
  type: "box",
  mother: "tunnel",
  material: "G4_AIR",
  size: ["sampling_target_box_size", "sampling_target_box_size", "sampling_target_box_size"],
  position: ["det_shift","0.5*sampling_target_box_size+1.0*m","0.0"],
  rotation_mother: [0.0,-90.0,90.0],
}

/*
{
  name: "GEO",
  index: "target_box_geo",
  type: "box",
  mother: "world",
  size: ["sampling_target_box_size","sampling_target_box_size","sampling_target_box_size"],
  position: ["0.0","-det_shift","-0.5*det_tunnel_depth+0.5*sampling_target_box_size"],
  color: [0.0,1.0,1.0,0.5],
  drawstyle: "solid"
}
*/

{
  name: "GEO",
  index: "bar0",
  type: "box",
  mother: "detector",
  material: "G4_PLASTIC_SC_VINYLTOLUENE",
  size: ["det_sx","det_sz","det_sy"],
  position: ["0.5*det_focal_length","-2.5*det_system_spacing","0.0"],
  rotation: [0.0,0.0,0.0],
  rotation_mother: [0.0,90.0,0.0],
  color: [0.0,0.0,1.0,0.5],
  drawstyle: "solid"
  sensitive: "scint"
}

{  name: "GEO", index: "bar1", clone: "bar0",
   position: ["0.5*det_focal_length","-1.5*det_system_spacing","0.0"]
}
{  name: "GEO", index: "bar2", clone: "bar0",
   position: ["0.5*det_focal_length","-0.5*det_system_spacing","0.0"]
}


{  name: "GEO", index: "bar3", clone: "bar0",
    position: ["0.5*det_focal_length","0.5*det_system_spacing","0.0"]
}
{  name: "GEO", index: "bar4", clone: "bar0",
    position: ["0.5*det_focal_length","1.5*det_system_spacing","0.0"]
}
{  name: "GEO", index: "bar5", clone: "bar0",
    position: ["0.5*det_focal_length","2.5*det_system_spacing","0.0"]
}



{  name: "GEO", index: "target_det0", clone: "bar0",
   size: ["30.0*cm","30.0*cm","4.0*cm"],
   position: ["0.0","-30.0*cm","-0.5*det_focal_length"]
   color: [1.0,0.0,0.0,0.5],
   rotation: [0.0,0.0,0.0],
   rotation_mother: [0.0,0.0,0.0]
}


{  name: "GEO", index: "target_det1", clone: "target_det0", position: ["0.0","0.0*cm","-0.5*det_focal_length"] }
{  name: "GEO", index: "target_det2", clone: "target_det0", position: ["0.0","30.0*cm","-0.5*det_focal_length"] }
//{  name: "GEO", index: "target_det3", clone: "target_det0", position: ["0.0","0.0*cm","-0.5*det_focal_length+4.0*cm"] }


/**
 * CONINCIDENCE TRIGGERS
 *
 */

{
  name:  "TRIGGER",
  index: "trigger06",
  type: "coincidence",
  energy_threshold: "0",
  require_n: "2",
  processors: ["bar0_scint","target_det0_scint"],
  efficiency: "det0_eff*det6_eff"
}

{  name:  "TRIGGER",  index: "trigger07",  clone: "trigger06",  processors: ["bar0_scint","target_det1_scint"],
efficiency: "det0_eff*det7_eff"}
{  name:  "TRIGGER",  index: "trigger08",  clone: "trigger06",  processors: ["bar0_scint","target_det2_scint"],
efficiency: "det0_eff*det8_eff"}

{  name:  "TRIGGER",  index: "trigger16",  clone: "trigger06",  processors: ["bar1_scint","target_det0_scint"],
efficiency: "det1_eff*det6_eff"}
{  name:  "TRIGGER",  index: "trigger17",  clone: "trigger06",  processors: ["bar1_scint","target_det1_scint"],
efficiency: "det1_eff*det7_eff"}
{  name:  "TRIGGER",  index: "trigger18",  clone: "trigger06",  processors: ["bar1_scint","target_det2_scint"],
efficiency: "det1_eff*det8_eff"}

{  name:  "TRIGGER",  index: "trigger26",  clone: "trigger06",  processors: ["bar2_scint","target_det0_scint"],
efficiency: "det2_eff*det6_eff"}
{  name:  "TRIGGER",  index: "trigger27",  clone: "trigger06",  processors: ["bar2_scint","target_det1_scint"],
efficiency: "det2_eff*det7_eff"}
{  name:  "TRIGGER",  index: "trigger28",  clone: "trigger06",  processors: ["bar2_scint","target_det2_scint"],
efficiency: "det2_eff*det8_eff"}

{  name:  "TRIGGER",  index: "trigger36",  clone: "trigger06",  processors: ["bar3_scint","target_det0_scint"],
efficiency: "det3_eff*det6_eff"}
{  name:  "TRIGGER",  index: "trigger37",  clone: "trigger06",  processors: ["bar3_scint","target_det1_scint"],
efficiency: "det3_eff*det7_eff"}
{  name:  "TRIGGER",  index: "trigger38",  clone: "trigger06",  processors: ["bar3_scint","target_det2_scint"],
efficiency: "det3_eff*det8_eff"}

{  name:  "TRIGGER",  index: "trigger46",  clone: "trigger06",  processors: ["bar4_scint","target_det0_scint"],
efficiency: "det4_eff*det6_eff"}
{  name:  "TRIGGER",  index: "trigger47",  clone: "trigger06",  processors: ["bar4_scint","target_det1_scint"],
efficiency: "det4_eff*det7_eff"}
{  name:  "TRIGGER",  index: "trigger48",  clone: "trigger06",  processors: ["bar4_scint","target_det2_scint"],
efficiency: "det4_eff*det8_eff"}

{  name:  "TRIGGER",  index: "trigger56",  clone: "trigger06",  processors: ["bar5_scint","target_det0_scint"],
efficiency: "det5_eff*det6_eff"}
{  name:  "TRIGGER",  index: "trigger57",  clone: "trigger06",  processors: ["bar5_scint","target_det1_scint"],
efficiency: "det5_eff*det7_eff"}
{  name:  "TRIGGER",  index: "trigger58",  clone: "trigger06",  processors: ["bar5_scint","target_det2_scint"],
efficiency: "det5_eff*det8_eff"}
