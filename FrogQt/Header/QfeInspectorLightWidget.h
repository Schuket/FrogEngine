#pragma once

#include <QtWidgets\QSpinBox>
#include <QtWidgets\QLayout>
#include <QtWidgets\QLabel>
#include <QtWidgets\QFrame>

namespace FrogEngine {
	namespace Component {
		namespace Light {
			class feSpotLight;
			class feDirectionalLight;
		} // namespace Light
	} // namespace Component
} // namespace FrogEngine

class QfeEditorInspector;
class QfeInspectorLightMaterialWidget;

class QfeInspectorLightWidget : public QWidget
{
	Q_OBJECT
public:
	QfeInspectorLightWidget(QfeEditorInspector* parent);
	~QfeInspectorLightWidget();

	QWidget* _mainVerticalLayoutWidget = nullptr;
	void SetupLight(FrogEngine::Component::Light::feDirectionalLight* dir_light = nullptr, FrogEngine::Component::Light::feSpotLight* spot_light = nullptr);
	bool _useInInspector = false;

private:
	QVBoxLayout* _vMainLayout = nullptr;

	QHBoxLayout* _hTitleLayout = nullptr;
	QHBoxLayout* _hDirectionTitleLayout = nullptr;
	QHBoxLayout* _hDirectionDataLayout = nullptr;
	QHBoxLayout* _hFOVLayout = nullptr;

	QLabel* _mainTitleLabel = nullptr;
	QLabel* _directionLabel = nullptr;
	QLabel* _directionXLabel = nullptr;
	QLabel* _directionYLabel = nullptr;
	QLabel* _directionZLabel = nullptr;
	QLabel* _fovLabel = nullptr;

	QLineEdit* _directionXLineEdit = nullptr;
	QLineEdit* _directionYLineEdit = nullptr;
	QLineEdit* _directionZLineEdit = nullptr;
	QLineEdit* _fovLineEdit = nullptr;

	QFrame* _frameFillerDirection = nullptr;
	QFrame* _frameFillerFov = nullptr;
	QFrame* _frameFiller = nullptr;

	QfeInspectorLightMaterialWidget* _lightMaterialWidget;
	FrogEngine::Component::Light::feDirectionalLight* _dirLight = nullptr;
	FrogEngine::Component::Light::feSpotLight* _spotLight = nullptr;

	void ConnectWidget();
};