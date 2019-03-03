#include "Header\QfeInspectorModelWidget.h"
#include "Header\QfeEditorInspector.h"

#include "Core\Component\Mesh\feModel.h"

QfeInspectorModelWidget::QfeInspectorModelWidget(QfeEditorInspector* parent)
	: QWidget(parent)
{
	_mainVerticalLayoutWidget = new QWidget(parent->_verticalLayoutWidget);
	_mainVerticalLayoutWidget->setObjectName(QStringLiteral("_mainVerticalLayoutWidget"));
	_mainVerticalLayoutWidget->setGeometry(QRect(0, 0, 50, 50));
	_mainVerticalLayoutWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	_vLayoutMain = new QVBoxLayout(_mainVerticalLayoutWidget);
	_vLayoutMain->setSpacing(6);
	_vLayoutMain->setContentsMargins(11, 11, 11, 11);
	_vLayoutMain->setObjectName(QStringLiteral("mainVerticalLayout"));
	_vLayoutMain->setSizeConstraint(QLayout::SetDefaultConstraint);
	_vLayoutMain->setContentsMargins(0, 0, 0, 0);

	// ~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~ //

	auto tmpSizePolicyVertical = QSizePolicy::Fixed;
	auto tmpSizePolicyHorizontal = QSizePolicy::Fixed;
	auto tmpSizePolicyVerticalFrame = QSizePolicy::Preferred;
	auto tmpFocusPolicy = Qt::FocusPolicy::ClickFocus;

	// ~~~~~~~~~~~~~ Title ~~~~~~~~~~~~~ //

	_hLayoutWidgetName = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hLayoutWidgetName->setSpacing(6);
	_hLayoutWidgetName->setContentsMargins(11, 11, 11, 11);
	_hLayoutWidgetName->setObjectName(QStringLiteral("_horizontalLayoutTitle"));
	_hLayoutWidgetName->setSizeConstraint(QLayout::SetFixedSize);
	_hLayoutWidgetName->setContentsMargins(0, 0, 0, 0);

	_labelWidgetName = new QLabel(_mainVerticalLayoutWidget);
	_labelWidgetName->setObjectName(QStringLiteral("_labelWidgetName"));
	_labelWidgetName->setText(QStringLiteral("Model"));
	_labelWidgetName->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_labelWidgetName->setFocusPolicy(tmpFocusPolicy);
	_labelWidgetName->setAttribute(Qt::WA_DeleteOnClose);

	_hLayoutWidgetName->addWidget(_labelWidgetName);
	_vLayoutMain->addLayout(_hLayoutWidgetName);

	// ~~~~~~~~~~~~~ ModelName ~~~~~~~~~~~~~ //

	_hLayoutWidgetModelName = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hLayoutWidgetModelName->setSpacing(6);
	_hLayoutWidgetModelName->setContentsMargins(11, 11, 11, 11);
	_hLayoutWidgetModelName->setObjectName(QStringLiteral("_hLayoutWidgetModelName"));
	_hLayoutWidgetModelName->setSizeConstraint(QLayout::SetFixedSize);
	_hLayoutWidgetModelName->setContentsMargins(0, 0, 0, 0);

	_labelWidgetModelName = new QLabel(_mainVerticalLayoutWidget);
	_labelWidgetModelName->setObjectName(QStringLiteral("_labelWidgetModelName"));
	_labelWidgetModelName->setText(QStringLiteral("ModelName: "));
	_labelWidgetModelName->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_labelWidgetModelName->setFocusPolicy(tmpFocusPolicy);
	_labelWidgetModelName->setAttribute(Qt::WA_DeleteOnClose);

	_lineEditWidgetModelName = new QLineEdit(_mainVerticalLayoutWidget);
	_lineEditWidgetModelName->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_lineEditWidgetModelName->setFocusPolicy(tmpFocusPolicy);
	_lineEditWidgetModelName->setAttribute(Qt::WA_DeleteOnClose);

	_hLayoutWidgetModelName->addWidget(_labelWidgetModelName);
	_hLayoutWidgetModelName->addWidget(_lineEditWidgetModelName);
	_vLayoutMain->addLayout(_hLayoutWidgetModelName);

	// ~~~~~~~~~~~~~ ModelPath ~~~~~~~~~~~~~ //

	_hLayoutWidgetModelPath = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hLayoutWidgetModelPath->setSpacing(6);
	_hLayoutWidgetModelPath->setContentsMargins(11, 11, 11, 11);
	_hLayoutWidgetModelPath->setObjectName(QStringLiteral("_hLayoutWidgetModelPath"));
	_hLayoutWidgetModelPath->setSizeConstraint(QLayout::SetFixedSize);
	_hLayoutWidgetModelPath->setContentsMargins(0, 0, 0, 0);

	_labelWidgetModelPath = new QLabel(_mainVerticalLayoutWidget);
	_labelWidgetModelPath->setObjectName(QStringLiteral("_labelWidgetModelPath"));
	_labelWidgetModelPath->setText(QStringLiteral("ModelPath: "));
	_labelWidgetModelPath->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_labelWidgetModelPath->setFocusPolicy(tmpFocusPolicy);
	_labelWidgetModelPath->setAttribute(Qt::WA_DeleteOnClose);

	_lineEditWidgetModelPath = new QLineEdit(_mainVerticalLayoutWidget);
	_lineEditWidgetModelPath->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_lineEditWidgetModelPath->setFocusPolicy(tmpFocusPolicy);
	_lineEditWidgetModelPath->setReadOnly(true);
	_lineEditWidgetModelPath->setAttribute(Qt::WA_DeleteOnClose);

	_hLayoutWidgetModelPath->addWidget(_labelWidgetModelPath);
	_hLayoutWidgetModelPath->addWidget(_lineEditWidgetModelPath);
	_vLayoutMain->addLayout(_hLayoutWidgetModelPath);

	// ~~~~~~~~~~~~~ Center ~~~~~~~~~~~~~ //

	_hLayoutWidgetCenter = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hLayoutWidgetCenter->setSpacing(6);
	_hLayoutWidgetCenter->setContentsMargins(11, 11, 11, 11);
	_hLayoutWidgetCenter->setObjectName(QStringLiteral("_hLayoutWidgetCenter"));
	_hLayoutWidgetCenter->setSizeConstraint(QLayout::SetFixedSize);
	_hLayoutWidgetCenter->setContentsMargins(0, 0, 0, 0);

	_labelWidgetCenter = new QLabel(_mainVerticalLayoutWidget);
	_labelWidgetCenter->setObjectName(QStringLiteral("_labelWidgetCenter"));
	_labelWidgetCenter->setText(QStringLiteral("Center: "));
	_labelWidgetCenter->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_labelWidgetCenter->setFocusPolicy(tmpFocusPolicy);
	_labelWidgetCenter->setAttribute(Qt::WA_DeleteOnClose);

	_lineEditWidgetCenterX = new QLineEdit(_mainVerticalLayoutWidget);
	_lineEditWidgetCenterX->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_lineEditWidgetCenterX->setFocusPolicy(tmpFocusPolicy);
	_lineEditWidgetCenterX->setAttribute(Qt::WA_DeleteOnClose);

	_lineEditWidgetCenterY = new QLineEdit(_mainVerticalLayoutWidget);
	_lineEditWidgetCenterY->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_lineEditWidgetCenterY->setFocusPolicy(tmpFocusPolicy);
	_lineEditWidgetCenterY->setAttribute(Qt::WA_DeleteOnClose);

	_lineEditWidgetCenterZ = new QLineEdit(_mainVerticalLayoutWidget);
	_lineEditWidgetCenterZ->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_lineEditWidgetCenterZ->setFocusPolicy(tmpFocusPolicy);
	_lineEditWidgetCenterZ->setAttribute(Qt::WA_DeleteOnClose);

	_hLayoutWidgetCenter->addWidget(_labelWidgetCenter);
	_hLayoutWidgetCenter->addWidget(_lineEditWidgetCenterX);
	_hLayoutWidgetCenter->addWidget(_lineEditWidgetCenterY);
	_hLayoutWidgetCenter->addWidget(_lineEditWidgetCenterZ);
	_vLayoutMain->addLayout(_hLayoutWidgetCenter);

	// ~~~~~~~~~~~~~ Radius ~~~~~~~~~~~~~ //

	_hLayoutWidgetRadius = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hLayoutWidgetRadius->setSpacing(6);
	_hLayoutWidgetRadius->setContentsMargins(11, 11, 11, 11);
	_hLayoutWidgetRadius->setObjectName(QStringLiteral("_hLayoutWidgetRadius"));
	_hLayoutWidgetRadius->setSizeConstraint(QLayout::SetFixedSize);
	_hLayoutWidgetRadius->setContentsMargins(0, 0, 0, 0);

	_labelWidgetRadius = new QLabel(_mainVerticalLayoutWidget);
	_labelWidgetRadius->setObjectName(QStringLiteral("_labelWidgetRadius"));
	_labelWidgetRadius->setText(QStringLiteral("Radius: "));
	_labelWidgetRadius->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_labelWidgetRadius->setFocusPolicy(tmpFocusPolicy);
	_labelWidgetRadius->setAttribute(Qt::WA_DeleteOnClose);

	_lineEditWidgetRadius = new QLineEdit(_mainVerticalLayoutWidget);
	_lineEditWidgetRadius->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_lineEditWidgetRadius->setFocusPolicy(tmpFocusPolicy);
	_lineEditWidgetRadius->setAttribute(Qt::WA_DeleteOnClose);

	_hLayoutWidgetRadius->addWidget(_labelWidgetRadius);
	_hLayoutWidgetRadius->addWidget(_lineEditWidgetRadius);
	_vLayoutMain->addLayout(_hLayoutWidgetRadius);

	// ~~~~~~~~~~~~~ Connect ~~~~~~~~~~~~~ //

}

