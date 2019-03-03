#pragma once

#include <QtWidgets\QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>

namespace FrogEngine {
	namespace Component {
		namespace Mesh {
			class feModel;
		} //namespace Mesh
	} //namespace Component
} //namespace FrogEngine


class QfeEditorInspector;

class QfeInspectorModelWidget : public QWidget
{
	Q_OBJECT
public:
	QfeInspectorModelWidget(QfeEditorInspector* parent);
	~QfeInspectorModelWidget();

	QWidget* _mainVerticalLayoutWidget = nullptr;

	void SetDefaultValue(FrogEngine::Component::Mesh::feModel* model);

	bool _useInInspector = false;

	public slots:
private:
	void ConnectWidget();
	
	QLabel* _labelWidgetName = nullptr;
	QLabel* _labelWidgetModelName = nullptr;
	QLabel* _labelWidgetModelPath = nullptr;
	QLabel* _labelWidgetCenter = nullptr;
	QLabel* _labelWidgetRadius = nullptr;

	QLineEdit* _lineEditWidgetModelName = nullptr;
	QLineEdit* _lineEditWidgetModelPath = nullptr;
	QLineEdit* _lineEditWidgetCenterX = nullptr;
	QLineEdit* _lineEditWidgetCenterY = nullptr;
	QLineEdit* _lineEditWidgetCenterZ = nullptr;
	QLineEdit* _lineEditWidgetRadius = nullptr;

	QHBoxLayout* _hLayoutWidgetName = nullptr;
	QHBoxLayout* _hLayoutWidgetModelPath = nullptr;
	QHBoxLayout* _hLayoutWidgetModelName = nullptr;
	QHBoxLayout* _hLayoutWidgetCenter = nullptr;
	QHBoxLayout* _hLayoutWidgetRadius = nullptr;

	QVBoxLayout* _vLayoutMain = nullptr;

	FrogEngine::Component::Mesh::feModel* _model;

	private slots:
};