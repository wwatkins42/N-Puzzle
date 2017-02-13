require 'gosu'

class NPuzzle < Gosu::Window
	def initialize(size, map)
		super 1024, 720
		self.caption = "NPuzzle"
		@map = map

		@background_image = Gosu::Image.new("media/huDiDyr.jpg", :tileable =>true)
		@board = Board.new(self, './media/Palette_NTSC.png',size)
	end

	def update

	end

	def draw
		@background_image.draw(0, 0, 0)
		@board.draw
	end
end

class Tile

	attr_reader :position

	def initialize(tileset, tile_pos)
		@image = tileset[tile_pos]
		@position = tile_pos
	end
end

class Board

	TILE_SIZE = 32
	Z_ORDER = 1
	ZOOM_SIZE = 4

	def initialize (window, tiles_path, size, map)
		@tileset = Gosu::Image.load_tiles(window, tiles_path, TILE_SIZE, TILE_SIZE, false)
		@size = size
		@board = generate_board
	end

	def draw
		@board.each_with_index do |line, height|
			puts height
			line.each_with_index do |tile, width|
				puts width
				@tileset[tile[0].position].draw(height * TILE_SIZE * ZOOM_SIZE + 200, width * TILE_SIZE * ZOOM_SIZE + 40, Z_ORDER, ZOOM_SIZE, ZOOM_SIZE)
				tile[1].draw(height * TILE_SIZE * ZOOM_SIZE + 200, width * TILE_SIZE * ZOOM_SIZE + 40, Z_ORDER)
			end
		end
	end

	private

	def generate_board
		board = Array.new(@size, [])
		color = 0
		n = 0
		(0..(@size-1)).each do |x|
			line = []
			(0..(@size-1)).each do |y|
				line << [Tile.new(@tileset, color), Gosu::Image.from_text(color.to_s, 80)]
				color += 1
				if color >= 12 && color % (12 + n) == 0
					color += 4
					n += 4
				end
			end
			board[x] = line
		end
		return board
	end

end

map = [[1, 2, 3, 4],
	   [12, 13, 14, 5],
   	   [11, 0, 15, 6],
   	   [10, 9, 8, 7]]
window = NPuzzle.new(5, map)
# tile = Tile.new
window.show
