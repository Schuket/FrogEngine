#pragma once

#include <QtWidgets\QDockWidget>
#include <QAction>

class QfeTreeViewDock : public QDockWidget
{
	Q_OBJECT
public:
	QfeTreeViewDock(QWidget* parent);
	~QfeTreeViewDock();

	void SetupAction(QAction* action);
private:
	void closeEvent(QCloseEvent* event);

	QAction* _treeViewAction;
};
