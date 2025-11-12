//
// Created by Argyraspides on 9/7/25.
//
#pragma once

#include "Vec2I.hpp"
#include <array>
#include <memory>

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
    Frame( size_t width, size_t height );
    Frame( Frame&& otherFrame );
    Frame( const Frame& otherFrame );

    ~Frame();

    [[nodiscard]] bool Empty() const;
    [[nodiscard]] int Width() const;
    [[nodiscard]] int Height() const;
    [[nodiscard]] int FlatSize() const;
    [[nodiscard]] wchar_t At( int x, int y ) const;
    [[nodiscard]] wchar_t At( Vec2I pos ) const;

    bool Write( int x, int y, wchar_t dat, FrameSection section = FrameSection::NONE );
    bool Write( Vec2I point, wchar_t dat, FrameSection section = FrameSection::NONE );

    void SetSection( FrameSection section, Vec2I offset, Vec2I dimension );

    Vec2I GetSectionOffset( FrameSection section );
    Vec2I GetSectionDimension( FrameSection section );

  private:
    void ValidateSection( FrameSection section );

  private:
    std::unique_ptr< std::vector< std::vector< wchar_t > > > m_buffer;

    std::unique_ptr< std::array< Vec2I, static_cast< size_t >( FrameSection::MAX ) > > m_frameSectionOffsets;
    std::unique_ptr< std::array< Vec2I, static_cast< size_t >( FrameSection::MAX ) > > m_frameSectionDimensions;

    size_t m_frameWidth;
    size_t m_frameHeight;
};
