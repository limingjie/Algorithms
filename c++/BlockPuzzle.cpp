//
// Solution to Game BlockPuzzle
//
// Author: Mingjie Li (limingjie@outlook.com)
// Date  : Aug 27, 2013
//
// TODO: GUI
//

#include <algorithm>  // std::sort
#include <iomanip>    // std::setw
#include <iostream>   // std::cout,   std::endl
#include <map>        // Ordered Map
#include <string>     // std::string, std::to_string
#include <utility>    // std::pair,   std::make_pair
#include <vector>     // std::vector

// Debug Tracking
static size_t count_setblock   = 0;
static size_t count_checkblock = 0;
static size_t count_setcell    = 0;
static size_t count_checkcell  = 0;

class Block
{
public:
    typedef std::vector<std::pair<size_t, size_t>> Cells;

    Block(size_t index, const std::string &cells);
    ~Block();

    const Cells &GetCells() const;
    const size_t GetIndex() const;
    const size_t GetWidth() const;
    const size_t GetHeight() const;
    const size_t GetWeight() const;
    void         Print() const;

private:
    Cells  cells;
    size_t index;
    size_t width;
    size_t height;
    double weight;

    void SetCell(size_t x, size_t y);
};

class Board
{
public:
    typedef std::map<size_t, std::pair<size_t, size_t>> Solution;

    Board(size_t width, size_t height);
    ~Board();

    const Solution &Solve(const std::vector<Block> &blocks);
    bool            SetBlock(const Block &block, size_t x, size_t y);
    void            Print() const;

private:
    std::vector<size_t> data;
    Solution            steps;
    size_t              width;
    size_t              height;

    void SetCell(size_t x, size_t y, size_t value = 0);
    bool CheckCell(size_t x, size_t y) const;
    void ClearCell(size_t x, size_t y);
    bool CheckBlock(const Block &block, size_t x, size_t y) const;
    void ClearBlock(const Block &block, size_t x, size_t y);
    bool Search(const std::vector<Block> &blocks);
};

