
public class Propiedad {
	public static int SOBRE = 1;
	public static int CIMA = 2;
	int tipo;
	String A = null; 
	String B = null;
	
	
	public Propiedad(int tipo, String a, String b) {
		super();
		this.tipo = tipo;
		A = a;
		B = b;
	}


	public Propiedad(int tipo, String a) {
		super();
		this.tipo = tipo;
		A = a;
	}

	

	@Override
	public boolean equals(Object obj) {
		Propiedad propiedad = (Propiedad) obj;
		// null.equals(null)
		if (tipo == propiedad.tipo && A.equals(propiedad.A) && 
				( (B == null && propiedad.B == null) || ( B.equals(propiedad.B)))){
			
			return true;
		} 
		return false;

	}


	@Override
	public String toString() {
		if (tipo == 1)
			return A + " sobre "+ B;
		else
			return A + " en la cima ";
		
	}
	
	
}
