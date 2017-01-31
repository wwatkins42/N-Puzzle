#!/usr/bin/env ruby -w

def random_puzzle(size)
    puzzle = []
    len = size * size
    range = (0..(size * size) - 1).to_a.shuffle
    while (len > 0)
        puzzle.push(range.shift)
        len -= 1
    end
    return puzzle
end
