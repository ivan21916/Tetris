#pragma once

#include <SFML/System/Vector2.hpp>
#include <math.h>

namespace TetrisTT
{
  /**Multiplies two vectors component-wise*/
  template<typename T>
  sf::Vector2<T> vec2Mul(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
  {
    return sf::Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
  }

  /**Takes dot product of two vectors.*/
  template<typename T>
  T vec2Dot(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs)
  {
    return lhs.x* rhs.x + lhs.y * rhs.y;
  }

  /**Rotates point about its origin by angle radians.*/
  template<typename T>
  sf::Vector2<T> vec2Rot(const sf::Vector2<T>& point, double angle)
  {
    double cos_a = cos(angle);
    double sin_a = sin(angle);

    sf::Vector2<T> result;

    result.x = (T)(cos_a * point.x - sin_a * point.y);
    result.y = (T)(sin_a * point.x + cos_a * point.y);

    return result;
  }


}
