//
// Created by Argyraspides on 9/7/25.
//
#pragma once

#include "Vec2I.hpp"
#include <array>
#include <memory>

class Frame
{
  public:
    enum class Section
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

    enum class Border
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,

        MAX
    };

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

    bool Write( int x, int y, wchar_t dat, Section section = Section::NONE );
    bool Write( Vec2I point, wchar_t dat, Section section = Section::NONE );

    void SetSection( Section section, Vec2I offset, Vec2I dimension );

    Vec2I GetSectionOffset( Section section );
    Vec2I GetSectionDimension( Section section );

    bool InFrame( Vec2I screenPos );

  private:
    void ValidateSection( Section section );

  private:
    // TODO::ARGYRASPIDES() { You did this for move semantics but you're a dummy and these already have move
    // constructors. Also there's no reason for this shit to be unique ptr bruh ... please understand and benchmark shit
    // before you pull theories out of your ass on what should be more efficient }
    std::unique_ptr< std::vector< std::vector< wchar_t > > > m_buffer;

    std::unique_ptr< std::array< Vec2I, static_cast< size_t >( Section::MAX ) > > m_frameSectionOffsets;
    std::unique_ptr< std::array< Vec2I, static_cast< size_t >( Section::MAX ) > > m_frameSectionDimensions;

    size_t m_frameWidth;
    size_t m_frameHeight;
};
