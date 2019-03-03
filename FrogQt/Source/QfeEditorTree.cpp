#include "Header\QfeEditorTree.h"
#include "Header\QfeEditorInspector.h"
#include "Header\QfeInspectorTransformWidget.h"
#include "Header\QfeInspectorModelWidget.h"
#include "Header\QfeInspectorLightWidget.h"

#include "Logger\Logger.h"

#include "Core\System\feSceneManager.h"
#include "Core\System\feScene.h"
#include "Core\Component\feComponent.h"
#include "Core\Object\feObject.h"

QfeEditorTree::QfeEditorTree(QWidget* parent)
	: QTreeWidget(parent)
{
	connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(ShowItemInEditor()));
}

void QfeEditorTree::SetDefaultDependencies(FrogEngine::System::feSceneManager* sceneManager, QfeEditorInspector* inspector)
{
	_sceneManager = sceneManager;
	_inspector = inspector;
	_inspector->setEditorTree(this);
	_objectsMap = std::map<QTreeWidgetItem*, FrogEngine::Object::feObject*>();
	_objectsVector = std::vector<FrogEngine::Object::feObject*>();

	Init();
}

void QfeEditorTree::Refresh()
{
	FrogEngine::Object::feObject* root = _sceneManager->GetCurrentScene()->GetRoot();
	std::vector<FrogEngine::Object::feObject*> rootChilds = root->GetChildren();
	int dif = _objectsVector.size() - rootChilds.size();
	if (dif < 0)
	{
		int current = _objectsVector.size();
		int end = rootChilds.size();
		for (; current < end; current++)
			AddChild(rootChilds[current]);
	}
	if (dif > 0)
	{
		int end = _objectsVector.size() - dif;
		for (int idx = 0; idx < end; idx++)
			RemoveChild(rootChilds[idx]);
	}
}

FrogEngine::Object::feObject * QfeEditorTree::GetCurrentCoreObject()
{
	return GetObjectEngine(currentItem());
}

void QfeEditorTree::Init()
{
	FrogEngine::Object::feObject* root = _sceneManager->GetCurrentScene()->GetRoot();
	headerItem()->setText(0, QString::fromStdString(root->GetName()));

	AddChilds(root->GetChildren(), nullptr);

}

void QfeEditorTree::RemoveChild(FrogEngine::Object::feObject* child)
{
	std::map<QTreeWidgetItem*, FrogEngine::Object::feObject*>::iterator it = _objectsMap.begin();

	for (; it != _objectsMap.end(); it++)
		if (it->second == child)
			_objectsMap.erase(it);

	std::vector<FrogEngine::Object::feObject*>::iterator itv = _objectsVector.begin();
	for (int i = 0; itv != _objectsVector.end(); itv++)
	{
		if (_objectsVector[i] == child)
			_objectsVector.erase(itv);
		i++;
	}
}

void QfeEditorTree::AddChilds(std::vector<FrogEngine::Object::feObject*> childList, QTreeWidgetItem* parent)
{
	std::size_t child_number = childList.size();

	for (std::size_t i = 0; i < child_number; i++)
	{
		AddChild(childList[i], parent);
	}
}

void QfeEditorTree::AddChild(FrogEngine::Object::feObject* child, QTreeWidgetItem* parent)
{
	QTreeWidgetItem* item = new QTreeWidgetItem();
	item->setText(0, QString::fromStdString(child->GetName()));
	if (parent)
		parent->addChild(item);
	else
		addTopLevelItem(item);

	_objectsMap.emplace(item, child);
	_objectsVector.push_back(child);
		//insert<QTreeWidgetItem*, FrogEngine::Object::feObject*>(item, child);

	//if (!child->GetComponent().empty())
	//	AddComponents(child->GetComponent(), item);

	if (!child->GetChildren().empty())
		AddChilds(child->GetChildren(), item);
}

void QfeEditorTree::AddComponents(std::vector<FrogEngine::Component::feComponent*> components, QTreeWidgetItem* parent)
{
	std::size_t componentsSize = components.size();
	for (std::size_t i = 0; i < componentsSize; i++)
	{
		AddComponent(components[i], parent);
	}
}

void QfeEditorTree::AddComponent(FrogEngine::Component::feComponent* component, QTreeWidgetItem* parent)
{
	QTreeWidgetItem* item = new QTreeWidgetItem();
	item->setText(0, QString::fromStdString(component->GetOwner()->GetName()));
	parent->addChild(item);
}

FrogEngine::Object::feObject* QfeEditorTree::GetObjectEngine(QTreeWidgetItem* item)
{
	return _objectsMap[item];
}

void QfeEditorTree::ShowItemInEditor()
{
	_inspector->RemoveAllWidget();

	QfeInspectorTransformWidget* transformWidget = _inspector->AddWidget<QfeInspectorTransformWidget>();
	transformWidget->SetTransformValue(&GetObjectEngine(currentItem())->GetTransform());
	transformWidget->_mainVerticalLayoutWidget->show();
	
	GetComponentToDisplay();
}

void QfeEditorTree::GetComponentToDisplay()
{
	FrogEngine::Object::feObject* object = GetObjectEngine(currentItem());
	std::map<std::size_t, FrogEngine::Component::feComponent*>components = object->GetComponent();
	std::map<std::size_t, FrogEngine::Component::feComponent*>::iterator it = components.begin();
	std::map<std::size_t, FrogEngine::Component::feComponent*>::iterator end = components.end();

	std::size_t modelHashCode = typeid(FrogEngine::Component::Mesh::feModel).hash_code();
	std::size_t dirLightHashCode = typeid(FrogEngine::Component::Light::feDirectionalLight).hash_code();
	std::size_t spotLightHashCode = typeid(FrogEngine::Component::Light::feSpotLight).hash_code();
	std::size_t cameraHashCode = typeid(FrogEngine::Component::Video::feCamera).hash_code();

	for (; it != end; it++)
	{
		if (it->first == modelHashCode)
		{
			QfeInspectorModelWidget* modelWidget = _inspector->AddWidget<QfeInspectorModelWidget>();
			modelWidget->SetDefaultValue(GetObjectEngine(currentItem())->GetComponent<FrogEngine::Component::Mesh::feModel>());
			modelWidget->_mainVerticalLayoutWidget->show();
		}
		if (it->first == dirLightHashCode || it->first == spotLightHashCode)
		{
			QfeInspectorLightWidget* lightWidget = _inspector->AddWidget<QfeInspectorLightWidget>();
			if (it->first == dirLightHashCode)
				lightWidget->SetupLight(GetObjectEngine(currentItem())->GetComponent<FrogEngine::Component::Light::feDirectionalLight>(), nullptr);
			else if(it->first == spotLightHashCode)
				lightWidget->SetupLight(nullptr, GetObjectEngine(currentItem())->GetComponent<FrogEngine::Component::Light::feSpotLight>());
			lightWidget->_mainVerticalLayoutWidget->show();
		}
		if (it->first == cameraHashCode)
		{
			QfeInspectorCameraWidget* cameraWidget = _inspector->AddWidget<QfeInspectorCameraWidget>();
			cameraWidget->SetupCamera(GetObjectEngine(currentItem())->GetComponent<FrogEngine::Component::Video::feCamera>());
			cameraWidget->_mainVerticalLayoutWidget->show();
		}
	}
}