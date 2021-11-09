//
// Solution to Game BlockPuzzle
//
// Author: Mingjie Li (limingjie0719@gmail.com)
// Date  : Aug 27, 2013
//
// Compiled successfully with g++ 4.8.1
//   g++ -std=c++11 -Wall -O2 -o BlockPuzzle BlockPuzzle.cpp
//
// TODO: GUI
//

#include <iostream>
#include <iomanip> // setw
#include <algorithm> // sort
#include <vector>
#include <string>

using namespace std;

typedef vector<pair<size_t, size_t>> BlockData;
typedef vector<size_t> BoardData;

class Block
{
public:
    Block();
    ~Block();

    Block& operator()(size_t x, size_t y);
    Block& operator()(string x, size_t y = 0);

    void Print(string title = "Block");
    void Print(size_t board_width, size_t board_height, size_t x, size_t y, string title = "Block");
    const BlockData* GetData() const;

    size_t width;
    size_t height;
    double weight;

private:

    BlockData *data;
};

typedef vector<Block *> Blocks;

class Board
{
public:
    Board(size_t width, size_t height);
    ~Board();

    bool Unblock(Blocks bs);
    void Print(string title = "Board");
    bool SetBlock(Block *b, size_t x, size_t y);

private:
    void SetCell(size_t x, size_t y);
    bool CheckCell(size_t x, size_t y);
    void ClearCell(size_t x, size_t y);
    bool CheckBlock(Block *b, size_t x, size_t y);
    void ClearBlock(Block *b, size_t x, size_t y);
    bool RecursiveSetBlock(Blocks &bs, size_t block_index);

    size_t width;
    size_t height;

    size_t count_setblock;
    size_t count_checkblock;
    size_t count_setcell;
    size_t count_checkcell;

    BoardData *data;
};

Block::Block()
{
    data = new BlockData();

    width = 0;
    height = 0;
    weight = 0;
}

Block::~Block()
{
    delete data;
}

// Compose a block
Block& Block::operator()(size_t x, size_t y)
{
    data->push_back(make_pair(x, y));

    if (x >= width) width = x + 1;
    if (y >= height) height = y + 1;

    // B - 2693,         , D - 5956
    // weight = height * height * width * 1.0 / data->size();

    // B - 1457, C - 3995, D - 4387
    // weight = data->size() * width * height * height;

    // B - 3017, C - 2185, D - 3365
    weight = data->size() * width * height;

    return (*this);
}

// Compose a block
Block& Block::operator()(string cells, size_t y)
{
    size_t x = 0;

    for (auto i = cells.cbegin(); i != cells.cend(); i++)
    {
        if ((*i) == '*')
        {
            (*this)(x, y);
        }
        else if ((*i) == '|')
        {
            x = 0;
            y++;

            continue;
        }

        x++;
    }

    return (*this);
}

inline const BlockData* Block::GetData() const
{
    return (const BlockData *) data;
}

void Block::Print(string title)
{
    Board b(width, height);
    b.SetBlock(this, 0, 0);
    b.Print(title);
}

void Block::Print(size_t board_width, size_t board_height, size_t block_x, size_t block_y, string title)
{
    Board b(board_width, board_height);
    b.SetBlock(this, block_x, block_y);
    b.Print(title);
}

Board::Board(size_t width, size_t height)
{
    this->width = width;
    this->height = height;

    data = new BoardData(width * height, 0);
}

Board::~Board()
{
    delete data;
}

// Set cell (x, y) = 1
inline void Board::SetCell(size_t x, size_t y)
{
    count_setcell++;
    (*data)[y * width + x] = 1;
}

// Check if cell (x, y) is empty
inline bool Board::CheckCell(size_t x, size_t y)
{
    count_checkcell++;
    return ((*data)[y * width + x] == 0);
}

// Set cell (x, y) = 0
inline void Board::ClearCell(size_t x, size_t y)
{
    (*data)[y * width + x] = 0;
}

// Put block on board starts from cell (x, y)
// return true if ok
// return false if not fit.
bool Board::SetBlock(Block *b, size_t x, size_t y)
{
    if (!CheckBlock(b, x, y))
    {
        return false;
    }

    const BlockData* d = b->GetData();
    for(auto i = d->cbegin(); i != d->cend(); i++)
    {
        SetCell(x + i->first, y + i->second);
    }

    count_setblock++;
    return true;
}

