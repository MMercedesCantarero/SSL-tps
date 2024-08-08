import kotlin.random.Random

fun main() {
    // Crear un array de 10,000 elementos
    val size = 10000
    val array = IntArray(size) { Random.nextInt(10000) } // Llenar el array con valores aleatorios entre 0 y 9999

    // Mostrar los primeros 5 y últimos 5 elementos antes de ordenar
    print("Primeros 5 elementos antes de ordenar: ")
    for (i in 0 until 5) {
        print("${array[i]} ")
    }
    println()

    print("Últimos 5 elementos antes de ordenar: ")
    for (i in (size - 5) until size) {
        print("${array[i]} ")
    }
    println()

    // Medir el tiempo antes de ordenar
    val startTime = System.currentTimeMillis()

    // Ordenar el array usando Bubble Sort
    bubbleSort(array)

    // Medir el tiempo después de ordenar
    val endTime = System.currentTimeMillis()
    val duration = endTime - startTime

    // Mostrar los primeros 5 y últimos 5 elementos después de ordenar
    print("Primeros 5 elementos después de ordenar: ")
    for (i in 0 until 5) {
        print("${array[i]} ")
    }
    println()

    print("Últimos 5 elementos después de ordenar: ")
    for (i in (size - 5) until size) {
        print("${array[i]} ")
    }
    println()

    // Mostrar la duración en milisegundos
    println(" ")
    println("Duración: $duration ms")
}

// Método para realizar el Bubble Sort
fun bubbleSort(arr: IntArray) {
    val n = arr.size
    for (i in 0 until n) { // Primer loop
        for (j in 1 until (n - i)) { // Segundo loop
            if (arr[j - 1] > arr[j]) { // Orden ascendente

                val temp = arr[j - 1]
                arr[j - 1] = arr[j]
                arr[j] = temp
            }
        }
    }
}