#ifndef OPENGLDISPLAY_H
#define OPENGLDISPLAY_H

#include "zplayer_global.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QScopedPointer>
#include <QException>

class ZPLAYER_EXPORT OpenGLDisplay : public QOpenGLWidget, public QOpenGLFunctions
{
public:
    explicit OpenGLDisplay(QWidget* parent = nullptr);
    ~OpenGLDisplay();

    void InitDrawBuffer(unsigned bsize);
    void DisplayVideoFrame(unsigned char **yuv, uint16_t *line_size, int frameWidth, int frameHeight);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    struct OpenGLDisplayImpl;
    QScopedPointer<OpenGLDisplayImpl> impl;
};

/***********************************************************************/

class OpenGlException: public QException
{
public:
     void raise() const { throw *this; }
     OpenGlException *clone() const { return new OpenGlException(*this); }
};

#endif // OPENGLDISPLAY_H
