#pragma once

#include "Logger\Logger.h"

#include <QtWidgets\QWidget>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QLabel>
#include <QtWidgets\QHBoxLayout>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QPushButton>

#include "Header\QfeInspectorModelWidget.h"
#include "Header\QfeInspectorTransformWidget.h"
#include "Header\QfeInspectorLightWidget.h"
#include "Header\QfeInspectorCameraWidget.h"

namespace FrogEngine {
	namespace Object {
		class feObject;
	} //namespace Object
} //namespace FrogEngine

class QfeEditorTree;

class QfeEditorInspector : public QWidget
{
	Q_OBJECT
public:
	QfeEditorInspector(QWidget* parent);
	~QfeEditorInspector();

	QWidget* _verticalLayoutWidget;

	template <class T>
	T* AddWidget()
	{
		T* tmpWidget = GetUnUsedWidget<T>();
		if (tmpWidget != nullptr)
			return tmpWidget;

		std::size_t tHashCode = typeid(T).hash_code();
		if (tHashCode == typeid(QfeInspectorModelWidget).hash_code())
			return dynamic_cast<T*>(AddModelWidget());
		else if (tHashCode == typeid(QfeInspectorTransformWidget).hash_code())
			return dynamic_cast<T*>(AddtransformWidget());
		else if (tHashCode == typeid(QfeInspectorLightWidget).hash_code())
			return dynamic_cast<T*>(AddLightWidget());
		else if (tHashCode == typeid(QfeInspectorCameraWidget).hash_code())
			return dynamic_cast<T*>(AddCameraWidget());
		return nullptr;
	}

	template <class T>
	void RemoveWidget(T* widget)
	{
		std::size_t tHashCode = typeid(T).hash_code();
		if (tHashCode == typeid(QfeInspectorModelWidget).hash_code())
		{
			_verticalLayout->removeWidget(dynamic_cast<QfeInspectorModelWidget*>(widget->_mainVerticalLayoutWidget));
			dynamic_cast<QfeInspectorModelWidget*>(widget)->_useInInspector = false;
			dynamic_cast<QfeInspectorModelWidget*>(widget)->_mainVerticalLayoutWidget->close();
		}
		else if (tHashCode == typeid(QfeInspectorTransformWidget).hash_code())
		{
			_verticalLayout->removeWidget(dynamic_cast<QfeInspectorTransformWidget*>(widget->_mainVerticalLayoutWidget));
			dynamic_cast<QfeInspectorTransformWidget*>(widget)->_useInInspector = false;
			dynamic_cast<QfeInspectorTransformWidget*>(widget)->_mainVerticalLayoutWidget->close();
		}
		else if (tHashCode == typeid(QfeInspectorLightWidget).hash_code())
		{
			_verticalLayout->removeWidget(dynamic_cast<QfeInspectorLightWidget*>(widget->_mainVerticalLayoutWidget));
			dynamic_cast<QfeInspectorLightWidget*>(widget)->_useInInspector = false;
			dynamic_cast<QfeInspectorLightWidget*>(widget)->_mainVerticalLayoutWidget->close();
		}
		else if (tHashCode == typeid(QfeInspectorCameraWidget).hash_code())
		{
			_verticalLayout->removeWidget(dynamic_cast<QfeInspectorCameraWidget*>(widget->_mainVerticalLayoutWidget));
			dynamic_cast<QfeInspectorCameraWidget*>(widget)->_useInInspector = false;
			dynamic_cast<QfeInspectorCameraWidget*>(widget)->_mainVerticalLayoutWidget->close();
		}
	}

	void RemoveAllWidget();

	QVBoxLayout* _verticalLayout;
	QFrame* _frameFiller;
	void Resize(int width, int heigth);

	void resizeEvent(QResizeEvent* resizeEvent);
	void setEditorTree(QfeEditorTree*);

private:
	QHBoxLayout* _titleLayout = nullptr;
	QLabel* _inspectorName = nullptr;
	QHBoxLayout* _hAddWidgetLayout = nullptr;
	QComboBox* _addWidgetComboBox = nullptr;
	QPushButton* _addWidgetButton = nullptr;

