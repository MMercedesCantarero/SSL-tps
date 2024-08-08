import java.util.Arrays;
import java.util.Random;

public class JavaQuickSort {
    public static void main(String[] args) {
        // Crea una lista de 10,000 elementos con valores aleatorios
        int[] array = new int[10000];
        Random random = new Random();
        for (int i = 0; i < array.length; i++) {
            array[i] = random.nextInt(10000);
        }

        // Mostrar los primeros y últimos 5 elementos antes de ordenar

        System.out.println("Primeros 5 elementos sin ordenar: " + Arrays.toString(Arrays.copyOfRange(array, 0, 5)));
        System.out.println("Últimos 5 elementos sin ordenar: " + Arrays.toString(Arrays.copyOfRange(array, array.length - 5, array.length)));


        long startTime = System.currentTimeMillis();
        quickSort(array, 0, array.length - 1);
        long endTime = System.currentTimeMillis();

        // Mostrar los primeros y últimos 5 elementos después de ordenar
        System.out.println("Primeros 5 elementos ordenados: " + Arrays.toString(Arrays.copyOfRange(array, 0, 5)));
        System.out.println("Últimos 5 elementos ordenados: " + Arrays.toString(Arrays.copyOfRange(array, array.length - 5, array.length)));

        // Mostrar el tiempo que tardó en milisegundos
        System.out.println("");
        System.out.println("Duración: " + (endTime - startTime) + " ms");
    }

    private static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    private static int partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return i + 1;
    }
}