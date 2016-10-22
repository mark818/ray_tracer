#ifndef CAMERA
#define CAMERA
#include "vec3.h"
#include "ray.h"
#include "matrix3x3.h"
#include "string"

using namespace std;

class camera {
public:

  /*
    Phi and theta are in RADIANS.
  */
  void place(const vec3& targetPos, const double phi, const double theta,
             const double r, const double minR, const double maxR);

  string param_string() {
    return "";
  }

  void copy_placement(const camera& other);

  /*
    Updates the screen size to be the specified size, keeping screenDist
    constant.
  */
  void set_screen_size(const size_t screenW, const size_t screenH);

  /*
    Translates the camera such that a value at distance d directly in front of
    the camera moves by (dx, dy). Note that dx and dy are in screen coordinates,
    while d is in world-space coordinates (like pos/dir/up).
  */
  void move_by(const double dx, const double dy, const double d);

  /*
    Move the specified amount along the view axis.
  */
  void move_forward(const double dist);

  /*
    Rotate by the specified amount around the target.
  */
  void rotate_by(const double dPhi, const double dTheta);

  vec3 position() const { return pos; }
  vec3 view_point() const { return targetPos; }
  vec3 up_dir() const { return c2w[1]; }
  double near_clip() const { return nClip; }
  double far_clip() const { return fClip; }

  /**
   * Returns a world-space ray from the camera that corresponds to a
   * ray exiting the camera that deposits light at the sensor plane
   * position given by (x,y).  x and y are provided in the normalized
   * coordinate space of the sensor.  For example (0.5, 0.5)
   * corresponds to the middle of the screen.
   *
   * \param x x-coordinate of the ray sample in the view plane
   * \param y y-coordinate of the ray sample in the view plane
   */
  ray generate_ray(double x, double y) const;

 private:
  // Computes pos, screenXDir, screenYDir from target, r, phi, theta.
  void compute_position();

  // Field of view aspect ratio, clipping planes.
  double nClip, fClip;

  // Current position and target point (the point the camera is looking at).
  vec3 pos, targetPos;

  // Orientation relative to target, and min & max distance from the target.
  double phi, theta, r, minR, maxR;

  // camera-to-world rotation matrix (note: also need to translate a
  // camera-space point by 'pos' to perform a full camera-to-world
  // transform)
  matrix3x3 c2w;

  // Info about screen to render to; it corresponds to the camera's full field
  // of view at some distance.
  size_t screenW, screenH;
  double screenDist;


};
#endif
