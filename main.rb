#!/usr/bin/env ruby -w

require_relative 'parse'
require_relative 'astar'
require_relative 'solvability'
require_relative 'Node'
require_relative 'List'

def main
  start, n = parse_puzzle(ARGV[0])
  goal = generate_solution(n)
  if is_solvable(start.flatten, goal.flatten, n)
    start.each {|y| puts "#{y}\n"}
    puts
    puts astar(start, goal)
  else
    puts "Puzzle is not solvable."
  end
end

main
