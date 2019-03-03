#pragma once

#include <QtWidgets\QDockWidget>
#include <QAction>


class QfeInspectorDock : public QDockWidget
{
	Q_OBJECT
public:
	QfeInspectorDock(QWidget* parent);
	~QfeInspectorDock();

	void SetupAction(QAction* action);

private:
	void closeEvent(QCloseEvent* event);
	QAction* _inspectorAction;
};
