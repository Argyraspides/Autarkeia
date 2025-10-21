//
// Created by Argyraspides on 9/7/25.
//

#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP
#include <string>

struct Vec2I;
class Frame
{
  public:
    Frame() = delete;
    Frame( int width, int height );
    ~Frame();

    [[nodiscard]] bool Empty() const;
    [[nodiscard]] int Width() const;
    [[nodiscard]] int Height() const;
    [[nodiscard]] int FlatSize() const;
    [[nodiscard]] char At( const int& x, const int& y ) const;

    bool Write( const int& x, const int& y, const char& dat );
    bool Write( const Vec2I& point, const char& dat );


    std::string& Buffer();

  private:
    std::string m_buffer;
    int m_frameWidth;
    int m_frameHeight;
};

#endif // FRAMEBUFFER_HPP
