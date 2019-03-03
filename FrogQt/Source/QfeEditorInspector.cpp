#include "Header\QfeEditorInspector.h"
#include "Header\QfeEditorTree.h"
#include "Core\System\feSceneManager.h"
#include "Core\System\feLightManager.h"

#include "Core\Object\feObject.h"

#include <QtWidgets/QPushButton>
#include <QResizeEvent>

QfeEditorInspector::QfeEditorInspector(QWidget* parent)
	: QWidget(parent)
{
	installEventFilter(this);

	std::vector<QfeInspectorModelWidget*> _modelWidgets = std::vector<QfeInspectorModelWidget*>();
	std::vector<QfeInspectorTransformWidget*>_transformWidgets = std::vector<QfeInspectorTransformWidget*>();

	_verticalLayoutWidget = new QWidget(this);
	_verticalLayoutWidget->setObjectName(QStringLiteral("Vertical Layout Widget"));
	_verticalLayoutWidget->setGeometry(QRect(0, 0, 301, 601));
	_verticalLayoutWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	_verticalLayout = new QVBoxLayout(_verticalLayoutWidget);
	_verticalLayout->setSpacing(6);
	_verticalLayout->setContentsMargins(11, 11, 11, 11);
	_verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	_verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
	_verticalLayout->setContentsMargins(0, 0, 0, 0);

	_hAddWidgetLayout = new QHBoxLayout(_verticalLayoutWidget);
	_hAddWidgetLayout->setSpacing(6);
	_hAddWidgetLayout->setContentsMargins(11, 11, 11, 11);
	_hAddWidgetLayout->setObjectName(QStringLiteral("_hAddWidgetLayout"));
	_hAddWidgetLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
	_hAddWidgetLayout->setContentsMargins(0, 0, 0, 0);

	_addWidgetComboBox = new QComboBox(this);
	_addWidgetComboBox->setObjectName(QStringLiteral("_addWidgetComboBox"));
	_addWidgetComboBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	_addWidgetComboBox->addItem("");
	_addWidgetComboBox->addItem("Directionnal Light Component");
	_addWidgetComboBox->addItem("Spot Light Component");
	_addWidgetComboBox->addItem("Camera Component");
	_addWidgetComboBox->addItem("Model Component");

	_addWidgetButton = new QPushButton(this);
	_addWidgetButton->setObjectName(QStringLiteral("_assWidgetButton"));
	_addWidgetButton->setText(QStringLiteral("AddComponent"));
	_addWidgetButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	_hAddWidgetLayout->addWidget(_addWidgetComboBox);
	_hAddWidgetLayout->addWidget(_addWidgetButton);
	_verticalLayout->addLayout(_hAddWidgetLayout);

	_frameFiller = new QFrame(this);
	_frameFiller->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	_verticalLayout->addWidget(_frameFiller);

	connect(_addWidgetButton, &QPushButton::pressed, this, [=]() {AddComponent(_editorTree->GetCurrentCoreObject(), _addWidgetComboBox->currentIndex()); });
}

QfeEditorInspector::~QfeEditorInspector()
{
	RemoveAllWidget();
	_modelWidgets.clear();
	_transformWidgets.clear();
	_lightWidgets.clear();
	_cameraWidgets.clear();

	_frameFiller->deleteLater();
	_frameFiller = nullptr;
	_addWidgetButton->deleteLater();
	_addWidgetButton = nullptr;
	_addWidgetComboBox->deleteLater();
	_addWidgetComboBox = nullptr;
	_hAddWidgetLayout->deleteLater();
	_hAddWidgetLayout = nullptr;
	_titleLayout->deleteLater();
	_titleLayout = nullptr;
	_verticalLayoutWidget->deleteLater();
	_verticalLayoutWidget = nullptr;
}

void QfeEditorInspector::setEditorTree(QfeEditorTree* editTree)
{
	_editorTree = editTree;
}

