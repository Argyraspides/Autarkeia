//
// Created by Argyraspides on 9/7/25.
//

#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP
#include "Vec2I.hpp"
#include <array>
#include <string>

enum class FrameSection
{
    ZERO = 0,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,

    MAX,
    NONE,
    INVALID
};

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
    [[nodiscard]] char At( int x, int y ) const;

    bool Write( int x, int y, char dat, FrameSection section = FrameSection::NONE );
    bool Write( Vec2I point, char dat, FrameSection section = FrameSection::NONE );

    void SetSection( FrameSection section, Vec2I offset, Vec2I dimension );

    std::string& Buffer();

  private:
    void ValidateSection( FrameSection section );
  private:
    std::string m_buffer;

    std::array< Vec2I, static_cast< size_t >( FrameSection::MAX )> m_frameSectionOffsets;
    std::array< Vec2I, static_cast< size_t >( FrameSection::MAX )> m_frameSectionDimensions;

    int m_frameWidth;
    int m_frameHeight;
};

#endif // FRAMEBUFFER_HPP