Block::Block(size_t index, const std::string &cells)
{
    this->cells = Cells();
    this->cells.reserve(cells.size());
    this->index = index;
    width       = 0;
    height      = 0;

    size_t x = 0;
    size_t y = 0;
    for (auto const &c : cells)
    {
        switch (c)
        {
            case '*':
                SetCell(x++, y);
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

    weight = this->cells.size() * width * height;
}

Block::~Block()
{
    // std::cout << "Block Released." << std::endl;
}

const Block::Cells &Block::GetCells() const { return cells; }
const size_t        Block::GetIndex() const { return index; }
const size_t        Block::GetWidth() const { return width; }
const size_t        Block::GetHeight() const { return height; }
const size_t        Block::GetWeight() const { return weight; }

// Compose a block
void Block::SetCell(size_t x, size_t y)
{
    cells.push_back(std::make_pair(x, y));

    if (x >= width) width = x + 1;
    if (y >= height) height = y + 1;
}

void Block::Print() const
{
    Board b(width, height);
    b.SetBlock(*this, 0, 0);
    b.Print();
}

Board::Board(size_t width, size_t height)
{
    this->width  = width;
    this->height = height;

    data = std::vector<size_t>(width * height, -1);
}

Board::~Board()
{
    // std::cout << "Board Released." << std::endl;
}

// SetCell cell (x, y) = 1
inline void Board::SetCell(size_t x, size_t y, size_t value)
{
    count_setcell++;
    data[y * width + x] = value;
}

// Check if cell (x, y) is empty
bool Board::CheckCell(size_t x, size_t y) const
{
    count_checkcell++;
    return (data[y * width + x] == -1);
}

// SetCell cell (x, y) = 0
void Board::ClearCell(size_t x, size_t y) { data[y * width + x] = -1; }

// Put block on board starts from cell (x, y)
// return true if ok
// return false if not fit.
bool Board::SetBlock(const Block &block, size_t x, size_t y)
{
    if (!CheckBlock(block, x, y))
    {
        return false;
    }

    for (auto const &c : block.GetCells())
    {
        SetCell(x + c.first, y + c.second, block.GetIndex());
    }

    count_setblock++;
    return true;
}

bool Board::CheckBlock(const Block &block, size_t x, size_t y) const
{
    count_checkblock++;

    if (block.GetWidth() + x > width || block.GetHeight() + y > height) return false;

    for (auto const &c : block.GetCells())
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
    for (auto const &c : block.GetCells())
    {
        ClearCell(x + c.first, y + c.second);
    }
}

// This is the core solution
bool Board::Search(const std::vector<Block> &blocks)
{
    static size_t depth = 0;

    // If no block left, solution found!
    if (depth == blocks.size())
    {
        depth--;  // Return to the previous block
        return true;
    }

    const Block &block = blocks[depth];

    size_t x_max = width - block.GetWidth();
    size_t y_max = height - block.GetHeight();
    for (size_t x = 0; x <= x_max; x++)
    {
        for (size_t y = 0; y <= y_max; y++)
        {
            // if there is a place for block, process.
            if (SetBlock(block, x, y))
            {
                depth++;  // Try the next block
                if (Search(blocks))
                {
                    steps[block.GetIndex()] = std::make_pair(x, y);
                    depth--;  // Return to the previous block
                    return true;
                }

                // If not able to found a solution for other blocks, rollback current block,
                // and continually find next available position for current block.
                ClearBlock(block, x, y);
            }
        }
    }

    depth--;  // Return to the previous block
    return false;
}

// Start solving the problem.
const Board::Solution &Board::Solve(const std::vector<Block> &blocks)
{
    std::vector<Block> copy(blocks);

    // Sort Blocks by block weight
    std::sort(copy.begin(), copy.end(),
              [](Block &a, Block &b) { return (a.GetWeight() > b.GetWeight()); });

    // Find solution
    bool found = Search(copy);
    if (!found) steps.clear();

    return steps;
}

void Board::Print() const
{
    static const std::string pattern("=*-o+WM~^");

    std::cout << "  ";
    for (size_t i = 0; i < width; i++)
    {
        std::cout << std::setw(3) << i;
    }

    for (size_t i = 0; i < width * height; i++)
    {
        if (i % width == 0)
        {
            std::cout << '\n' << std::setw(2) << i / width << ' ';
        }

        if (data[i] == -1)
        {
            std::cout << " . ";
        }
        else
        {
            std::cout << '[' << pattern[data[i] % pattern.size()] << ']';
        }
    }

    std::cout << '\n' << std::endl;
}

int main()
{
    struct
    {
        Board              Board;
        std::vector<Block> Blocks;
    } puzzles[] = {
        {
            Board(10, 6),
            std::vector<Block>{
                Block(0, "*****|* *"),
                Block(1, " ***|***|  *"),
                Block(2, " **|***| **"),
                Block(3, " *|**|*|*"),
                Block(4, " *|****| *"),
                Block(5, "*|***|  **|  *"),
                Block(6, "*|***| **|  *"),
                Block(7, " * **|****"),
                Block(8, "  **|*****"),
            },
        },
        {
            Board(5, 6),
            std::vector<Block>{
                Block(0, "**"),
                Block(1, "***"),
                Block(2, "****"),
                Block(3, "*|**| *"),
                Block(4, "*|*|**"),
                Block(5, "*|**|*"),
                Block(6, "**|*"),
                Block(7, "** *| ***"),
            },
        },
        {
            Board(10, 3),
            std::vector<Block>{
                Block(0, "***|* *"),
                Block(1, "*|***"),
                Block(2, " **|**"),
                Block(3, "*|*"),
                Block(4, "****|   *"),
                Block(5, "**|**"),
                Block(6, " *|**"),
                Block(7, "***"),
            },
        },
        {
            Board(6, 5),
            std::vector<Block>{
                Block(0, "***|*"),
                Block(1, "****"),
                Block(2, " *|**|*"),
                Block(3, "*|**"),
                Block(4, "***"),
                Block(5, "**|**"),
                Block(6, "*|*"),
                Block(7, "  *|* *|***"),
            },
        },
        {
            Board(5, 6),
            std::vector<Block>{
                Block(0, "***"),
                Block(1, "***| *| *"),
                Block(2, "**|**"),
                Block(3, "*|**"),
                Block(4, " **| *|**"),
                Block(5, "*|*"),
                Block(6, "***|  *"),
                Block(7, "*|**| *"),
            },
        },
    };

    auto &puzzle = puzzles[4];

    for (auto const &block : puzzle.Blocks)
    {
        std::cout << "Block " + std::to_string(block.GetIndex()) << '\n';
        block.Print();
    }

    auto steps = puzzle.Board.Solve(puzzle.Blocks);
    if (steps.size() != 0)
    {
        std::cout << "Steps\n";
        for (auto const &s : steps)
        {
            std::cout << "- Put block " << s.first << " on [" << s.second.first << ", "
                      << s.second.second << "]\n";
        }

        std::cout << "\nBoard\n";
        puzzle.Board.Print();
    }
    else
    {
        std::cout << "No solution!" << std::endl;
    }

    std::cout << "count_setblock   = " << count_setblock
              << "\ncount_checkblock = " << count_checkblock
              << "\ncount_setcell    = " << count_setcell
              << "\ncount_checkcell  = " << count_checkcell << std::endl;

    return 0;
}
