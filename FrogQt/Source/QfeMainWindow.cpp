#include "Header\QfeMainWindow.h"
#include "Header\QfeDrawer.h"
#include "Core\System\feDevice.h"
#include "Core\System\feSceneManager.h"
#include "Core\System\feResourceManager.h"
#include "Header\QfeEditorTree.h"
#include "Header\QfeEditorInspector.h"
#include <QResizeEvent>
#include <QDebug>

QfeMainWindow::~QfeMainWindow()
{
	delete _drawerWidget;
	_drawerWidget = nullptr;
	delete _editorTreeClass;
	_editorTreeClass = nullptr;
	delete ui.InspectorDock;
	ui.InspectorDock = nullptr;
	delete ui.RenderDock;
	ui.RenderDock = nullptr;
	delete ui.TreeViewDock;
	ui.TreeViewDock = nullptr;
	_device->Shutdown();
	delete _device;
}

QfeMainWindow::QfeMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_drawerWidget = new QfeDrawer(ui.RenderWidget, ui.RenderWidget->pos(), ui.RenderWidget->size());
	show();
	_drawerWidget->show();

	_device = FrogEngine::System::feDevice::Create();
	_device->SetDefaultParameters(reinterpret_cast<HWND>(_drawerWidget->GetWinID()));
	_device->SetHasOnSimulation(false);

	_drawerWidget->InitDevice(_device);
	
	ui.EngineTree->SetDefaultDependencies(_device->GetScnMgr(), ui.Inspector);
	_editorTreeClass = ui.EngineTree;
	ui.centralWidget->close();

	splitDockWidget(ui.InspectorDock, ui.TreeViewDock, Qt::Orientation::Horizontal);
	splitDockWidget(ui.InspectorDock, ui.RenderDock, Qt::Orientation::Horizontal);
	ResizeDockWidget();
	
	ui.actionInspector->setChecked(true);
	ui.actionTreeView->setChecked(true);
	ui.InspectorDock->SetupAction(ui.actionInspector);
	ui.TreeViewDock->SetupAction(ui.actionTreeView);

	connect(ui.actionStart, &QAction::triggered, this, [=]() {DisableEditor(); _device->StartSimulation(); _drawerWidget->_inSimulation = true; _drawerWidget->GetInGameCamera(); QfeMainWindow::resizeEvent(nullptr); });
	connect(ui.actionStop, &QAction::triggered, this, [=]() {EnableEditor(); _device->StopSimulation(); _drawerWidget->_inSimulation = false; QfeMainWindow::resizeEvent(nullptr); });
	
	connect(ui.actionInspector, &QAction::triggered, this, [=]() {ui.actionInspector->isChecked() ? ui.InspectorDock->show() : ui.InspectorDock->hide(); });
	connect(ui.actionTreeView, &QAction::triggered, this, [=]() {ui.actionTreeView->isChecked() ? ui.TreeViewDock->show() : ui.TreeViewDock->hide(); });

	connect(ui.actionAddEmptyObject, &QAction::triggered, this, [=]() {_device->GetScnMgr()->CreateObject(); _editorTreeClass->Refresh();});
	connect(ui.actionAddSphere, &QAction::triggered, this, [=]() {_device->GetScnMgr()->AddComponent(_device->GetScnMgr()->CreateObject(), _device->GetScnMgr()->GetRessourceLoader()->LoadModel("../Textures/sphere.obj")); _editorTreeClass->Refresh(); });
	connect(ui.actionAddCube, &QAction::triggered, this, [=]() {_device->GetScnMgr()->AddComponent(_device->GetScnMgr()->CreateObject(), _device->GetScnMgr()->GetRessourceLoader()->LoadModel("../Textures/Cube/Cube.obj")); _editorTreeClass->Refresh(); });

	ui.RenderDock->installEventFilter(this);
}

void QfeMainWindow::DisableEditor()
{
	ui.InspectorDock->setDisabled(true); 
	ui.TreeViewDock->setDisabled(true);

	ui.actionAddCube->setDisabled(true);
	ui.actionAddSphere->setDisabled(true);
	ui.actionAddEmptyObject->setDisabled(true);
}

void QfeMainWindow::EnableEditor()
{
	ui.InspectorDock->setDisabled(false);
	ui.TreeViewDock->setDisabled(false);

	ui.actionAddCube->setDisabled(false);
	ui.actionAddSphere->setDisabled(false);
	ui.actionAddEmptyObject->setDisabled(false);
}

void QfeMainWindow::resizeEvent(QResizeEvent * event)
{
	if (_drawerWidget)
		_drawerWidget->Resize(ui.RenderWidget->size().width(), ui.RenderWidget->size().height());
}

void QfeMainWindow::ResizeDockWidget()
{
	QList<QDockWidget*> h_dockList = { ui.RenderDock, ui.InspectorDock, ui.TreeViewDock };
	
	int windowWidth = width();
	int windowHeight = height();

	ui.RenderDock->setMinimumHeight(0.40 * windowHeight);
	ui.RenderDock->setMinimumWidth(0.40 * windowWidth);

	ui.InspectorDock->setMinimumWidth(0.10 * windowWidth);
	ui.InspectorDock->setMinimumHeight(0.5 * windowHeight);

	ui.TreeViewDock->setMinimumWidth(0.10 * windowWidth);
	ui.TreeViewDock->setMinimumHeight(0.5 * windowHeight);

	int h_render = 0.5 * windowWidth;
	int h_inspector = 0.25 * windowWidth;
	int h_treeView = 0.25 * windowWidth;


	QList<int> h_dockSize = { h_render, h_inspector, h_treeView };

	resizeDocks(h_dockList, h_dockSize, Qt::Orientation::Horizontal);
}

bool QfeMainWindow::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::Resize && obj == ui.RenderDock)
	{
		QResizeEvent* rEvent = static_cast<QResizeEvent*>(event);
		QfeMainWindow::resizeEvent(rEvent);
	}
	return QWidget::eventFilter(obj, event);
}