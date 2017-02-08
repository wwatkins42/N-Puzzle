#!/usr/bin/env ruby -w

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
