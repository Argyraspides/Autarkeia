#pragma once

#include <cassert>
#include <vector>

template < size_t N, size_t M > class Matf
{
  public:
    Matf() = default;

    int Rows()
    {
        return m_mat.size();
    }

    int Cols()
    {
        return m_mat.size() > 0 ? m_mat[ 0 ].size() : 0;
    }

    float At( size_t row, size_t col )
    {
        return m_mat.at( row ).at( col );
    }

    std::vector< float >& operator[]( size_t idx )
    {
        return m_mat.at( idx );
    }

  private:
    std::vector< std::vector< float > > m_mat = std::vector< std::vector< float > >( N, std::vector< float >( M ) );
};