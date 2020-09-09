#ifndef GLUTVIEWERSIMPLE_H
#define GLUTVIEWERSIMPLE_H

#include "Canvas2dViewerInterface.h"

#include "GL/freeglut.h"
#include <iostream>
#include <vector>

#include "ra_types.h"

template <typename T> // NOTE: where T is integral
static inline ra_types::displacement1i_t coords_to_index(
    T x, T y, ra_types::distance1ui_t w, ra_types::distance1ui_t h)
{
    if ((x < 0) || (y < 0))
        return 0; // cartesian Q1
    ra_types::displacement1i_t temp = x + y * w;
    if (ra_types::distance1ui_t(temp < h * w))
        return temp;
    else
        return 0;
}

// only GL_POINTS mode is used for drawing with opengl
// this approach shows how simple_drawing::algorithmes work

template <size_t width, size_t height, size_t display_size>
class visual_tests_glut_window
{
private:
    // lightwieght abstraction
    typedef ra_types::ImageRgb888Const<display_size> image;
    // storage of images for opengl window tests
    static std::vector<image>* image_registry;

public:
    static void run()
    {
        test_opengl_points_only();

        // never return from this
        glutMainLoop();
    }

    visual_tests_glut_window(int argc, char* argv[])
    {
        // one time init
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE);

        // storage of images for opengl window tests
        image_registry = new std::vector<image>();
    }

    ~visual_tests_glut_window() { delete image_registry; }

private:
    // callback for glut - vertical line
    static void display_test_v()
    {
        // clear buf
        glClear(GL_COLOR_BUFFER_BIT);

        /* this block is duplicated by some reason */
        glOrtho(0.0, width, 0.0, height, -1., 1.);
        glViewport(0, 0, width, height);

        //(-1,1)          (1,1)
        //        (0,0)
        //(-1,-1)         (1,-1)

        GLint step_y = height / 2;
        // GLint step_x = width / 2;

        GLint start   = 0;
        GLint finish  = height * 50 /*pix*/;
        GLint current = start;

        glBegin(GL_POINTS);
        {
            while (current < finish)
            {
                glColor3ub(255, 0, 0);            // red
                glVertex2i(50 * height, current); // mid

                current += step_y;
            }
        }
        glEnd();
        glFlush();
        glutSwapBuffers();
    }

    // callback for glut - horizontal line
    static void display_test_h()
    {
        // clear buf
        glClear(GL_COLOR_BUFFER_BIT);

        /* this block is duplicated by some reason */
        glOrtho(0.0, width, 0.0, height, -1., 1.);
        glViewport(0, 0, width, height);

        // GLint step_y = height / 2;
        GLint step_x = width / 2;

        GLint start   = 0;
        GLint finish  = width * 50 /*pix*/;
        GLint current = start;

        glBegin(GL_POINTS);
        {
            while (current < finish)
            {
                glColor3f(0.0, 1.0, 0.0);
                glVertex2i(current, 50 * width);

                current += step_x;
            }
        }
        glEnd();
        glFlush();
        glutSwapBuffers();
    }

    // glut produces windows
    static void test_window_line_vertical()
    {
        // get window 1
        GLint window1;
        glutInitWindowSize(width, height);
        glutInitWindowPosition(200, 250);

        auto window_title1 = "Vertical";
        window1            = glutCreateWindow(window_title1);

        /* this block is duplicated by some reason */
        glOrtho(0.0, width, 0.0, height, -1., 1.);
        glViewport(0, 0, width, height);

        glutDisplayFunc(display_test_v);

        glClearColor(1., 1., 1., 1.);
        std::cout << "Open window " << window1 << " for " << window_title1
                  << std::endl;
    }

    static void test_window_line_horizontal()
    {
        // get window 2 (yes, this is the reason)
        GLint window2;
        glutInitWindowSize(width, height);
        glutInitWindowPosition(500, 250);

        auto window_title2 = "HORIZONTAL";
        window2            = glutCreateWindow(window_title2);

        /* this block is duplicated by some reason */
        glOrtho(0.0, width, 0.0, height, -1., 1.);
        glViewport(0, 0, width, height);

        glutDisplayFunc(display_test_h);

        // glClearColor(1.0, 1.0, 1.0, 1.0);
        std::cout << "Open window " << window2 << " for " << window_title2
                  << std::endl;
    }

    // tests for pure glut

    static void test_opengl_points_only()
    {
        test_window_line_vertical();

        test_window_line_horizontal();
    }

    // callback for glut - draw images from canvas
    // NOTE: right now canvas coordinate system and window's one are different
    static void display_image()
    {
        static size_t number;
        image         img = image_registry->at(number++);

        GLint h = GLint(height);
        GLint w = GLint(width);

        // clear buf
        glClear(GL_COLOR_BUFFER_BIT);

        /* this block is duplicated by some reason */
        glOrtho(0.0, w, 0.0, h, -1., 1.);
        glViewport(0, 0, w, h);

        GLint step_y = h / 2;
        GLint step_x = w / 2;

        GLint current_y = 0;

        glBegin(GL_POINTS);
        {
            while (current_y < h)
            {
                GLint current_x = 0;
                while (current_x < w)
                {
                    auto i =
                        coords_to_index(current_x, current_y, width, height);
                    glColor3ub(img[i].r, img[i].g, img[i].b);

                    glVertex2i(current_x * step_x, current_y * step_y);
                    current_x += 1;
                }
                current_y += 1;
            }
        }
        glEnd();
        glFlush();
        glutSwapBuffers();
    }

    // produce window with glut for showing image
    template <size_t N>
    static void test_window_image(const char*                      title,
                                  std::array<ra_types::rgb888, N>& image)
    {
        // implicit static binding with ordered number of function call and
        // index in image registry
        image_registry->push_back(image);

        // get one more window (yes, this is the reason)
        GLint window;
        glutInitWindowSize(width, height);
        glutInitWindowPosition(500, 250);

        window = glutCreateWindow(title);

        /* this block is duplicated by some reason */
        glOrtho(0.0, width, 0.0, height, -1., 1.);
        glViewport(0, 0, width, height);

        // expects void(*)(), so we explictly use static registry of images
        glutDisplayFunc([]() -> void { display_image(); });

        // NOTE: commented line show artifacts borned by bad callback;
        // Right now, gl clear color is Black, and white color in canvas
        // is produced by canvas initialization with default ctor pixel()
        // which is simple_drawing::color::WHITE
        // glClearColor(1.0, 1.0, 1.0, 1.0);

        std::cout << "Open window " << window << " for " << title << std::endl;
    }
};

// static member of template class declaration
template <size_t width, size_t height, size_t display_size>
std::vector<
    typename visual_tests_glut_window<width, height, display_size>::image>*
    visual_tests_glut_window<width, height, display_size>::image_registry;

class GlutViewerSimple : public Canvas2dViewerInterface
{
public:
    GlutViewerSimple();

    void ViewResult(const ra_core::pipeline::Canvas2d& canvas,
                    const std::string_view description) const override;

    void glutMainLoop(int argc, char* argv[]);
};

#endif // GLUTVIEWERSIMPLE_H
