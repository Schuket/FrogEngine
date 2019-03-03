#include "Header\QSFMLCanvas.h"
#include <QWindow>

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif

QSFMLCanvas::QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, int frameCount)
	:QWidget(parent), myInitialized(false)
{
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);

	setFocusPolicy(Qt::ClickFocus);

	move(position);
	resize(size);

	windowID = winId();

	myTimer.setInterval(frameCount);
}

QSFMLCanvas::~QSFMLCanvas() {}

void QSFMLCanvas::showEvent(QShowEvent*)
{
	if (!myInitialized)
	{
		#ifdef Q_WS_X11
			XFlush(QX11Info::display());
		#endif

		//sf::ContextSettings windowContextSettings;
		//windowContextSettings.depthBits = 24;
		//windowContextSettings.stencilBits = 8;
		//windowContextSettings.antialiasingLevel = 2;
		//windowContextSettings.majorVersion = 4.5;
		//windowContextSettings.minorVersion = 0;
		//windowContextSettings.attributeFlags = sf::ContextSettings::Core;
		//sf::Window::create(reinterpret_cast<sf::WindowHandle>(winId()), windowContextSettings);
//		winId();
		OnInit();
		connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));

		myTimer.start();
		myInitialized = true;
	}
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
	return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
	OnUpdate();

	//SwapBuffers();
}