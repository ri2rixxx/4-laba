package main

import (
 "bufio"
 "fmt"
 "os"
 "strings"
)

func readLine(scanner *bufio.Scanner) string {
 scanner.Scan()
 return scanner.Text()
}

// Метод Борда
func borda(votes [][]string, candidates []string) string {
 score := make(map[string]int)
 n := len(candidates)

 for _, vote := range votes {
  for i, cand := range vote {
   score[cand] += n - i - 1
  }
 }

 maxScore := -1
 var winner string
 for cand, s := range score {
  if s > maxScore {
   maxScore = s
   winner = cand
  }
 }
 return winner
}

// Метод Кондорсе
func condorcet(votes [][]string, candidates []string) string {
 n := len(candidates)
 winCount := make(map[string]map[string]int)

 // Инициализация
 for _, a := range candidates {
  winCount[a] = make(map[string]int)
  for _, b := range candidates {
   winCount[a][b] = 0
  }
 }

 for _, vote := range votes {
  for i := 0; i < n; i++ {
   for j := i + 1; j < n; j++ {
    winCount[vote[i]][vote[j]]++
   }
  }
 }

 for _, cand1 := range candidates {
  winner := true
  for _, cand2 := range candidates {
   if cand1 == cand2 {
    continue
   }
   if winCount[cand1][cand2] <= winCount[cand2][cand1] {
    winner = false
    break
   }
  }
  if winner {
   return cand1
  }
 }
 return "Нет победителя по Кондорсе"
}

func main() {
 scanner := bufio.NewScanner(os.Stdin)

 fmt.Print("Введите количество кандидатов и избирателей: ")
 var n, k int
 fmt.Scanf("%d %d\n", &n, &k)

 fmt.Println("Введите имена кандидатов:")
 scanner.Scan()
 candidates := strings.Fields(scanner.Text())

 votes := make([][]string, k)
 fmt.Println("Введите предпочтения избирателей (по", n, "кандидатов в строке):")
 for i := 0; i < k; i++ {
  scanner.Scan()
  votes[i] = strings.Fields(scanner.Text())
 }

 bordaWinner := borda(votes, candidates)
 condorcetWinner := condorcet(votes, candidates)

 fmt.Println("\nПобедитель по методу Борда:", bordaWinner)
 fmt.Println("Победитель по методу Кондорсе:", condorcetWinner)

 if bordaWinner != condorcetWinner && condorcetWinner != "Нет победителя по Кондорсе" {
  fmt.Println("Разные алгоритмы дали разные результаты.")
 }
}
