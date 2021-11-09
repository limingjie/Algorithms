//
// Solution to Game BlockPuzzle
//
// Author: Mingjie Li (limingjie0719@gmail.com)
// Date  : Aug 27, 2013
//
// TODO: GUI
//

#include <algorithm>  // std::sort
#include <iomanip>    // std::setw
#include <iostream>   // std::cout,   std::endl
#include <string>     // std::string, std::to_string
#include <utility>    // std::pair,   std::make_pair
#include <vector>

typedef std::vector<std::pair<size_t, size_t>> BlockData;
typedef std::vector<size_t>                    BoardData;

// Debug Tracking
static size_t count_setblock   = 0;
static size_t count_checkblock = 0;
static size_t count_setcell    = 0;
static size_t count_checkcell  = 0;

class Block
{
public:
    Block(const std::string &cells);

    void Print(const std::string &title = "Block") const;
    void Print(size_t board_width, size_t board_height, size_t x, size_t y,
               const std::string &title = "Block") const;

private:
    friend class Board;

    BlockData data;

    size_t width;
    size_t height;
    double weight;

    void SetCell(size_t x, size_t y);
};

typedef std::vector<Block> Blocks;

class Board
{
public:
    Board(size_t width, size_t height);

    bool Resolve(const Blocks &blocks);
    bool SetBlock(const Block &block, size_t x, size_t y);

    void Print(const std::string &title = "Board") const;

private:
    BoardData data;

    size_t width;
    size_t height;

    void SetCell(size_t x, size_t y);
    bool CheckCell(size_t x, size_t y) const;
    void ClearCell(size_t x, size_t y);
    bool CheckBlock(const Block &block, size_t x, size_t y) const;
    void ClearBlock(const Block &block, size_t x, size_t y);
    bool FindSolution(const Blocks &blocks, size_t block_index);
};

Block::Block(const std::string &cells)
{
    data   = BlockData();
    width  = 0;
    height = 0;
    weight = 0;

    size_t x = 0;
    size_t y = 0;
    for (auto &c : cells)
    {
        switch (c)
        {
            case '*':
                SetCell(x, y);
                x++;
                break;
            case '|':
                x = 0;
                y++;
                break;
            default:
                x++;
                break;
        }
    }

    weight = data.size() * width * height;
}

// Compose a block
void Block::SetCell(size_t x, size_t y)
{
    data.push_back(std::make_pair(x, y));

    if (x >= width) width = x + 1;
    if (y >= height) height = y + 1;
}

void Block::Print(const std::string &title) const { Print(width, height, 0, 0, title); }

void Block::Print(size_t board_width, size_t board_height, size_t block_x, size_t block_y,
                  const std::string &title) const
{
    Board b(board_width, board_height);
    b.SetBlock(*this, block_x, block_y);
    b.Print(title);
}

Board::Board(size_t width, size_t height)
{
    this->width  = width;
    this->height = height;

    data = BoardData(width * height, 0);
}

// SetCell cell (x, y) = 1
inline void Board::SetCell(size_t x, size_t y)
{
    count_setcell++;
    data[y * width + x] = 1;
}

// Check if cell (x, y) is empty
bool Board::CheckCell(size_t x, size_t y) const
{
    count_checkcell++;
    return (data[y * width + x] == 0);
}

// SetCell cell (x, y) = 0
void Board::ClearCell(size_t x, size_t y) { data[y * width + x] = 0; }

// Put block on board starts from cell (x, y)
// return true if ok
// return false if not fit.
bool Board::SetBlock(const Block &block, size_t x, size_t y)
{
    if (!CheckBlock(block, x, y))
    {
        return false;
    }

    for (auto &c : block.data)
    {
        SetCell(x + c.first, y + c.second);
    }

    count_setblock++;
    return true;
}

bool Board::CheckBlock(const Block &block, size_t x, size_t y) const
{
    count_checkblock++;

    if (block.width + x > width || block.height + y > height) return false;

    for (auto &c : block.data)
    {
        if (!CheckCell(c.first + x, c.second + y))
        {
            return false;
        }
    }

    return true;
}

// Clear the block from board
void Board::ClearBlock(const Block &block, size_t x, size_t y)
{
    for (auto &c : block.data)
    {
        ClearCell(x + c.first, y + c.second);
    }
}

