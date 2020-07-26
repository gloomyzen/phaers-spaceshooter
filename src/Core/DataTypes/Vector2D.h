#ifndef TOWERDEFENSE_GAME_VECTOR2D_H
#define TOWERDEFENSE_GAME_VECTOR2D_H

#include <iostream>

class Vector2D {
public:

  Vector2D();
  Vector2D(float x, float y);

  float getX() const { return x; };
  float getY() const { return y; };

  void setX(float _x) { x = _x; };
  void setY(float _y) { y = _y; };

  Vector2D& Add(const Vector2D& vec);
  Vector2D& Subtract(const Vector2D& vec);
  Vector2D& Multiply(const Vector2D& vec);
  Vector2D& Divide(const Vector2D& vec);
  Vector2D &Zero();

  friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
  friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
  friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
  friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

  Vector2D &operator+=(const Vector2D &vec);
  Vector2D &operator-=(const Vector2D &vec);
  Vector2D &operator*=(const Vector2D &vec);
  Vector2D &operator/=(const Vector2D &vec);

  Vector2D &operator*(const int &i);

  friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);

private:
  float x, y;
};


#endif// TOWERDEFENSE_GAME_VECTOR2D_H
