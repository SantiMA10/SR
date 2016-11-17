mainbox = [30,41,20];
inbox = [24, 38, 60];
sides = [57,11,4];

difference(){
    union(){
        translate([-mainbox[0]/2,0,0])
        cube(mainbox);
        
        translate([-sides[0]/2,0,0])
        cube(sides);
    }

translate([-inbox[0]/2,-1,-1])
cube([inbox[0],inbox[1]+1,inbox[2]]);
}