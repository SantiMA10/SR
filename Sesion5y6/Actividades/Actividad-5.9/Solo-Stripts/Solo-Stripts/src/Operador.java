import java.util.LinkedList;
import java.util.List;


public class Operador {
	public static int MOVER = 1;
	
	int tipo;
	String A = null; 
	String B = null; 
	String C = null; 
	
	List<Propiedad> precondiciones;
	List<Propiedad> propiedadesEliminar;
	List<Propiedad> propiedadesAgregar;
	
	
	public Operador(int tipo, String a, String b, String c) {
		super();
		
		// precondiciones
		precondiciones = new LinkedList<Propiedad>();
		precondiciones.add(new Propiedad(Propiedad.SOBRE, a, b));
		precondiciones.add(new Propiedad(Propiedad.CIMA, a));
		if (!c.equals("S"))
			precondiciones.add(new Propiedad(Propiedad.CIMA, c));
		
		// eliminar
		propiedadesEliminar = new LinkedList<Propiedad>();
		propiedadesEliminar.add(new Propiedad(Propiedad.SOBRE, a, b));
		propiedadesEliminar.add(new Propiedad(Propiedad.CIMA, c));
		
		// agregar
		propiedadesAgregar = new LinkedList<Propiedad>();
		propiedadesAgregar.add(new Propiedad(Propiedad.SOBRE, a, c));
		if (!b.equals("S"))
			propiedadesAgregar.add(new Propiedad(Propiedad.CIMA, b));
		
		this.tipo = tipo;
		A = a;
		B = b;
		C = c;
	}


	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return "Mover " +A+ " que está sobre "+B+" encima del "+C;
	}


	@Override
	public boolean equals(Object obj) {
		Operador operador = (Operador) obj;
		if (tipo == operador.tipo &&  A.equals(operador.A) && B.equals(operador.B) && C.equals(operador.C))
			return true;
		else 
			return false;
	}
	
	
	


}
