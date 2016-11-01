
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
