cubo_X = 45;
cubo_Y = 28;
cubo_Z = 4;
cubo_Radio = 4;

pieza1X = 6;
pieza1Y = 10;
pieza1Z = 8;

pieza2X = pieza1X;
pieza2Y = pieza1Y/2;
pieza2Z = pieza1Z * 3/5;

module crearCubo() {
    hull() {
    for (i=[0:3])
        translate([(i % 2) * cubo_X, (i - i % 2) * cubo_Y, 0]) {
            cylinder(r=cubo_Radio, h=1);
            translate([0, 0, cubo_Z])
                sphere(cubo_Radio);
        }
    }
}

module crearPieza1() {

    translate([cubo_X/2 + 3, cubo_X/2 + 3, cubo_Z + cubo_Radio])
    cube([pieza1X, pieza1Y, pieza1Z]);
}

module crearPieza2() {
    translate([-3, cubo_X/2 + pieza2Z , cubo_Z])
    cube([pieza2X, pieza2Y, pieza2Z + 2 * cubo_Z]);
}

translate([-23, -28, 0])
union() {
    crearCubo();
    crearPieza1();
    crearPieza2();
}