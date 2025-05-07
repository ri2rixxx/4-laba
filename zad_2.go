package main

import (
 "fmt"
 "math/rand"
 "strconv"
 "time"
)

func swapDigits(n int) int {
 if n < 10 {
  return n
 }
 s := strconv.Itoa(n)
 runes := []rune(s)
 runes[0], runes[len(runes)-1] = runes[len(runes)-1], runes[0]
 res, _ := strconv.Atoi(string(runes))
 return res
}

func main() {
 rand.Seed(time.Now().UnixNano())

 var n1, n2 int
 fmt.Print("Введите размер первого массива (n1 >= 10): ")
 fmt.Scan(&n1)
 if n1 < 10 {
  fmt.Println("Ошибка: n1 должно быть >= 10")
  return
 }

 fmt.Print("Введите размер второго массива (n2 >= 50): ")
 fmt.Scan(&n2)
 if n2 < 50 {
  fmt.Println("Ошибка: n2 должно быть >= 50")
  return
 }

 var arr1 [1000]float64
 var arr2 [1000]int

 // 1. Заполнение первого массива
 for i := 0; i < n1; i++ {
  arr1[i] = rand.Float64() * 100
 }
 fmt.Println("\nПервый массив (вещественные числа):")
 for i := 0; i < n1; i++ {
  fmt.Printf("%.2f ", arr1[i])
 }
 fmt.Println()

 // 2. Среднее и сумма квадратов отклонений
 sum := 0.0
 for i := 0; i < n1; i++ {
  sum += arr1[i]
 }
 avg := sum / float64(n1)

 sqSum := 0.0
 for i := 0; i < n1; i++ {
  diff := arr1[i] - avg
  sqSum += diff * diff
 }
 fmt.Printf("\nСреднее значение: %.4f\n", avg)
 fmt.Printf("Сумма квадратов разностей: %.4f\n", sqSum)

 // 3. Замена разрядов
 for i := 0; i < n1; i++ {
  val := int(arr1[i])
  if i%2 == 0 && val%2 == 0 {
   arr1[i] = float64(swapDigits(val))
  }
 }
 fmt.Println("\nПосле замены разрядов:")
 for i := 0; i < n1; i++ {
  fmt.Printf("%.2f ", arr1[i])
 }
 fmt.Println()

 // 4. Перемещение первого элемента в конец
 first := arr1[0]
 for i := 0; i < n1-1; i++ {
  arr1[i] = arr1[i+1]
 }
 arr1[n1-1] = first

 fmt.Println("\nПосле модификации (первый в конец):")
 for i := 0; i < n1; i++ {
  fmt.Printf("%.2f ", arr1[i])
 }
 fmt.Println()

 // 5. Заполнение второго массива
 for i := 0; i < n2; i++ {
  arr2[i] = rand.Intn(21) - 10 // [-10;10]
 }
 fmt.Println("\nВторой массив (целые числа):")
 for i := 0; i < n2; i++ {
  fmt.Printf("%d ", arr2[i])
 }
 fmt.Println()

 // Частоты
 var counts [21]int
 for i := 0; i < n2; i++ {
  counts[arr2[i]+10]++
 }

 fmt.Println("\nЧастоты элементов:")
 for i := 0; i < 21; i++ {
  if counts[i] > 0 {
   fmt.Printf("%d: %d\n", i-10, counts[i])
  }
 }

 // Удаление повторов
 var seen [21]bool
 var unique [21]int
 uniqueCount := 0
 for i := 0; i < n2; i++ {
  idx := arr2[i] + 10
  if !seen[idx] {
   seen[idx] = true
   unique[uniqueCount] = arr2[i]
   uniqueCount++
  }
 }
 fmt.Println("\nУникальные элементы:")
 for i := 0; i < uniqueCount; i++ {
  fmt.Printf("%d ", unique[i])
 }
 fmt.Println()
}