	QfeEditorTree* _editorTree;

	std::vector<QfeInspectorModelWidget*> _modelWidgets;
	std::vector<QfeInspectorTransformWidget*> _transformWidgets;
	std::vector<QfeInspectorLightWidget*> _lightWidgets;
	std::vector<QfeInspectorCameraWidget*> _cameraWidgets;

	template<class T>
	T* GetUnUsedWidget()
	{
		unsigned int idx = 0;

		if (typeid(T).hash_code() == typeid(QfeInspectorModelWidget).hash_code())
		{
			for (; idx < _modelWidgets.size(); idx++)
				if (!_modelWidgets[idx]->_useInInspector)
				{
					_modelWidgets[idx]->_useInInspector = true;
					EmplaceWidgetInInspector<T>(dynamic_cast<T*>(_modelWidgets[idx]));
					return dynamic_cast<T*>(_modelWidgets[idx]);
				}
		}
		else if (typeid(T).hash_code() == typeid(QfeInspectorTransformWidget).hash_code())
		{
			for (; idx < _transformWidgets.size(); idx++)
				if (!_transformWidgets[idx]->_useInInspector)
				{
					_transformWidgets[idx]->_useInInspector = true;
					EmplaceWidgetInInspector<T>(dynamic_cast<T*>(_transformWidgets[idx]));
					return dynamic_cast<T*>(_transformWidgets[idx]);
				}
		}
		else if (typeid(T).hash_code() == typeid(QfeInspectorLightWidget).hash_code())
		{
			for (; idx < _lightWidgets.size(); idx++)
				if (!_lightWidgets[idx]->_useInInspector)
				{
					_lightWidgets[idx]->_useInInspector = true;
					EmplaceWidgetInInspector<T>(dynamic_cast<T*>(_lightWidgets[idx]));
					return dynamic_cast<T*>(_lightWidgets[idx]);
				}
		}
		else if (typeid(T).hash_code() == typeid(QfeInspectorCameraWidget).hash_code())
		{
			for (; idx < _cameraWidgets.size(); idx++)
				if (!_cameraWidgets[idx]->_useInInspector)
				{
					_cameraWidgets[idx]->_useInInspector = true;
					EmplaceWidgetInInspector<T>(dynamic_cast<T*>(_cameraWidgets[idx]));
					return dynamic_cast<T*>(_cameraWidgets[idx]);
				}
		}
		return nullptr;
	}

	QfeInspectorModelWidget* AddModelWidget();
	QfeInspectorTransformWidget* AddtransformWidget();
	QfeInspectorLightWidget* AddLightWidget();
	QfeInspectorCameraWidget* AddCameraWidget();


	template<class T>
	void EmplaceWidgetInInspector(T* widget)
	{
		_verticalLayout->removeItem(_hAddWidgetLayout);
		_verticalLayout->removeWidget(_frameFiller);

		if (typeid(T).hash_code() == typeid(QfeInspectorModelWidget).hash_code())
			_verticalLayout->addWidget(dynamic_cast<QfeInspectorModelWidget*>(widget)->_mainVerticalLayoutWidget);
		else if ((typeid(T).hash_code() == typeid(QfeInspectorTransformWidget).hash_code()))
			_verticalLayout->addWidget(dynamic_cast<QfeInspectorTransformWidget*>(widget)->_mainVerticalLayoutWidget);
		else if ((typeid(T).hash_code() == typeid(QfeInspectorLightWidget).hash_code()))
			_verticalLayout->addWidget(dynamic_cast<QfeInspectorLightWidget*>(widget)->_mainVerticalLayoutWidget);
		else if ((typeid(T).hash_code() == typeid(QfeInspectorCameraWidget).hash_code()))
			_verticalLayout->addWidget(dynamic_cast<QfeInspectorCameraWidget*>(widget)->_mainVerticalLayoutWidget);

		_verticalLayout->addLayout(_hAddWidgetLayout);
		_verticalLayout->addWidget(_frameFiller);
	}

	bool eventFilter(QObject* obj, QEvent* event);

	void AddComponent(FrogEngine::Object::feObject* obj, int componentIdx);
	private slots:
};