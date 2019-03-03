#pragma once

#include "GL\glew.h"
#include <QtWidgets\QWidget>
#include <QWindow>
#include <QTimer>
#include "SFML\Graphics.hpp"
#include "../WindowEvent/WindowEvent.h"

class QSFMLCanvas : public QWidget, public Window
{
public:
	QSFMLCanvas(QWidget* parent, const QPoint& position, const QSize& size, int frameCount = 0);
	virtual ~QSFMLCanvas();
	
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;

	virtual QPaintEngine* paintEngine() const;
	virtual void showEvent(QShowEvent*);
	virtual void paintEvent(QPaintEvent*);
	WId GetWinID() const { return windowID; }
private:

	WId windowID;
	QTimer myTimer;
	bool myInitialized;
};

