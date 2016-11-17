y_base = 70;
x_base = 15;
z_base = 3;

h_tornillo = z_base+4;
r_tornillo = 3;

marge_borde_con_tornillo = 3;

difference(){
    cube([x_base, y_base, z_base], center = true);
    translate([0, (y_base/2) - r_tornillo - marge_borde_con_tornillo, -1]){
        cylinder(r=r_tornillo, h=h_tornillo, $fn=200, center = true);
    }
    translate([0, -(y_base/2) + r_tornillo + marge_borde_con_tornillo, -1]){
        cylinder(r=r_tornillo, h=h_tornillo, $fn=200, center = true);
    }
}