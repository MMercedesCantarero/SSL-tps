import java.util.Random;

public class JavaBubbleSort {
    public static void main(String[] args) {
        // Crear un array de 10,000 elementos
        int size = 10000;
        int[] array = new int[size];
        Random rand = new Random();

        // Llenar el array con valores aleatorios
        for (int i = 0; i < size; i++) {
            array[i] = rand.nextInt(10000); // números aleatorios entre 0 y 9999
        }

        // Mostrar los primeros 5 y últimos 5 elementos antes de ordenar
        System.out.print("Primeros 5 elementos antes de ordenar: ");
        for (int i = 0; i < 5; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println();

        System.out.print("Últimos 5 elementos antes de ordenar: ");
        for (int i = size - 5; i < size; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println();

        // Medir el tiempo antes de ordenar
        long startTime = System.currentTimeMillis();

        // Ordenar el array usando Bubble Sort
        bubbleSort(array);

        // Medir el tiempo después de ordenar
        long endTime = System.currentTimeMillis();
        long duration = endTime - startTime;

        // Mostrar los primeros 5 y últimos 5 elementos después de ordenar
        System.out.print("Primeros 5 elementos después de ordenar: ");
        for (int i = 0; i < 5; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println();

        System.out.print("Últimos 5 elementos después de ordenar: ");
        for (int i = size - 5; i < size; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println("\n");

        // Mostrar la duración en milisegundos
        System.out.println("Duración: " + duration + " ms");
    }

    // Método para realizar el Bubble Sort
    public static void bubbleSort(int[] arr) {
        int n = arr.length;  // Longitud del array
        int temp = 0;   // Variable temporal para el intercambio
        for(int i=0; i < n; i++){ // Primer loop
            for(int j=1; j < (n-i); j++){ // Segundo loop
                if(arr[j-1] > arr[j]){  // Si quiero orden descendente, cambio > por <

                    //Intercambiar elementos
                    temp = arr[j-1];
                    arr[j-1] = arr[j];
                    arr[j] = temp;

                }
            }
        }
    }
}