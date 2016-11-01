//Pieza base
alto_cubo = 2;
an_cubo = 65;
pro_cubo = 65;

alto_cilindro = 65;

ancho_tornillo_base = 3;
alto_tornillo_base = 3;

ancho_tornillo_servo = 5;
alto_tornillo_servo = 5+1;
margen_tornillo_servo =1;

ancho_servo = 11.8;
alto_servo =16+1;
pro_servo = 22.2;

//Pieza Horizontal
y_base = 150;
x_base = 25;
z_base = 3;

h_tornillo = z_base+4;
r_tornillo = 3;

marge_borde_con_tornillo = 3;

//Pieza Herramienta

x_caja = 40;
y_caja = 60;
z_caja = 30;

x_servo = 11.8;
y_servo = 22.2;
z_servo = 16;

y_servo_tornillos = 32.2;

d_tornillo_servo = 4;
h_tornillo_servo = 10;
margen_tornillo_servo = 1;

h_herramienta = 60;
d_herramienta = 5;
margen_herramienta = 1;

d_tornillo_sujecion = 5;
h_tornillo_sujecion = 3;

union(){
    difference(){
        rotate([90,0,0])
            cube ([an_cubo,alto_cubo,pro_cubo], center = true);
        translate([an_cubo/2-ancho_tornillo_base,an_cubo/2-ancho_tornillo_base,0])
            cylinder (h = alto_tornillo_base, d = ancho_tornillo_base, center = true,$fn=300);
        translate([-(an_cubo/2-ancho_tornillo_base),an_cubo/2-ancho_tornillo_base,0])
            cylinder (h = alto_tornillo_base, d = ancho_tornillo_base, center = true,$fn=300);
        translate([-(an_cubo/2-ancho_tornillo_base),-(an_cubo/2-ancho_tornillo_base),0])
            cylinder (h = alto_tornillo_base, d = ancho_tornillo_base, center = true,$fn=300);
        translate([(an_cubo/2-ancho_tornillo_base),-(an_cubo/2-ancho_tornillo_base),0])
            cylinder (h = alto_tornillo_base, d = ancho_tornillo_base, center = true,$fn=300);
    }
    difference(){
        translate([0,0,alto_cilindro/2+ alto_cubo/2] )
            cylinder (h = alto_cilindro, d = an_cubo - 10, center = true,$fn=300);
        translate([0,0,alto_cubo/2+alto_cilindro-alto_servo/2+1])
            cube ([ancho_servo,pro_servo,alto_servo], center = true);
        translate([0,pro_servo/2+ancho_tornillo_servo/2+margen_tornillo_servo,alto_cubo/2+alto_cilindro-alto_tornillo_servo/2+1])
            cylinder (h = alto_tornillo_servo, d = ancho_tornillo_servo, center = true,$fn=300);
        translate([0,-(pro_servo/2+ancho_tornillo_servo/2+margen_tornillo_servo),alto_cubo/2+alto_cilindro-      alto_tornillo_servo/2+1])
            cylinder (h = alto_tornillo_servo, d = ancho_tornillo_servo, center = true,$fn=300);
    }
    
}

translate([0,y_base/2-marge_borde_con_tornillo-h_tornillo/2,alto_cubo/2+alto_cilindro+z_base]){
    union(){
        difference(){
            cube([x_base, y_base, z_base], center = true);
            translate([0, (y_base/2) - r_tornillo - marge_borde_con_tornillo, -1]){
                cylinder(r=r_tornillo, h=h_tornillo, $fn=200, center = true);
            }
            translate([0, -(y_base/2) + r_tornillo + marge_borde_con_tornillo, -1]){
                cylinder(r=r_tornillo, h=h_tornillo, $fn=200, center = true);
            }
        }
    }
}

translate([0,y_base-marge_borde_con_tornillo-h_tornillo/2+y_caja/2-y_servo_tornillos/2-marge_borde_con_tornillo,alto_cubo/2+alto_cilindro+z_caja/2+z_base*2]){
    rotate([0,0,180]){
    difference(){
        cube([x_caja, y_caja, z_caja], center=true);
        translate([0, (y_caja/2)-(y_servo_tornillos/2), -(z_caja/2)+(z_servo/2)-0.01]){
            union(){
                cube([x_servo, y_servo, z_servo], center=true);
                translate([0, +(y_servo/2)+(d_tornillo_servo/2)+margen_tornillo_servo, -(z_servo/2)+(h_tornillo_servo/2)]){
                    cylinder(d=d_tornillo_servo, h=h_tornillo_servo, $fn=200, center=true);
                }
                translate([0, -(y_servo/2)-(d_tornillo_servo/2)-margen_tornillo_servo, -(z_servo/2)+(h_tornillo_servo/2)]){
                    cylinder(d=d_tornillo_servo, h=h_tornillo_servo, $fn=200, center=true);
                }
            }
        }
        translate([0,(-y_caja/2)+(d_herramienta/2)+margen_herramienta,0]){
            cylinder(h=h_herramienta, d=d_herramienta, $fn=200, center=true);
        }
        translate([0,(-y_caja/2)+(h_tornillo_sujecion/2)-0.01,0]){
            rotate([90, 0, 0]){
             cylinder(h=h_tornillo_sujecion, d=d_tornillo_sujecion, $fn=200, center=true);
            }
        }   
    }
}
}

