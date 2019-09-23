import java.util.Scanner;
import java.util.Random;


public class Tree23_Main {



    public static void main(String[] args) {
		//Vars here
		int nextNumber = 0, numBuscar=0, numEliminar=0;

        Tree23<Integer> tree = new Tree23<>();

        Scanner scanner = new Scanner(System.in);

        //Insertando los elementos random al árbol
        tree.add(857898);
        tree.add(344154);
        tree.add(127590);
        tree.add(5027);
        tree.add(4925);
        tree.add(880343);
        tree.add(600025);
        tree.add(386632);
        tree.add(486084);
        tree.add(18);

        Random rnd = new Random();
		for(int i=0;i<=99990;i++){
			nextNumber = rnd.nextInt(1000000-0)+1;
			tree.add(nextNumber);
        }

		//Función buscar
		System.out.println("Numero a buscar: ");
		numBuscar = scanner.nextInt();
		long startTime = System.nanoTime();
		tree.search(numBuscar);
		long endTime = System.nanoTime() - startTime;
		System.out.println("El tiempo de ejecución es: " + endTime);


		//Impresión ordenada ascendente
		tree.inOrder();

		System.out.println("");
		//Borrar
		System.out.println("Numero a eliminar: ");
		numEliminar = scanner.nextInt();
		tree.remove(numEliminar);

		tree.inOrder();

		//Impresión ordenada descendentemente

		//Obtener la altura

		//Obtener la profundidad

    }



}

//El código fue obtenido de la siguiente liga https://github.com/SValentyn/2-3-tree/tree/master/src