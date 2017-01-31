#!/usr/bin/env ruby -w

class List
  attr_accessor :nodes

  def initialize
    @nodes = []
  end

  def add(node)
    @nodes.push(node)
  end

  def remove(node)
    @nodes.delete(node)
  end

  def get_min
    v = 2147483647
    n = nil
    @nodes.each do |node|
      if node.fScore < v
        v = node.fScore
        n = node
      end
    end
    return n
  end

  def contains?(grid)
    @nodes.each do |node|
      return true if node.grid == grid
    end
    return false
  end
end
