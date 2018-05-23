//----------------
// Bar definitions
 {
 name: "VARIABLE",
 index: "simconstants",
 det_tunnel_depth: "25*m",

  world_box_width: "20.0*m",
  target_tunnel_dist: "15.0*m",
  target_tunnel_size: "3*m",
  target_tunnel_length: "10.0*m",

  // 2*depth*tan(60+delta) (where delta = 5)
  // world_box_length: "2.0*det_tunnel_depth*2.144506",
  world_box_length: "20.0*m"

  det_sx: "4.0*cm",
  det_sy: "80.0*cm",
  det_sz: "15.0*cm",

  det_rot_plane1: "15"
  det_rot_plane2: "-15"

  det_focal_length: "110.0*cm",

  det_system_offset: "0.5*15*cm",// can't seem to set this as "0.5*det_sz"???
  det_system_spacing: "15*cm*1.1",// can't seem to set this as "det_sz"???

  det_system_xsep: "20*cm",
  det_system_lowbar: "0.0*cm",
  sampling_target_box_size: "1.2*m"

}
