#pragma once

#include <QtWidgets\QLabel>
#include <QtWidgets\QLayout>
#include <QtWidgets\QSpinBox>
#include <QtWidgets\QFrame>

namespace FrogEngine {
	namespace Component {
		namespace Video {
			class feCamera;
		} // namespace Video
	} // namespace Component
} // namespace FrogEngine

class QfeEditorInspector;

class QfeInspectorCameraWidget : QWidget
{
	Q_OBJECT
public:
	QfeInspectorCameraWidget(QfeEditorInspector* parent);
	~QfeInspectorCameraWidget();

	QWidget* _mainVerticalLayoutWidget = nullptr;
	bool _useInInspector = false;

	void SetupCamera(FrogEngine::Component::Video::feCamera* camera);

private:
	QVBoxLayout* _vMainLayout = nullptr;

	QHBoxLayout* _hTitleLayout = nullptr;
	QHBoxLayout* _hFOVLayout = nullptr;
	QHBoxLayout* _hNearLayout = nullptr;
	QHBoxLayout* _hFarLayout = nullptr;

	QLabel* _TitleLabel = nullptr;
	QLabel* _FOVLabel = nullptr;
	QLabel* _NearLabel = nullptr;
	QLabel* _FarLabel = nullptr;

	QDoubleSpinBox* _FOVSpinBox = nullptr;
	QDoubleSpinBox* _NearSpinBox = nullptr;
	QDoubleSpinBox* _FarSpinBox = nullptr;
	
	FrogEngine::Component::Video::feCamera* _cam = nullptr;

	void ConnectWidget();
};