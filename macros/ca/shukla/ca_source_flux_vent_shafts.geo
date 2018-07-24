// ---------------------------------------------------
// Flux Generator Source Location : Default is Shukla
// Shukla default values
{
  name: "SHUKLA",
  index: "config",
  min_energy: 0.1,
  max_energy: 5000.0,
  I0: 88.5,
  n: 3.0,
  E0: 4.28,
  epsilon: 854.,
  radius: 6371.,
  distance: 36.61
}


{
  name: "GLOBAL",
  index: "config",
  flux: "shukla",
  physics: "shielding",
  batchcommands: "",
}

{
  name: "FLUX",
  index: "source_box",
  size: ["world_box_length", "world_box_width", "1.*mm"],
  position: ["0.0","0.0", "0.5*det_tunnel_depth - 2*mm"]
}

// Target for the main detector plane
{
  name: "FLUX",
  index: "target_box_0",
  size: ["source_target_box_size","source_target_box_size","source_target_box_size"],
  position: ["0.0","-det_shift","0.5*sampling_target_box_size+0.5*det_focal_length-0.5*det_tunnel_depth"]
}
