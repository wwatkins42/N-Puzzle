#!/usr/bin/env ruby -w

def random_puzzle(puzzle, size, i)
    c = Array.new(2)
    i.times do |x|
        move = rand(4)
        puzzle.each {|y| y.index(0) ? c = [puzzle.index(y), y.index(0)] : nil}
        if move == 0 && c[0] - 1 >= 0
            puzzle[c[0] - 1][c[1]], puzzle[c[0]][c[1]] = puzzle[c[0]][c[1]], puzzle[c[0] - 1][c[1]]
        elsif move == 1 && c[1] + 1 < size
            puzzle[c[0]][c[1] + 1], puzzle[c[0]][c[1]] = puzzle[c[0]][c[1]], puzzle[c[0]][c[1] + 1]
        elsif move == 2 && c[0] + 1 < size
            puzzle[c[0] + 1][c[1]], puzzle[c[0]][c[1]] = puzzle[c[0]][c[1]], puzzle[c[0] + 1][c[1]]
        elsif move == 3 && c[1] - 1 >= 0
            puzzle[c[0]][c[1] - 1], puzzle[c[0]][c[1]] = puzzle[c[0]][c[1]], puzzle[c[0]][c[1] - 1]
        end
    end
    return puzzle
end

if $PROGRAM_NAME == __FILE__
    require_relative 'generate_solution'

    n = ARGV[0].to_i
    puzzle = generate_solution(n)
    puzzle = random_puzzle(puzzle, n, 10000) # MAY SEGFAULT WITH 2 or 4 or 3, or even another value
    puts "#{puzzle.flatten.join(',')}"
end
