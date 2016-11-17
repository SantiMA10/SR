mainbox = [73.6,14,40.1];
inbox = [70, 38, 60];
sides = [70,2,110];
backbox = [52,15,29.4];

union(){
    difference(){
        union(){
            translate([-mainbox[0]/2,-mainbox[1],0])
            cube(mainbox);
            
            translate([-sides[0]/2,-sides[1],0])
            cube(sides);
            
            translate([-backbox[0]/2,0,27.593])
            cube(backbox);
        }
    union(){
        translate([-inbox[0]/2,-inbox[1]-2,10])
        cube([inbox[0],inbox[1],inbox[2]]);
        
        translate([-inbox[0]/2,-(mainbox[1]-4)-2,2])
        cube([inbox[0],mainbox[1]-4,inbox[2]]);
        };
        
        translate([-50,1.7365,17.745])
        rotate([10,0,0])
        cube([100,30,10]);
        
        translate([-50,0,57])
        rotate([-7.5,0,0])
        cube([100,30,10]);
        
        translate([-50,10.2,57])
        rotate([-80,0,0])
        cube([100,30,10]);
        
        translate([-22.5,2,0])
        cube([45,20,100]);
    }
    
    translate([-backbox[0]/2,0,27.593])
    rotate([10,0,0])
    cube([backbox[0],15.1,4]);
}