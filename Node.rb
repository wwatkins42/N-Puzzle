#!/usr/bin/env ruby -w

class Node
  include Comparable

  attr_accessor :grid, :gScore, :fScore, :moves

  def initialize(grid, gScore, moves)
    @grid = grid
    @gScore = gScore
    @fScore = 0
    @moves = moves
  end
end
