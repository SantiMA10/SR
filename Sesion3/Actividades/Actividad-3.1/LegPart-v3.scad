mainbox = [40,24,10];
inbox = [34, 70, 60];

union(){
    difference(){
       union(){
           translate([-mainbox[0],-mainbox[1],0])
             cube(mainbox);
           
           translate([0,-mainbox[1],mainbox[2]/2])
           rotate([0,-90,0])
           cylinder(h=mainbox[0],r=mainbox[2]/2);
           
           
                
       }
       union(){
           translate([-inbox[0]-3,-inbox[1]-3,-1])
            cube([inbox[0],inbox[1],inbox[2]]);
           
           translate([-5,-mainbox[1],mainbox[2]/2])
           rotate([0,90,0])
           cylinder(h=7.5,r=mainbox[2]/4,$fn=20);
           
           translate([-5,-11,mainbox[2]/2])
           rotate([0,90,0])
           cylinder(h=7.5,r=.5,$fn=20);
           
           translate([-5,-17,mainbox[2]/2])
           rotate([0,90,0])
           cylinder(h=7.5,r=.5,$fn=20);
           
           translate([-11,-5,mainbox[2]/2])
           rotate([-90,0,0])
           cylinder(h=7.5,r=.5,$fn=20);
           
           translate([-29,-5,mainbox[2]/2])
           rotate([-90,0,0])
           cylinder(h=7.5,r=.5,$fn=20);
           
           translate([-20,-5,mainbox[2]/2])
           rotate([-90,0,0])
           cylinder(h=7.5,r=2,$fn=20);
            
       } 
    }
    translate([-mainbox[0],-mainbox[1],mainbox[2]/2])
       rotate([0,90,0])
       cylinder(h=7.5,r=mainbox[2]/4.5,$fn=20);
}
    