//
// Created by robin on 05.11.22.
//

#ifndef GAME_DEV_TEMPLATE_COLORI_HPP
#define GAME_DEV_TEMPLATE_COLORI_HPP

#include <type_traits>
#include <cstdint>
#include <string>

namespace ggj
{
    /*!
     * Using Colori (Color Int) not to interfere with the raylib definition of "Color"
     */
    class Colori
    {
        public:
            /*!
             * Parses color from color format #aarrggbb in hex format or optionally #rrggbb.
             * @param color Colori in "#rrggbbaa" hex format.
             * @example "#ffaa07ff" and "#aa07ff". In cases where alpha is not a value, it is set to 255.
            */
            inline explicit Colori(const std::string &color)
            {
                parseHexString(color);
            }
            inline Colori(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
            inline Colori() { r = g = b = 0; a = 255; }

            inline bool operator==(const Colori &rhs) const;
            inline bool operator==(const std::string &rhs) const;
            inline bool operator!=(const Colori &rhs) const;

            /*! Red */
            uint8_t r{};
            /*! Green */
            uint8_t g{};
            /*! Blue */
            uint8_t b{};
            /*! Alpha */
            uint8_t a{};

        private:
            void parseHexString(const std::string &color)
            {
                if (color.size() == 9)
                {
                    a = std::stoi(color.substr(1, 2), nullptr, 16);
                    r = std::stoi(color.substr(3, 2), nullptr, 16);
                    g = std::stoi(color.substr(5, 2), nullptr, 16);
                    b = std::stoi(color.substr(7, 2), nullptr, 16);
                }
                else if (color.size() == 7)
                {
                    r = std::stoi(color.substr(1, 2), nullptr, 16);
                    g = std::stoi(color.substr(3, 2), nullptr, 16);
                    b = std::stoi(color.substr(5, 2), nullptr, 16);
                    a = 255;
                }
            }

    };

    /*!
     * Create a new color in rgba (red, green, blue, alpha) format
     */
    Colori::Colori(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    bool Colori::operator==(const std::string &rhs) const
    {
        Colori other {rhs};
        return *this == other;
    }

    bool Colori::operator==(const Colori &rhs) const
    {
        return r == rhs.r &&
               g == rhs.g &&
               b == rhs.b &&
               a == rhs.a;
    }

    bool Colori::operator!=(const Colori &rhs) const
    {
        return !(rhs == *this);
    }
}
#endif //GAME_DEV_TEMPLATE_COLORI_HPP
