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


difference(){
    *cube([x_caja, y_caja, z_caja], center=true);
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
    
}

translate([0,(-y_caja/2)+(d_tornillo_sujecion/2),0]){
        rotate([90, 0, 0]){
         cylinder(h=h_tornillo_sujecion, d=d_tornillo_sujecion, $fn=200, center=true);
        }
    }   


