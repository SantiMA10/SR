cubo_X = 32;
cubo_Y = 36;
cubo_Z = 4;
cubo_Radio = 4;

module crearCubo() {
    rotate([0,180,0])
    hull() {
    for (i=[0:3])
        translate([(i % 2) * cubo_X, (i - i % 2) * cubo_Y, 0]) {
            cylinder(r=cubo_Radio, h=1);
            translate([0, 0, cubo_Z])
                sphere(cubo_Radio);
        }
    }
}

module crearAgujeros() {
    translate([-cubo_X + (cubo_X/6), (cubo_Y - cubo_Y/5)/3, -40])
    cube([cubo_X * 2 / 3, cubo_Y / 3, 50]);
        
    translate([-cubo_X + (cubo_X/6), cubo_Y + (cubo_Y - cubo_Y/8)/2, -40])
    cube([cubo_X * 2 / 3, cubo_Y / 3, 50]);
        
    translate([-cubo_X/2, cubo_Y, -40])
    cylinder(r=2, h=50);
        
    translate([-cubo_X/2, cubo_Y/9, -40])
    cylinder(r=1.5, h=50, $fn=10);
        
    translate([-cubo_X/2, cubo_Y * 2 - (cubo_Y/15), -40])
    cylinder(r=1.5, h=50, $fn=10);    
        
          
    translate([-cubo_X/11, cubo_Y/2 - 2, -40])
    cylinder(r=1, h=50, $fn=10);       
        
    translate([-cubo_X + cubo_X/11, cubo_Y/2 - 2, -40])
    cylinder(r=1, h=50, $fn=10);     

    translate([-cubo_X/11, cubo_Y + cubo_Y/2 + 4, -40])
    cylinder(r=1, h=50, $fn=10);       
        
    translate([-cubo_X + cubo_X/11, cubo_Y + cubo_Y/2 + 4, -40])
    cylinder(r=1, h=50, $fn=10);     
}

rotate([0, 0, 90])
translate([16, -37, 3])
difference() {
    crearCubo();  
    #crearAgujeros();
}