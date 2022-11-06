//
// Created by robin on 30.10.22.
//

#ifndef GAME_DEV_TEMPLATE_VECTOR2D_HPP
#define GAME_DEV_TEMPLATE_VECTOR2D_HPP

namespace dev
{

    template<typename T>
    class Vector2D
    {

        public:
            inline Vector2D(T xPos, T yPos);
            inline Vector2D() { x = y = 0; }

            inline bool operator==(const Vector2D &rhs) const;
            inline bool operator!=(const Vector2D &rhs) const;

            T x;
            T y;
    };

    /*!
     *
     * @tparam T template type
     * @param xPos x-position
     * @param yPos y-position
     */
    template<typename T>
    Vector2D<T>::Vector2D(T xPos, T yPos)
    {
        x = xPos;
        y = yPos;
    }

    template<typename T>
    bool Vector2D<T>::operator==(const Vector2D &rhs) const
    {
        return x == rhs.x &&
               y == rhs.y;
    }

    template<typename T>
    bool Vector2D<T>::operator!=(const Vector2D &rhs) const
    {
        return !(rhs == *this);
    }

    typedef Vector2D<int> Vector2Di;
    typedef Vector2D<float> Vector2Df;

} // dev

#endif //GAME_DEV_TEMPLATE_VECTOR2D_HPP
