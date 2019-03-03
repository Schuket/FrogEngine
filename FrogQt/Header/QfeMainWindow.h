#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QfeMainWindow.h"

namespace FrogEngine {
	namespace System {
		class feDevice;
	} //namespace System
} //namesoace FrogEngine

class QfeEditorTree;
class QfeDrawer;

class QfeMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QfeMainWindow(QWidget *parent = Q_NULLPTR);
	~QfeMainWindow();
	void resizeEvent(QResizeEvent* event);
	
private:
	Ui::QfeMainWindowClass ui;
	QfeDrawer* _drawerWidget = nullptr;
	FrogEngine::System::feDevice* _device = nullptr;
	QfeEditorTree* _editorTreeClass;
	
	void DisableEditor();
	void EnableEditor();
	void ResizeDockWidget();
	bool eventFilter(QObject* obj, QEvent* event);
};
