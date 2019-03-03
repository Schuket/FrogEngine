#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QDoubleSpinBox>


namespace FrogEngine {
	namespace Object {
		class feTransform;
	} //namespace Object
} //namespace FrogEngine

class QfeEditorInspector;

class QfeInspectorTransformWidget : public QWidget
{
	Q_OBJECT
public:
	QfeInspectorTransformWidget(QfeEditorInspector* parent);
	~QfeInspectorTransformWidget();

	QWidget* _mainVerticalLayoutWidget = nullptr;

	void SetTransformValue(FrogEngine::Object::feTransform* ObjectTransform);

	bool _useInInspector = false;

	public slots:
private:
	void ClearLineEdit();
	void ConnectLineEdit();

	QLineEdit* _xPositionLineEdit = nullptr;
	QLineEdit* _yPositionLineEdit = nullptr;
	QLineEdit* _zPositionLineEdit = nullptr;
	QLineEdit* _xRotationLineEdit = nullptr;
	QLineEdit* _yRotationLineEdit = nullptr;
	QLineEdit* _zRotationLineEdit = nullptr;
	QLineEdit* _xScaleLineEdit = nullptr;
	QLineEdit* _yScaleLineEdit = nullptr;
	QLineEdit* _zScaleLineEdit = nullptr;

	QFrame* _positionFrameFiller = nullptr;
	QFrame* _rotationFrameFiller = nullptr;
	QFrame* _scaleFrameFiller = nullptr;

	QLabel* _xPositionLabel = nullptr;
	QLabel* _yPositionLabel = nullptr;
	QLabel* _zPositionLabel = nullptr;
	QLabel* _xRotationLabel = nullptr;
	QLabel* _yRotationLabel = nullptr;
	QLabel* _zRotationLabel = nullptr;
	QLabel* _xScaleLabel = nullptr;
	QLabel* _yScaleLabel = nullptr;
	QLabel* _zScaleLabel = nullptr;

	QLabel* _widgetTitleLabel = nullptr;
	QLabel* _subTitlePosition = nullptr;
	QLabel* _subTitleRotation = nullptr;
	QLabel* _subTitleScale = nullptr;
	
	QVBoxLayout* _mainVerticalLayout = nullptr;

	QHBoxLayout* _horizontalLayoutTitle = nullptr;
	QHBoxLayout* _horizontalLayoutSubTitlePosition = nullptr;
	QHBoxLayout* _horizontalLayoutSubTitleRotation = nullptr;
	QHBoxLayout* _horizontalLayoutSubTitleScale = nullptr;

	QHBoxLayout* _horizontalLayoutPosition = nullptr;
	QHBoxLayout* _horizontalLayoutRotation = nullptr;
	QHBoxLayout* _horizontalLayoutScale = nullptr;
	

	FrogEngine::Object::feTransform* _currentObjectTransform = nullptr;

	private slots:
};
