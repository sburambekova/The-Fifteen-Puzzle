
#include "frame.h"

// Default constructs in solved position:

frame::frame()
{
  // int frame[nrcolumns][nrrows];

  unsigned int a = 1;
  for (int i = 0; i < nrrows; i++)
  {
    for (int j = 0; j < nrcolumns; j++)
    {
      if(a<nrcolumns*nrrows){
      table[i][j] = a;
      a++;
    } else{
      open_place.row = i;
      open_place.column = j;
      table[i][j] = 0;
    }
    }
  }
 
}




frame::frame(std::initializer_list<std::initializer_list<unsigned int>> init)
{
  // unsigned int col = init.begin()->size();
  //  size_t row_Indx=0;

  // for(auto row:init){
  //     row_Indx++;
  //     size_t column_Indx=0;
  //     for(auto column : row){
  //         table[row_Indx][column_Indx] = column;
  //         column_Indx++;
  //         if(column == 0) {
  //       open_place.column = column_Indx;
  //       open_place.row = row_Indx; // index of empty cell
  //     }
  //     }
  // }

  unsigned int i = 0, j = 0;
  for (auto row : init)
  {
    for (auto tabl : row)
    {
      table[i][j] = tabl;
      if (tabl == 0)
      {
        open_place = position(i, j);
      }
      ++j;
    }
    ++i;
    j = 0;
  }
}

position frame::find(unsigned int val) const
{
  for (unsigned int i = 0; i < nrrows; i++)
  {
    for (unsigned int j = 0; j < nrcolumns; j++)
    {
      if (table[i][j] == val)
      {
        return position(i, j);
      }
    }
  }
  return position(-1, -1);
}

void frame::print(std::ostream &out) const
{
  for (unsigned int i = 0; i < nrrows; ++i)
  {
    for (unsigned int j = 0; j < nrcolumns; ++j)
    {
      out << std::setw(4);
      out << table[i][j] << " ";
    }
    out << std::endl;
  }
  out << "\n";
  out << "open place is at " << open_place << std::endl;
}

bool frame::makemove(move m)
{
  position newOpen_place = open_place;

  if (m == move::right)
  {
    ++newOpen_place.column;
  }
  else if (m == move::up)
  {
    --newOpen_place.row;
  }
  else if (m == move::down)
  {
    ++newOpen_place.row;
  }
  else if (m == move::left)
  {
    --newOpen_place.column;
  }
  //   open_place = newOpen_place;
  //   return true;
  // } else{
  //     return false;
  // }
  if (newOpen_place.row >= 0 && newOpen_place.row < nrrows && newOpen_place.column >= 0 && newOpen_place.column < nrcolumns)
  {
 
    std::swap(table[open_place.row][open_place.column], table[newOpen_place.row][newOpen_place.column]);
  
    open_place = newOpen_place;
    return true;
  }
  else
  {
    return false;
  }
}

bool frame::before::operator()(const frame &f1, const frame &f2) const
{
  for (size_t i = 0; i < frame::nrrows; i++)
  {
    for (size_t j = 0; j < frame::nrcolumns; j++)
    {
      if (f1.table[i][j] < f2.table[i][j])
      {
        return true;
      }
      else if (f1.table[i][j] > f2.table[i][j])
      {
        return false;
      }
    }
  }
  return false;
}

unsigned int frame::distance(const frame &f) const
{
  unsigned int total = 0;

  for (unsigned int i = 0; i < nrrows; i++)
  {
    for (unsigned int j = 0; j < nrcolumns; j++)
    {
      if (table[i][j] != 0)
      {
        position current(i, j);

        total += ::distance(current, f.find(table[i][j]));
      }
    
    }
  }

  return total;
}
