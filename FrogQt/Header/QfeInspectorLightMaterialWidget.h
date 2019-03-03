#pragma once

#include <QtWidgets\QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets\QSpinBox>

namespace FrogEngine {
	namespace Material {
		class feLightMaterial;
	} //namespace Component
} //namespace FrogEngine

class QfeInspectorLightWidget;

class QfeInspectorLightMaterialWidget : public QWidget
{
	Q_OBJECT
public:
	QfeInspectorLightMaterialWidget(QfeInspectorLightWidget* parent);
	~QfeInspectorLightMaterialWidget();

	QWidget* _mainVerticalLayoutWidget = nullptr;
	void SetupLightMaterial(FrogEngine::Material::feLightMaterial* lightMaterial);

private:
	QVBoxLayout* _VMainLayout = nullptr;
	
	QHBoxLayout* _HNameLayout = nullptr;
	QHBoxLayout* _HColorNameLayout = nullptr;
	QHBoxLayout* _HColorLayout = nullptr;
	QHBoxLayout* _HIntensityLayout = nullptr;
	QHBoxLayout* _HAmbiantLayout = nullptr;

	QLabel* _NameWidgetLabel = nullptr;
	QLabel* _ColorNameLabel = nullptr;
	QLabel* _ColorRLabel = nullptr;
	QLabel* _ColorGLabel = nullptr;
	QLabel* _ColorBLabel = nullptr;
	QLabel* _ColorALabel = nullptr;
	QLabel* _IntensityLabel = nullptr;
	QLabel* _AmbiantLabel = nullptr;

	QDoubleSpinBox* _ColorRSpinBox = nullptr;
	QDoubleSpinBox* _ColorGSpinBox = nullptr;
	QDoubleSpinBox* _ColorBSpinBox = nullptr;
	QDoubleSpinBox* _ColorASpinBox = nullptr;
	QDoubleSpinBox* _IntensitySpinBox = nullptr;
	QDoubleSpinBox* _AmbiantSpinBox = nullptr;

	QFrame* _ColorFrameFiller = nullptr;

	FrogEngine::Material::feLightMaterial* _lightMaterial;

	void ConnectWidget();
};
