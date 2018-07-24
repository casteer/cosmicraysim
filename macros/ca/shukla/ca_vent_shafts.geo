// Vent shaft
/*{
  name: "GEO",
  index: "vent_shaft0",
  material: "G4_WATER",
  mother: "world",
  size: ["target_tunnel_size", "target_tunnel_size", "det_tunnel_depth+sampling_target_box_size-8*m"],
  position: ["0.0","0.0","sampling_target_box_size+1.0*m"],
  type: "box",
}
*/

/**
 * The Vent shaft itself
 */
 {
   index: "vent_shaft0",
   name: "GEO",
   material: "G4_AIR",
   mother: "world",
   position: ["0.0","0.0","sampling_target_box_size+3.0*m"],
   type: "cons",
   r_min1: "0.0",
   r_max1: "target_tunnel_size*0.5",
   r_min2: "0.0",
   r_max2: "target_tunnel_size*0.5",
   size_z: "det_tunnel_depth+sampling_target_box_size-5*m",
   color: [0.2,0.8,0.2,0.5],
   drawstyle: "solid",
 }


 {
   index: "vent_shaft_fill",
   name: "GEO",
   material: "Standard_Rock",
   mother: "vent_shaft0",
   position: ["0.0","0.0","-0.5*(det_tunnel_depth+sampling_target_box_size-5*m)+fill_height*0.5"],
   type: "cons",
   r_min1: "0.0",
   r_max1: "target_tunnel_size*0.5",
   r_min2: "0.0",
   r_max2: "target_tunnel_size*0.5",
   size_z: "fill_height",
   color: [0.8,0.8,0.2,0.5],
   drawstyle: "solid",
 }
