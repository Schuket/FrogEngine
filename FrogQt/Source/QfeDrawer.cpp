#include "Header\QfeDrawer.h"
#include "Core\System\feDevice.h"
#include "Core\System\feInputManager.h"
#include "Core\Object\feObject.h"
#include "Core\System\feSceneManager.h"
#include "Core\System\feScene.h"
#include "Core\Component\Video\feEditorCamera.h"
#include "Core\Component\Video\feCamera.h"
#include <QResizeEvent>

QfeDrawer::QfeDrawer(QWidget* parent, const QPoint& position, const QSize& size, int frameCout)
	:QSFMLCanvas(parent, position, size)
{
}

QfeDrawer::~QfeDrawer()
{
}

void QfeDrawer::InitDevice(FrogEngine::System::feDevice* newDevice)
{
	_device = newDevice;
	//_device->GetInputMgr()->SetWindow(this);
	editorCamera = _device->GetScnMgr()->GetEditorCamera()->GetComponent<FrogEngine::Component::Video::feEditorCamera>();
	editorCamera->SetFrustum(size().width(), size().height());
	_device->RunInit();
	_DrawerCreate = true;
}

void QfeDrawer::Resize(int width, int height)
{
	if (!_DrawerCreate)
		return;
	resize(width, height);
	if (editorCamera != nullptr && !_inSimulation)
		editorCamera->SetFrustum(width, height);
	if (_inGameCamera != nullptr && _inSimulation)
		_inGameCamera->SetFrustum(width, height);
}

void QfeDrawer::GetInGameCamera()
{
	if (_device->GetScnMgr()->GetCurrentScene()->GetMainCamera())
		_inGameCamera = _device->GetScnMgr()->GetCurrentScene()->GetMainCamera()->GetComponent<Component::Video::feCamera>();
	else
		_inGameCamera = nullptr;
}


void QfeDrawer::OnInit()
{
}

void QfeDrawer::OnUpdate()
{
	if (_device == nullptr)
		return;

	_device->Run();
}