
x_caja = 53.4+10;
y_caja = 68.6+10;
z_caja = 30;

x_cables = 8;
y_cables = 30;
z_cables = x_cables;

x_superior = 8;
y_superior = 40;
z_superior = x_superior;

separcion_caja_tapa =5;

 difference(){
    translate([0,0,30/2])
        cube ([x_caja,y_caja,z_caja], center = true);
     translate([0,0,30/2+5])
        cube ([x_caja-10,y_caja-10,z_caja], center = true);
     translate([x_caja/5,y_caja/2,z_caja/2-5])
        cube ([x_cables,y_cables,z_cables], center = true);
     translate([-x_caja/5,y_caja/2,z_caja/2-5])
        cube ([x_cables,y_cables,z_cables], center = true);
 }
 
 difference(){
    translate([x_caja+separcion_caja_tapa,0,z_caja])
        cube ([x_caja,y_caja,2], center = true);
     translate([x_caja+separcion_caja_tapa,0,z_caja+2])
        cube ([x_superior,y_superior,z_superior], center = true);
 }
  
