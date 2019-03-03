#include "Header\QfeTreeViewDock.h"

QfeTreeViewDock::QfeTreeViewDock(QWidget* parent)
	: QDockWidget(parent)
{
}

QfeTreeViewDock::~QfeTreeViewDock()
{
}

void QfeTreeViewDock::SetupAction(QAction* action)
{
	_treeViewAction = action;
}

void QfeTreeViewDock::closeEvent(QCloseEvent* event)
{
	_treeViewAction->setChecked(false);
}