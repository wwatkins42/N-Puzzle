#!/usr/bin/env ruby -w

def parse_puzzle(filename)
  if filename == nil
    return generate_puzzle
  end
  content = File.read(filename)
  n = content.scan(/^\d{1,}$/)[0].to_i
  puzzle = content.scan(/^[ \d]{3,}/).map(&:split).map{|x| x.map(&:to_i)}
  if !(puzzle.map(&:size).all? {|x| x == n}) || puzzle.size != n || n < 3 ||
    puzzle.flatten != puzzle.flatten.uniq || puzzle.flatten.any? {|x| x >= n * n}
    return generate_puzzle
  end
  return puzzle, n
end

if $PROGRAM_NAME == __FILE__
  require_relative 'solvability'

  puzzle, n = parse_puzzle(ARGV[0])
  if (!is_solvable(puzzle.flatten, generate_solution(n).flatten, n))
      puts 'False'
  else
      puts n
      puts "#{puzzle.flatten.join(',')}"
  end
end
