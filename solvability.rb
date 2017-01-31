#!/usr/bin/env ruby -w

def generate_solution(n)
  inc = 0
  puzzle = Array.new(n){Array.new(n)}
  (0..(n + 1) / 2).each do |depth|
    r = depth
    while r < n - depth
      puzzle[depth][r] = (inc += 1)
      r += 1
    end
    d = depth + 1
    while d < n - depth
      puzzle[d][r - 1] = (inc += 1)
      d += 1
    end
    l = d - 1
    while l - 1 >= depth
      puzzle[d - 1][l - 1] = (inc += 1)
      l -= 1
    end
    u = d - 1
    while u - 1 > depth
      puzzle[u - 1][l] = (inc += 1)
      u -= 1
    end
  end
  puzzle.each {|y| y.index(n*n) ? puzzle[puzzle.index(y)][y.index(n*n)] = 0 : nil}
  return puzzle
end

def invertion_count(tab)
  invertion = 0
  i = 0
  tab.each do |x|
    (i..(tab.count-1)).each do |y|
      if (tab[y] != 0 && x != 0 && x > tab[y])
        invertion += 1
      end
    end
    i += 1
  end
  return invertion
end

def is_solvable(puzzle, goal, size)

  invertion_puzzle = invertion_count(puzzle);
  invertion_goal = invertion_count(goal);
  
  if size % 2 == 0
    invertion_goal += goal.index(0)
    invertion_puzzle += puzzle.index(0)
  end
  return (invertion_puzzle % 2 == invertion_goal % 2)
end
