import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class Strip {
	List<Operador> operadores;
	
	public void generarOperadores(){
		/**
	
		// algoritmo de permutaci�n en java
		String[] letras = new String[] {"A","B","C","S"};
		
		permutacion(letras,"",3 ,4);
		
		for(Operador operador: operadores ){
			System.out.println(operador.toString());
		}
		
		**/
		
		operadores.add(new Operador (Operador.MOVER, "A", "B", "C"));
		operadores.add(new Operador (Operador.MOVER, "A", "B", "S"));
		operadores.add(new Operador (Operador.MOVER, "A", "C", "B"));
		operadores.add(new Operador (Operador.MOVER, "A", "C", "S"));
		operadores.add(new Operador (Operador.MOVER, "A", "S", "B"));
		operadores.add(new Operador (Operador.MOVER, "A", "S", "C"));
		
		operadores.add(new Operador (Operador.MOVER, "B", "A", "C"));
		operadores.add(new Operador (Operador.MOVER, "B", "A", "S"));
		operadores.add(new Operador (Operador.MOVER, "B", "C", "A"));
		operadores.add(new Operador (Operador.MOVER, "B", "C", "S"));
		operadores.add(new Operador (Operador.MOVER, "B", "S", "A"));
		operadores.add(new Operador (Operador.MOVER, "B", "S", "C"));
		
		operadores.add(new Operador (Operador.MOVER, "C", "A", "B"));
		operadores.add(new Operador (Operador.MOVER, "C", "A", "S"));
		operadores.add(new Operador (Operador.MOVER, "C", "B", "A"));
		operadores.add(new Operador (Operador.MOVER, "C", "B", "S"));
		operadores.add(new Operador (Operador.MOVER, "C", "S", "A"));
		operadores.add(new Operador (Operador.MOVER, "C", "S", "B"));
		
	}
	
	private void permutacion (String[] elementos, String actual, int tamGrupo, int elementosGrupo) {
		// cada vez que agregamos uno reducimos
        if (tamGrupo != 0) { 
            for (int i = 0; i < elementosGrupo; i++) {
                if (!actual.contains(elementos[i])) { // Controla que no haya repeticiones
                	permutacion(elementos, actual + elementos[i] + " ", tamGrupo - 1, elementosGrupo);
                }
            }
        } else {
        	
            String letras[] = actual.split(" ");
            // no vale que empiece por S.
	        if (!letras[0].equals("S")){
	        	System.out.println("Primera letra: "+letras[0]);
	            System.out.println(actual);
	            operadores.add(new Operador (Operador.MOVER, letras[0], letras[1], letras[2]));
            }
        }
    }
	
	public Strip(){
		
		// Operadores Mundo, generar todas las combinaciones.
		operadores = new LinkedList<Operador>();
		// Podr�a meterlos manualmente...
		generarOperadores();
		
		// Estado Inicial
		List<Propiedad> propiedadesIni = new LinkedList<Propiedad>();
		propiedadesIni.add (new Propiedad(Propiedad.CIMA, "B"));
		propiedadesIni.add (new Propiedad(Propiedad.SOBRE, "B","A"));
		propiedadesIni.add (new Propiedad(Propiedad.SOBRE, "A","C"));
		propiedadesIni.add (new Propiedad(Propiedad.SOBRE, "C","S"));
		Estado estadoInicial = new Estado(propiedadesIni);
		
		// Estado final
		List<Propiedad> objetivos = new LinkedList<Propiedad>();
		objetivos.add (new Propiedad(Propiedad.CIMA, "C"));
		objetivos.add (new Propiedad(Propiedad.SOBRE, "C","B"));
		objetivos.add (new Propiedad(Propiedad.SOBRE, "B","A"));
		objetivos.add (new Propiedad(Propiedad.SOBRE, "A","S"));
		Estado estadoObjetivo = new Estado(objetivos);
		
		// Plan - inicialmente sin nada
		Stack<Operador> plan = new Stack<Operador>();
		
		Stack<Estado> estados = new Stack<Estado>();
		estados.add(estadoInicial);
		
		Planear(estados, estadoObjetivo, plan);
		
		System.out.println("------------------------- Plan");
		for(Operador operacionPlan : plan){
			System.out.println(operacionPlan);
		}
	
	}

	
	boolean Planear(Stack<Estado> estados, Estado objetivos, Stack<Operador> plan){
		Estado estado = estados.peek();
		if(objetivosCompletados(estado, objetivos)){
			return true;
		}
		else{
			List<Operador> operadorAplicables = getOperadoresAplicables(estado);
			
			for(Operador operador: operadorAplicables){
				Estado nuevoEstado = actualizarEstado(estado, operador);
				if(!estados.contains(nuevoEstado)){
					estados.push(nuevoEstado);
					plan.push(operador);
					if(Planear(estados, objetivos, plan))
						return true;
					else {
						estados.pop();
						plan.pop();
					}
				}
			}
		}
		return false;
	}
	

	private Estado actualizarEstado(Estado estado, Operador operador) {
		// Crear nuevo estado.
		LinkedList<Propiedad> propiedades = new LinkedList<Propiedad>();
		propiedades.addAll(estado.propiedades);
		Estado nuevoEstado =  new Estado(propiedades);

		nuevoEstado.propiedades.addAll(operador.propiedadesAgregar);
		nuevoEstado.propiedades.removeAll(operador.propiedadesEliminar);
		
		return nuevoEstado;
	}
	
	boolean objetivosCompletados (List<Propiedad> estadoInicial, Stack<Propiedad> objetivos){
		return estadoInicial.containsAll(objetivos);
	}
	
	boolean objetivosCompletados (Estado estado, Estado objetivos){
		return estado.propiedades.containsAll(objetivos.propiedades);
	}
	
	private List<Operador> getOperadoresAplicables (Estado estado) {
		List<Operador> operadoresAplicables = new LinkedList<Operador>();
		
		for( Operador operador : operadores){
			// �Cumple las precondiciones?
			if (estado.propiedades.containsAll(operador.precondiciones)){
				operadoresAplicables.add(operador);
			}
		}
	
		return operadoresAplicables;
	}
	
}
