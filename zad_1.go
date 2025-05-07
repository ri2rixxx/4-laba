package main

import (
 "fmt"
 "math"
)

func f(x float64) float64 {
 return x*math.Log(x+2) - 2
}

func df(x float64) float64 {
 return math.Log(x+2) + x/(x+2)
}

func phi(x float64) float64 {
 return 2 / math.Log(x+2)
}

func bisection(a, b, eps float64) {
 fmt.Println("\nМетод половинного деления")
 fmt.Printf("%-4s%-12s%-12s%-12s\n", "N", "a", "b", "b-a")
 n := 0
 for (b - a) >= eps {
  c := (a + b) / 2
  fmt.Printf("%-4d%-12.6f%-12.6f%-12.6f\n", n, a, b, b-a)
  if f(a)*f(c) < 0 {
   b = c
  } else {
   a = c
  }
  n++
 }
 fmt.Printf("Корень ≈ %.8f\n", (a+b)/2)
}

func newton(x0, eps float64) {
 fmt.Println("\nМетод Ньютона")
 fmt.Printf("%-4s%-14s%-14s%-14s\n", "N", "x_n", "x_n+1", "|x_n+1 - x_n|")
 n := 0
 for {
  x1 := x0 - f(x0)/df(x0)
  fmt.Printf("%-4d%-14.8f%-14.8f%-14.8f\n", n, x0, x1, math.Abs(x1-x0))
  if math.Abs(x1-x0) < eps {
   fmt.Printf("Корень ≈ %.8f\n", x1)
   break
  }
  x0 = x1
  n++
 }
}

func iteration(x0, eps float64) {
 fmt.Println("\nМетод простых итераций")
 fmt.Printf("%-4s%-14s%-14s%-14s\n", "N", "x_n", "x_n+1", "|x_n+1 - x_n|")
 n := 0
 for {
  x1 := phi(x0)
  fmt.Printf("%-4d%-14.8f%-14.8f%-14.8f\n", n, x0, x1, math.Abs(x1-x0))
  if math.Abs(x1-x0) < eps {
   fmt.Printf("Корень ≈ %.8f\n", x1)
   break
  }
  x0 = x1
  n++
 }
}

func main() {
 var a, b, x0, eps float64
 fmt.Print("Введите a, b, x0, eps: ")
 fmt.Scan(&a, &b, &x0, &eps)

 bisection(a, b, eps)
 newton(x0, eps)
 iteration(x0, eps)
}
