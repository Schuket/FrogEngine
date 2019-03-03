#pragma once

#include <QtWidgets\QTreeWidget>

namespace FrogEngine {
	namespace System {
		class feSceneManager;
	} //namespace System
	namespace Object {
		class feObject;
	}//namespace Object
	namespace Component {
		class feComponent;
	} //namespace Component
} // namespace FrogEngine

class QfeEditorInspector;

class QfeEditorTree : public QTreeWidget
{
	Q_OBJECT
public:
	QfeEditorTree(QWidget* parent = Q_NULLPTR);
	~QfeEditorTree() = default;

	void SetDefaultDependencies(FrogEngine::System::feSceneManager* sceneManager, QfeEditorInspector* inspector);
	void Refresh();

	FrogEngine::Object::feObject* GetCurrentCoreObject();

	FrogEngine::System::feSceneManager* GetSceneMgr() { return _sceneManager; }

	public slots:
	void ShowItemInEditor();

private:
	void Init();
	void RemoveChild(FrogEngine::Object::feObject* child);
	void AddChilds(std::vector<FrogEngine::Object::feObject*> childList, QTreeWidgetItem* parent);
	void AddChild(FrogEngine::Object::feObject* child, QTreeWidgetItem* parent = nullptr);
	void AddComponents(std::vector<FrogEngine::Component::feComponent*> components, QTreeWidgetItem* parent = nullptr);
	void AddComponent(FrogEngine::Component::feComponent* component, QTreeWidgetItem* parent);
	FrogEngine::Object::feObject* GetObjectEngine(QTreeWidgetItem* item);
	void GetComponentToDisplay();

	FrogEngine::System::feSceneManager* _sceneManager;
	std::map<QTreeWidgetItem*, FrogEngine::Object::feObject*> _objectsMap;
	std::vector<FrogEngine::Object::feObject*> _objectsVector;
	QfeEditorInspector* _inspector;
	private slots:
};