bool Board::CheckBlock(Block *b, size_t x, size_t y)
{
    count_checkblock++;

    if (b->width + x > width || b->height + y > height)
        return false;

    const BlockData* d = b->GetData();
    for(auto i = d->cbegin(); i != d->cend(); i++)
    {
        if (!CheckCell(i->first + x, i->second + y))
        {
            return false;
        }
    }

    return true;
}

// Clear the block from board
void Board::ClearBlock(Block *b, size_t x, size_t y)
{
    const BlockData* d = b->GetData();
    for(auto i = d->cbegin(); i != d->cend(); i++)
    {
        ClearCell(x + i->first, y + i->second);
    }
}

// This is the core solution
bool Board::RecursiveSetBlock(Blocks &bs, size_t block_index)
{
    Block* block = bs[block_index];

    size_t xmax = width - block->width;
    size_t ymax = height - block->height;

    for (size_t x = 0; x <= xmax; x++)
    {
        for (size_t y = 0; y <= ymax; y++)
        {
            // if there is a place for block, process.
            if (SetBlock(block, x, y))
            {
                // If the block is the last one, solution found.
                if (block_index == bs.size() - 1)
                {
                    cout << "Step: Put block " << block_index << " at [" << x << ", " << y << "]" << endl;
                    block->Print(width, height, x, y, "Block " + to_string(block_index));
                    return true;
                }

                // If not the last one, process other blocks.
                if (RecursiveSetBlock(bs, block_index + 1))
                {
                    // If all other blocks are positioned correctly, solution found.
                    cout << "Step: Put block " << block_index << " at [" << x << ", " << y << "]" << endl;
                    block->Print(width, height, x, y, "Block " + to_string(block_index));
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
bool Board::Unblock(Blocks bs)
{
    count_setblock = 0;
    count_checkblock = 0;
    count_setcell = 0;
    count_checkcell = 0;

    // Sort Blocks by block weight
    sort(bs.begin(), bs.end(), [](Block *a, Block *b)
    {
        return (a->weight > b->weight);
    });

    for (auto i = bs.cbegin(); i != bs.cend(); i++)
    {
        (*i)->Print("Block " + to_string(i - bs.cbegin()));
    }

    // Find solution
    bool result = RecursiveSetBlock(bs, 0);

    cout << "count_setblock   = " << count_setblock << endl
         << "count_checkblock = " << count_checkblock << endl
         << "count_setcell    = " << count_setcell << endl
         << "count_checkcell  = " << count_checkcell << endl;

    return result;
}

void Board::Print(string title)
{
    cout << title << endl << "   ";

    for (size_t i = 0; i < width; i++)
    {
        cout << setw(2) << i;
    }

    for (size_t i = 0; i < width * height; i++)
    {
        if (i % width == 0)
        {
            cout << endl << setw(2) << i / width << ' ';
        }

        if ((*data)[i])
        {
            cout << "[]";
        }
        else
        {
            cout << "__";
        }
    }

    cout << endl << endl;
}

void puzzle_d()
{
    Blocks bs;
    Board board(10, 6);

    bs.push_back(&(*(new Block()))("*****|* *"));
    bs.push_back(&(*(new Block()))(" ***|***|  *"));
    bs.push_back(&(*(new Block()))(" **|***| **"));
    bs.push_back(&(*(new Block()))(" *|**|*|*"));
    bs.push_back(&(*(new Block()))(" *|****| *"));
    bs.push_back(&(*(new Block()))("*|***|  **|  *"));
    bs.push_back(&(*(new Block()))("*|***| **|  *"));
    bs.push_back(&(*(new Block()))(" * **|****"));
    bs.push_back(&(*(new Block()))("  **|*****"));

    cout << "---------- Puzzle D ----------" << endl;

    if (!board.Unblock(bs))
    {
        cout << "No solution!" << endl;
    }

    for (auto i = bs.cbegin(); i != bs.cend(); i++)
    {
        delete (*i);
    }
}

void puzzle_e()
{
    Blocks bs;
    Board board(5, 6);

    bs.push_back(&(*(new Block()))("**"));
    bs.push_back(&(*(new Block()))("***"));
    bs.push_back(&(*(new Block()))("****"));
    bs.push_back(&(*(new Block()))("*|**| *"));
    bs.push_back(&(*(new Block()))("*|*|**"));
    bs.push_back(&(*(new Block()))("*|**|*"));
    bs.push_back(&(*(new Block()))("**|*"));
    bs.push_back(&(*(new Block()))("** *| ***"));

    cout << "---------- Puzzle E ----------" << endl;

    if (!board.Unblock(bs))
    {
        cout << "No solution!" << endl;
    }

    for (auto i = bs.cbegin(); i != bs.cend(); i++)
    {
        delete (*i);
    }
}

void puzzle_f()
{
    Blocks bs;
    Board board(10, 3);

    bs.push_back(&(*(new Block()))("***|* *"));
    bs.push_back(&(*(new Block()))("*|***"));
    bs.push_back(&(*(new Block()))(" **|**"));
    bs.push_back(&(*(new Block()))("*|*"));
    bs.push_back(&(*(new Block()))("****|   *"));
    bs.push_back(&(*(new Block()))("**|**"));
    bs.push_back(&(*(new Block()))(" *|**"));
    bs.push_back(&(*(new Block()))("***"));

    cout << "---------- Puzzle F ----------" << endl;

    if (!board.Unblock(bs))
    {
        cout << "No solution!" << endl;
    }

    for (auto i = bs.cbegin(); i != bs.cend(); i++)
    {
        delete (*i);
    }
}

void puzzle_g()
{
    Blocks bs;
    Board board(6, 5);

    bs.push_back(&(*(new Block()))("***|*"));
    bs.push_back(&(*(new Block()))("****"));
    bs.push_back(&(*(new Block()))(" *|**|*"));
    bs.push_back(&(*(new Block()))("*|**"));
    bs.push_back(&(*(new Block()))("***"));
    bs.push_back(&(*(new Block()))("**|**"));
    bs.push_back(&(*(new Block()))("*|*"));
    bs.push_back(&(*(new Block()))("  *|* *|***"));

    cout << "---------- Puzzle G ----------" << endl;

    if (!board.Unblock(bs))
    {
        cout << "No solution!" << endl;
    }

    for (auto i = bs.cbegin(); i != bs.cend(); i++)
    {
        delete (*i);
    }
}

void puzzle_h()
{
    Blocks bs;
    Board board(6, 5);

    bs.push_back(&(*(new Block()))("***|*"));
    bs.push_back(&(*(new Block()))(" *|***"));
    bs.push_back(&(*(new Block()))(" *|**| *| *"));
    bs.push_back(&(*(new Block()))("**|*"));
    bs.push_back(&(*(new Block()))("*****"));
    bs.push_back(&(*(new Block()))("*|*"));
    bs.push_back(&(*(new Block()))("**|**"));
    bs.push_back(&(*(new Block()))("*|*|*"));

    cout << "---------- Puzzle H ----------" << endl;

    if (!board.Unblock(bs))
    {
        cout << "No solution!" << endl;
    }

    for (auto i = bs.cbegin(); i != bs.cend(); i++)
    {
        delete (*i);
    }
}

void puzzle_i()
{
    Blocks bs;
    Board board(5, 6);

    bs.push_back(&(*(new Block()))("***"));
    bs.push_back(&(*(new Block()))("***| *| *"));
    bs.push_back(&(*(new Block()))("**|**"));
    bs.push_back(&(*(new Block()))("*|**"));
    bs.push_back(&(*(new Block()))(" **| *|**"));
    bs.push_back(&(*(new Block()))("*|*"));
    bs.push_back(&(*(new Block()))("***|  *"));
    bs.push_back(&(*(new Block()))("*|**| *"));

    cout << "---------- Puzzle I ----------" << endl;

    if (!board.Unblock(bs))
    {
        cout << "No solution!" << endl;
    }

    for (auto i = bs.cbegin(); i != bs.cend(); i++)
    {
        delete (*i);
    }
}

int main()
{
    puzzle_i();

    return 0;
}