// This is the core solution
bool Board::FindSolution(const Blocks &blocks, size_t block_index)
{
    const Block &block = blocks[block_index];

    size_t xmax = width - block.width;
    size_t ymax = height - block.height;

    for (size_t x = 0; x <= xmax; x++)
    {
        for (size_t y = 0; y <= ymax; y++)
        {
            // if there is a place for block, process.
            if (SetBlock(block, x, y))
            {
                // If the block is the last one, solution found.
                // If not the last one, process other blocks.
                if (block_index == blocks.size() - 1 || FindSolution(blocks, block_index + 1))
                {
                    // If all other blocks are positioned correctly, solution found.
                    std::cout << "Step: Put block " << block_index << " at [" << x << ", " << y
                              << "]" << std::endl;
                    block.Print(width, height, x, y, "Block " + std::to_string(block_index));
                    return true;
                }
                else
                {
                    // If not able to found a solution for other blocks, rollback current block,
                    // and continually find next available position for current block.
                    ClearBlock(block, x, y);
                    continue;
                }
            }
        }
    }

    return false;
}

// Start solving the problem.
bool Board::Resolve(const Blocks &blocks)
{
    Blocks copy(blocks);

    // Sort Blocks by block weight
    std::sort(copy.begin(), copy.end(), [](Block &a, Block &b) { return (a.weight > b.weight); });

    size_t i = 0;
    for (auto &block : copy)
    {
        block.Print("Block " + std::to_string(i++));
    }

    // Find solution
    bool result = FindSolution(copy, 0);

    std::cout << "count_setblock   = " << count_setblock << std::endl
              << "count_checkblock = " << count_checkblock << std::endl
              << "count_setcell    = " << count_setcell << std::endl
              << "count_checkcell  = " << count_checkcell << std::endl;

    return result;
}

void Board::Print(const std::string &title) const
{
    std::cout << title << std::endl << "   ";

    for (size_t i = 0; i < width; i++)
    {
        std::cout << std::setw(2) << i;
    }

    for (size_t i = 0; i < width * height; i++)
    {
        if (i % width == 0)
        {
            std::cout << std::endl << std::setw(2) << i / width << ' ';
        }

        std::cout << (data[i] ? "[]" : "__");
    }

    std::cout << std::endl << std::endl;
}

void puzzle(size_t i) {}

int main()
{
    struct
    {
        Board  Board;
        Blocks Blocks;
    } puzzles[] = {
        {
            Board(10, 6),
            Blocks{
                Block("*****|* *"),
                Block(" ***|***|  *"),
                Block(" **|***| **"),
                Block(" *|**|*|*"),
                Block(" *|****| *"),
                Block("*|***|  **|  *"),
                Block("*|***| **|  *"),
                Block(" * **|****"),
                Block("  **|*****"),
            },
        },
        {
            Board(5, 6),
            Blocks{
                Block("**"),
                Block("***"),
                Block("****"),
                Block("*|**| *"),
                Block("*|*|**"),
                Block("*|**|*"),
                Block("**|*"),
                Block("** *| ***"),
            },
        },
        {
            Board(10, 3),
            Blocks{
                Block("***|* *"),
                Block("*|***"),
                Block(" **|**"),
                Block("*|*"),
                Block("****|   *"),
                Block("**|**"),
                Block(" *|**"),
                Block("***"),
            },
        },
        {
            Board(6, 5),
            Blocks{
                Block("***|*"),
                Block("****"),
                Block(" *|**|*"),
                Block("*|**"),
                Block("***"),
                Block("**|**"),
                Block("*|*"),
                Block("  *|* *|***"),
            },
        },
        {
            Board(5, 6),
            Blocks{
                Block("***"),
                Block("***| *| *"),
                Block("**|**"),
                Block("*|**"),
                Block(" **| *|**"),
                Block("*|*"),
                Block("***|  *"),
                Block("*|**| *"),
            },
        },
    };

    auto &puzzle = puzzles[4];
    if (!puzzle.Board.Resolve(puzzle.Blocks))
    {
        std::cout << "No solution!" << std::endl;
    }

    return 0;
}
