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

if $PROGRAM_NAME == __FILE__
    if (ARGV.count > 0)
        n = ARGV[0].to_i
        puzzle = generate_solution(n)
        puts "#{puzzle.flatten.join(',')}"
    end
end
