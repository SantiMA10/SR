import java.util.LinkedList;
import java.util.List;


public class Estado {

	List<Propiedad> propiedades = new LinkedList<Propiedad>();

	public Estado(List<Propiedad> propiedades) {
		super();
		this.propiedades = propiedades;
	}

	
	@Override
	public boolean equals(Object obj) {
		// suponemos que no hay estados repetidos ni nada de eso
		Estado estado = (Estado) obj;
		
		if( propiedades.size() != estado.propiedades.size() ){
			return false;
		}
		
		if (propiedades.containsAll(estado.propiedades))
			return true;
		
		return false;
	}


	@Override
	public String toString() {
		String texto = "Estado: [";
		for(Propiedad propiedad: propiedades){
			texto+= propiedad + ",";
		}
		return texto + "]";
	}

	
	
}
