import kotlin.random.Random
import kotlin.system.measureTimeMillis

fun main() {
    // Crear una lista de 10,000 elementos con valores aleatorios
    val array = IntArray(10000) { Random.nextInt(10000) }

    // Mostrar los primeros y últimos 5 elementos antes de ordenar
    println("Primeros 5 elementos sin ordenar: ${array.copyOfRange(0, 5).joinToString(", ")}")
    println("Últimos 5 elementos sin ordenar: ${array.copyOfRange(array.size - 5, array.size).joinToString(", ")}")

    // Medir el tiempo de ejecución del ordenamiento
    val timeTaken = measureTimeMillis {
        quickSort(array, 0, array.size - 1)
    }

    // Mostrar los primeros y últimos 5 elementos después de ordenar
    println("Primeros 5 elementos ordenados: ${array.copyOfRange(0, 5).joinToString(", ")}")
    println("Últimos 5 elementos ordenados: ${array.copyOfRange(array.size - 5, array.size).joinToString(", ")}")
    println("");
    // Mostrar el tiempo que tardó en milisegundos
    println("Duración: $timeTaken ms")
}

// Función para realizar Quick Sort
fun quickSort(arr: IntArray, low: Int, high: Int) {
    if (low < high) {
        // Encuentra la posición del pivote y particiona el arreglo
        val pi = partition(arr, low, high)

        // Ordena los subarreglos a la izquierda y a la derecha del pivote
        quickSort(arr, low, pi - 1)
        quickSort(arr, pi + 1, high)
    }
}

// Función para particionar el arreglo y colocar el pivote en la posición correcta
fun partition(arr: IntArray, low: Int, high: Int): Int {
    val pivot = arr[high] // Elegir el pivote como el último elemento del subarreglo
    var i = low - 1 // Índice del elemento menor

    for (j in low until high) {
        if (arr[j] <= pivot) {
            i++
            arr.swap(i, j) // Intercambiar elementos
        }
    }
    arr.swap(i + 1, high) // Colocar el pivote en la posición correcta
    return i + 1
}

// Función de extensión para intercambiar elementos en un arreglo
fun IntArray.swap(i: Int, j: Int) {
    val temp = this[i]
    this[i] = this[j]
    this[j] = temp
}