void QfeEditorInspector::AddComponent(FrogEngine::Object::feObject* obj, int componentIdx)
{
	if (obj == nullptr || componentIdx == 0)
	{ 
		_addWidgetComboBox->setCurrentIndex(0);
		return;
	}

	if (componentIdx == 1)
	{
		if (obj->GetComponent<FrogEngine::Component::Light::feDirectionalLight>())
			return;
		FrogEngine::Component::Light::feDirectionalLight* dirLight = new FrogEngine::Component::Light::feDirectionalLight();
		_editorTree->GetSceneMgr()->AddComponent(obj, dirLight);
		AddLightWidget()->SetupLight(dirLight, nullptr);
	}
	else if (componentIdx == 2)
	{
		if (obj->GetComponent<FrogEngine::Component::Light::feSpotLight>())
			return;
		FrogEngine::Component::Light::feSpotLight* spotLight = new FrogEngine::Component::Light::feSpotLight();
		_editorTree->GetSceneMgr()->AddComponent(obj, spotLight);
		AddLightWidget()->SetupLight(nullptr, spotLight);

	}
	else if (componentIdx == 3)
	{
		if (obj->GetComponent<FrogEngine::Component::Video::feCamera>())
			return;
		FrogEngine::Component::Video::feCamera* camComp = new FrogEngine::Component::Video::feCamera();
		obj->AddComponent(camComp);
		AddCameraWidget()->SetupCamera(camComp);
	}
	else if (componentIdx == 4)
	{
		if (obj->GetComponent<FrogEngine::Component::Mesh::feModel>())
			return;
		FrogEngine::Component::Mesh::feModel* modelComp = new FrogEngine::Component::Mesh::feModel();
		obj->AddComponent(modelComp);
		AddModelWidget()->SetDefaultValue(modelComp);
	}

	_addWidgetComboBox->setCurrentIndex(0);
}

QfeInspectorModelWidget * QfeEditorInspector::AddModelWidget()
{
	QfeInspectorModelWidget* widget = new QfeInspectorModelWidget(this);
	widget->_useInInspector = true;

	EmplaceWidgetInInspector<QfeInspectorModelWidget>(widget);

	_modelWidgets.push_back(widget);
	return widget;
}

QfeInspectorTransformWidget * QfeEditorInspector::AddtransformWidget()
{
	QfeInspectorTransformWidget* widget = new QfeInspectorTransformWidget(this);
	widget->_useInInspector = true;

	EmplaceWidgetInInspector<QfeInspectorTransformWidget>(widget);

	_transformWidgets.push_back(widget);
	return widget;
}

QfeInspectorLightWidget* QfeEditorInspector::AddLightWidget()
{
	QfeInspectorLightWidget* widget = new QfeInspectorLightWidget(this);
	widget->_useInInspector = true;

	EmplaceWidgetInInspector<QfeInspectorLightWidget>(widget);

	_lightWidgets.push_back(widget);
	return widget;
}

QfeInspectorCameraWidget* QfeEditorInspector::AddCameraWidget()
{
	QfeInspectorCameraWidget* widget = new QfeInspectorCameraWidget(this);
	widget->_useInInspector = true;

	EmplaceWidgetInInspector<QfeInspectorCameraWidget>(widget);

	_cameraWidgets.push_back(widget);
	return widget;
}

void QfeEditorInspector::RemoveAllWidget()
{
	unsigned int idx = 0;
	unsigned int end = _transformWidgets.size();
	
	for (; idx < end; idx++)
	{
		if (_transformWidgets[idx]->_useInInspector)
		{
			_verticalLayout->removeWidget(_transformWidgets[idx]->_mainVerticalLayoutWidget);
			_transformWidgets[idx]->_mainVerticalLayoutWidget->close();
		}
		_transformWidgets[idx]->_useInInspector = false;
	}

	idx = 0;
	end = _modelWidgets.size();

	for (; idx < end; idx++)
	{
		if (_modelWidgets[idx]->_useInInspector)
		{
			_verticalLayout->removeWidget(_modelWidgets[idx]->_mainVerticalLayoutWidget);
			_modelWidgets[idx]->_mainVerticalLayoutWidget->close();
		}
		_modelWidgets[idx]->_useInInspector = false;
	}

	idx = 0;
	end = _lightWidgets.size();

	for (; idx < end; idx++)
	{
		if (_lightWidgets[idx]->_useInInspector)
		{
			_verticalLayout->removeWidget(_lightWidgets[idx]->_mainVerticalLayoutWidget);
			_lightWidgets[idx]->_mainVerticalLayoutWidget->close();
		}
		_lightWidgets[idx]->_useInInspector = false;
	}

	idx = 0;
	end = _cameraWidgets.size();

	for (; idx < end; idx++)
	{
		if (_cameraWidgets[idx]->_useInInspector)
		{
			_verticalLayout->removeWidget(_cameraWidgets[idx]->_mainVerticalLayoutWidget);
			_cameraWidgets[idx]->_mainVerticalLayoutWidget->close();
		}
		_cameraWidgets[idx]->_useInInspector = false;
	}
}

void QfeEditorInspector::Resize(int _width, int _height)
{
	_verticalLayoutWidget->resize(_width, _height);
}

void QfeEditorInspector::resizeEvent(QResizeEvent* resizeEvent)
{
	Resize(width(), height());
}

bool QfeEditorInspector::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::Resize && obj == this)
	{
		QResizeEvent* resizeEvent = static_cast<QResizeEvent*>(event);
		QfeEditorInspector::resizeEvent(resizeEvent);
	}
	return QWidget::eventFilter(obj, event);
}