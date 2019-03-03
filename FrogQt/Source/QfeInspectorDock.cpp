#include "Header\QfeInspectorDock.h"

QfeInspectorDock::QfeInspectorDock(QWidget* parent)
	: QDockWidget(parent)
{
}

QfeInspectorDock::~QfeInspectorDock()
{
}

void QfeInspectorDock::SetupAction(QAction* action)
{
	_inspectorAction = action;
}

void QfeInspectorDock::closeEvent(QCloseEvent* event)
{
	qDebug("inspector close");
	_inspectorAction->setChecked(false);
}