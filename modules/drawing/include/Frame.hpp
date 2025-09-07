//
// Created by gaugamela on 9/7/25.
//

#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP
#include <string>

class Frame
{
  public:
    Frame( int width, int height );
    ~Frame();

    const bool Empty() const;
    const int Width() const;
    const int Height() const;
    const int FlatSize() const;

    bool Write( const int& x, const int& y, const char& dat );
    const char At( const int& x, const int& y ) const;
    std::string& Buffer();

  private:
    std::string m_buffer;
    int m_frameWidth;
    int m_frameHeight;
};

#endif // FRAMEBUFFER_HPP
