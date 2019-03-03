#pragma once

#include "QSFMLCanvas.h"

namespace FrogEngine {
	namespace System {
		class feDevice;
	} //namespace System

	namespace Component {
		namespace Video {
			class feEditorCamera;
			class feCamera;
		} //namespace Video
	}//namespace Component
} //namespace FrogEngine


class QfeDrawer : public QSFMLCanvas
{
	Q_OBJECT
public:
	QfeDrawer(QWidget* parent, const QPoint& position, const QSize& size, int frameCount = 0);
	~QfeDrawer();

	void InitDevice(FrogEngine::System::feDevice*);
	void Resize(int width, int height);

	void GetInGameCamera();
	bool _inSimulation = false;
private:
	void OnInit();
	void OnUpdate();
	FrogEngine::System::feDevice* _device = nullptr;
	FrogEngine::Component::Video::feEditorCamera* editorCamera = nullptr;
	FrogEngine::Component::Video::feCamera* _inGameCamera = nullptr;
	bool _DrawerCreate = false;
};