QfeInspectorModelWidget::~QfeInspectorModelWidget()
{
	_labelWidgetName = nullptr;
	_labelWidgetModelName = nullptr;
	_labelWidgetModelPath = nullptr;
	_labelWidgetCenter = nullptr;
	_labelWidgetRadius = nullptr;

	_lineEditWidgetModelName = nullptr;
	_lineEditWidgetModelPath = nullptr;
	_lineEditWidgetCenterX = nullptr;
	_lineEditWidgetCenterY = nullptr;
	_lineEditWidgetCenterZ = nullptr;
	_lineEditWidgetRadius = nullptr;

	_hLayoutWidgetName = nullptr;
	_hLayoutWidgetModelPath = nullptr;
	_hLayoutWidgetModelName = nullptr;
	_hLayoutWidgetCenter = nullptr;
	_hLayoutWidgetRadius = nullptr;

	_vLayoutMain = nullptr;

	_model = nullptr;
}

void QfeInspectorModelWidget::SetDefaultValue(FrogEngine::Component::Mesh::feModel* model)
{
	_model = model;

	_lineEditWidgetModelName->setText(QString::fromStdString(model->GetName()));
	_lineEditWidgetModelPath->setText(QString::fromStdString(model->GetPath()));

	Math::Vector3d center = model->GetCenter();
	_lineEditWidgetCenterX->setText(QString::number(center.X()));
	_lineEditWidgetCenterY->setText(QString::number(center.Y()));
	_lineEditWidgetCenterZ->setText(QString::number(center.Z()));

	_lineEditWidgetRadius->setText(QString::number(model->GetRadius()));

	ConnectWidget();
}

void QfeInspectorModelWidget::ConnectWidget()
{
	connect(_lineEditWidgetModelName, &QLineEdit::returnPressed, this, [=]() {_model->SetName(_lineEditWidgetModelName->text().toStdString());});

	connect(_lineEditWidgetCenterX, &QLineEdit::returnPressed, this, [=]() {_model->GetCenter().X(_lineEditWidgetCenterX->text().toFloat());});
	connect(_lineEditWidgetCenterY, &QLineEdit::returnPressed, this, [=]() {_model->GetCenter().X(_lineEditWidgetCenterY->text().toFloat());});
	connect(_lineEditWidgetCenterZ, &QLineEdit::returnPressed, this, [=]() {_model->GetCenter().X(_lineEditWidgetCenterZ->text().toFloat());});

	connect(_lineEditWidgetRadius, &QLineEdit::returnPressed, this, [=]() {_model->SetRadius(_lineEditWidgetRadius->text().toFloat());});
}