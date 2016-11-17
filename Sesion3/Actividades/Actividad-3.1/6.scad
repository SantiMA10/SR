anchoPared  = 1.5;

diffOffset = 10;

cuboX = 70;
cuboY = 20;
cuboZ = 24;

rotate([0, 0, 180])
translate([-39, -20, 0])
difference() {

cube([cuboX + 4 * anchoPared, cuboY, cuboZ]);

translate([-diffOffset/2, -diffOffset, -diffOffset/2])
#cube([cuboX/9 + diffOffset/2, cuboY - anchoPared + diffOffset, cuboZ + diffOffset]);
    
translate([cuboX / 9 + anchoPared, anchoPared, -diffOffset/2])
#cube([2 * cuboX/9, cuboY - anchoPared + diffOffset, cuboZ + diffOffset]);
    
translate([3 * cuboX / 9 + (2 * anchoPared), -diffOffset, -diffOffset/2])
#cube([3 * cuboX/9, cuboY - anchoPared + diffOffset, cuboZ + diffOffset]);    
    
translate([6 * cuboX / 9 + (3 * anchoPared), anchoPared, -diffOffset/2])
#cube([2 * cuboX/9, cuboY - anchoPared + diffOffset, cuboZ + diffOffset]);    
    
translate([8 * cuboX / 9 + (4 * anchoPared), -diffOffset, -diffOffset/2])    
#cube([cuboX/9 + diffOffset/2, cuboY - anchoPared + diffOffset, cuboZ + diffOffset]);    
   


translate([cuboX/18, cuboY + diffOffset / 2, cuboZ/2])        
rotate([90, 0, 0])
    #cylinder(h = anchoPared + diffOffset, r = 1.5, $fn=20);
    
translate([4 * cuboX/9 + 5*anchoPared, cuboY + diffOffset / 2, cuboZ/2])        
rotate([90, 0, 0])
    #cylinder(h = anchoPared + diffOffset, r = 1.5, $fn=20);    
    
translate([cuboX - cuboX/18 + 4* anchoPared, cuboY + diffOffset / 2, cuboZ/2])        
rotate([90, 0, 0])
    #cylinder(h = anchoPared + diffOffset, r = 1.5, $fn=20);    
}