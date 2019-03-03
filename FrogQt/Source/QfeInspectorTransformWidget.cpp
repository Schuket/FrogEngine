#include "Header\QfeInspectorTransformWidget.h"
#include "Header\QfeEditorInspector.h"
#include "Core\Object\feTransform.h"

QfeInspectorTransformWidget::QfeInspectorTransformWidget(QfeEditorInspector* parent)
	: QWidget(parent)
{
	_mainVerticalLayoutWidget = new QWidget(parent->_verticalLayoutWidget);
	_mainVerticalLayoutWidget->setObjectName(QStringLiteral("_mainVerticalLayoutWidget"));
	_mainVerticalLayoutWidget->setGeometry(QRect(0, 0, 50, 50));
	// _mainVerticalLayoutWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	_mainVerticalLayoutWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	
	_mainVerticalLayout = new QVBoxLayout(_mainVerticalLayoutWidget);
	_mainVerticalLayout->setSpacing(6);
	_mainVerticalLayout->setContentsMargins(11, 11, 11, 11);
	_mainVerticalLayout->setObjectName(QStringLiteral("mainVerticalLayout"));
	_mainVerticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
	_mainVerticalLayout->setContentsMargins(0, 0, 0, 0);

	// ~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~ //

	auto tmpSizePolicyVertical = QSizePolicy::Fixed;
	auto tmpSizePolicyHorizontal = QSizePolicy::Expanding;
	auto tmpSizePolicyVerticalFrame = QSizePolicy::Preferred;
	auto tmpFocusPolicy = Qt::FocusPolicy::ClickFocus;

	// ~~~~~~~~~~~~~ Title ~~~~~~~~~~~~~ //

	_horizontalLayoutTitle = new QHBoxLayout(_mainVerticalLayoutWidget);
	_horizontalLayoutTitle->setSpacing(6);
	_horizontalLayoutTitle->setContentsMargins(11, 11, 11, 11);
	_horizontalLayoutTitle->setObjectName(QStringLiteral("_horizontalLayoutTitle"));
	_horizontalLayoutTitle->setSizeConstraint(QLayout::SetFixedSize);
	_horizontalLayoutTitle->setContentsMargins(0, 0, 0, 0);

	_widgetTitleLabel = new QLabel(_mainVerticalLayoutWidget);
	_widgetTitleLabel->setObjectName(QStringLiteral("_widgetTitleLabel"));
	_widgetTitleLabel->setText(QStringLiteral("Transform"));
	_widgetTitleLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_widgetTitleLabel->setFocusPolicy(tmpFocusPolicy);
	_widgetTitleLabel->setAttribute(Qt::WA_DeleteOnClose);
	

	_horizontalLayoutTitle->addWidget(_widgetTitleLabel);
	_mainVerticalLayout->addLayout(_horizontalLayoutTitle);

	// ~~~~~~~~~~~~~ Position SubTitle ~~~~~~~~~~~~~ //

	_horizontalLayoutSubTitlePosition = new QHBoxLayout(_mainVerticalLayoutWidget);
	_horizontalLayoutSubTitlePosition->setSpacing(6);
	_horizontalLayoutSubTitlePosition->setContentsMargins(11, 11, 11, 11);
	_horizontalLayoutSubTitlePosition->setObjectName(QStringLiteral("_horizontalLayoutSubTitlePosition"));
	_horizontalLayoutSubTitlePosition->setSizeConstraint(QLayout::SetFixedSize);
	_horizontalLayoutSubTitlePosition->setContentsMargins(0, 0, 0, 0);

	_subTitlePosition = new QLabel(_mainVerticalLayoutWidget);
	_subTitlePosition->setObjectName(QStringLiteral("_subTitlePosition"));
	_subTitlePosition->setText(QStringLiteral("Position"));
	_subTitlePosition->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_subTitlePosition->setFocusPolicy(tmpFocusPolicy);
	_subTitlePosition->setAttribute(Qt::WA_DeleteOnClose);

	_horizontalLayoutSubTitlePosition->addWidget(_subTitlePosition);
	_mainVerticalLayout->addLayout(_horizontalLayoutSubTitlePosition);

	// ~~~~~~~~~~~~~ Position Value ~~~~~~~~~~~~~ //

	_horizontalLayoutPosition = new QHBoxLayout(_mainVerticalLayoutWidget);
	_horizontalLayoutPosition->setSpacing(6);
	_horizontalLayoutPosition->setContentsMargins(11, 11, 11, 11);
	_horizontalLayoutPosition->setObjectName(QStringLiteral("_horizontalLayoutPosition"));
	_horizontalLayoutPosition->setSizeConstraint(QLayout::SetFixedSize);
	_horizontalLayoutPosition->setContentsMargins(0, 0, 0, 0);

	_xPositionLabel = new QLabel(_mainVerticalLayoutWidget);
	_xPositionLabel->setObjectName(QStringLiteral("_xPositionLabel"));
	_xPositionLabel->setText(QStringLiteral("X "));
	_xPositionLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_xPositionLabel->setFocusPolicy(tmpFocusPolicy);
	_xPositionLabel->setAttribute(Qt::WA_DeleteOnClose);

	_xPositionLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_xPositionLineEdit->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_xPositionLineEdit->setFocusPolicy(tmpFocusPolicy);
	_xPositionLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_yPositionLabel = new QLabel(_mainVerticalLayoutWidget);
	_yPositionLabel->setObjectName(QStringLiteral("_yPositionLabel"));
	_yPositionLabel->setText(QStringLiteral("Y "));
	_yPositionLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_yPositionLabel->setFocusPolicy(tmpFocusPolicy);
	_yPositionLabel->setAttribute(Qt::WA_DeleteOnClose);

	_yPositionLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_yPositionLineEdit->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_yPositionLineEdit->setFocusPolicy(tmpFocusPolicy);
	_yPositionLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_zPositionLabel = new QLabel(_mainVerticalLayoutWidget);
	_zPositionLabel->setObjectName(QStringLiteral("_zPositionLabel"));
	_zPositionLabel->setText(QStringLiteral("Z "));
	_zPositionLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_zPositionLabel->setFocusPolicy(tmpFocusPolicy);
	_zPositionLabel->setAttribute(Qt::WA_DeleteOnClose);

	_zPositionLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_zPositionLineEdit->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_zPositionLineEdit->setFocusPolicy(tmpFocusPolicy);
	_zPositionLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_positionFrameFiller = new QFrame(_mainVerticalLayoutWidget);
	_positionFrameFiller->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVerticalFrame);
	_positionFrameFiller->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	_positionFrameFiller->setAttribute(Qt::WA_DeleteOnClose);

	_horizontalLayoutPosition->addWidget(_xPositionLabel);
	_horizontalLayoutPosition->addWidget(_xPositionLineEdit);
	_horizontalLayoutPosition->addWidget(_yPositionLabel);
	_horizontalLayoutPosition->addWidget(_yPositionLineEdit);
	_horizontalLayoutPosition->addWidget(_zPositionLabel);
	_horizontalLayoutPosition->addWidget(_zPositionLineEdit);
	_horizontalLayoutPosition->addWidget(_positionFrameFiller);
	_mainVerticalLayout->addLayout(_horizontalLayoutPosition);

	// ~~~~~~~~~~~~~ Rotation SubTitle ~~~~~~~~~~~~~ //

	_horizontalLayoutSubTitleRotation = new QHBoxLayout(_mainVerticalLayoutWidget);
	_horizontalLayoutSubTitleRotation->setSpacing(6);
	_horizontalLayoutSubTitleRotation->setContentsMargins(11, 11, 11, 11);
	_horizontalLayoutSubTitleRotation->setObjectName(QStringLiteral("_horizontalLayoutSubTitleRotation"));
	_horizontalLayoutSubTitleRotation->setSizeConstraint(QLayout::SetFixedSize);
	_horizontalLayoutSubTitleRotation->setContentsMargins(0, 0, 0, 0);

	_subTitleRotation = new QLabel(_mainVerticalLayoutWidget);
	_subTitleRotation->setObjectName(QStringLiteral("_subTitleRotation"));
	_subTitleRotation->setText(QStringLiteral("Rotation"));
	_subTitleRotation->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_subTitleRotation->setFocusPolicy(tmpFocusPolicy);
	_subTitleRotation->setAttribute(Qt::WA_DeleteOnClose);

	_horizontalLayoutSubTitleRotation->addWidget(_subTitleRotation);
	_mainVerticalLayout->addLayout(_horizontalLayoutSubTitleRotation);

	// ~~~~~~~~~~~~~ Rotation Value ~~~~~~~~~~~~~ //

	_horizontalLayoutRotation = new QHBoxLayout(_mainVerticalLayoutWidget);
	_horizontalLayoutRotation->setSpacing(6);
	_horizontalLayoutRotation->setContentsMargins(11, 11, 11, 11);
	_horizontalLayoutRotation->setObjectName(QStringLiteral("_horizontalLayoutRotation"));
	_horizontalLayoutRotation->setSizeConstraint(QLayout::SetFixedSize);
	_horizontalLayoutRotation->setContentsMargins(0, 0, 0, 0);

	_xRotationLabel = new QLabel(_mainVerticalLayoutWidget);
	_xRotationLabel->setObjectName(QStringLiteral("_xRotationLabel"));
	_xRotationLabel->setText(QStringLiteral("X "));
	_xRotationLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_xRotationLabel->setFocusPolicy(tmpFocusPolicy);
	_xRotationLabel->setAttribute(Qt::WA_DeleteOnClose);

	_xRotationLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_xRotationLineEdit->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_xRotationLineEdit->setFocusPolicy(tmpFocusPolicy);
	_xRotationLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_yRotationLabel = new QLabel(_mainVerticalLayoutWidget);
	_yRotationLabel->setObjectName(QStringLiteral("_yRotationLabel"));
	_yRotationLabel->setText(QStringLiteral("Y "));
	_yRotationLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_yRotationLabel->setFocusPolicy(tmpFocusPolicy);
	_yRotationLabel->setAttribute(Qt::WA_DeleteOnClose);

	_yRotationLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_yRotationLineEdit->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_yRotationLineEdit->setFocusPolicy(tmpFocusPolicy);
	_yRotationLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_zRotationLabel = new QLabel(_mainVerticalLayoutWidget);
	_zRotationLabel->setObjectName(QStringLiteral("_zRotationLabel"));
	_zRotationLabel->setText(QStringLiteral("Z "));
	_zRotationLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_zRotationLabel->setFocusPolicy(tmpFocusPolicy);
	_zRotationLabel->setAttribute(Qt::WA_DeleteOnClose);

	_zRotationLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_zRotationLineEdit->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_zRotationLineEdit->setFocusPolicy(tmpFocusPolicy);
	_zRotationLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_rotationFrameFiller = new QFrame(_mainVerticalLayoutWidget);
	_rotationFrameFiller->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVerticalFrame);
	_rotationFrameFiller->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	_rotationFrameFiller->setAttribute(Qt::WA_DeleteOnClose);

	_horizontalLayoutRotation->addWidget(_xRotationLabel);
	_horizontalLayoutRotation->addWidget(_xRotationLineEdit);
	_horizontalLayoutRotation->addWidget(_yRotationLabel);
	_horizontalLayoutRotation->addWidget(_yRotationLineEdit);
	_horizontalLayoutRotation->addWidget(_zRotationLabel);
	_horizontalLayoutRotation->addWidget(_zRotationLineEdit);
	_horizontalLayoutRotation->addWidget(_rotationFrameFiller);
	_mainVerticalLayout->addLayout(_horizontalLayoutRotation);

	// ~~~~~~~~~~~~~ Scale SubTitle ~~~~~~~~~~~~~ //

	_horizontalLayoutSubTitleScale = new QHBoxLayout(_mainVerticalLayoutWidget);
	_horizontalLayoutSubTitleScale->setSpacing(6);
	_horizontalLayoutSubTitleScale->setContentsMargins(11, 11, 11, 11);
	_horizontalLayoutSubTitleScale->setObjectName(QStringLiteral("_horizontalLayoutSubTitleScale"));
	_horizontalLayoutSubTitleScale->setSizeConstraint(QLayout::SetFixedSize);
	_horizontalLayoutSubTitleScale->setContentsMargins(0, 0, 0, 0);

	_subTitleScale = new QLabel(_mainVerticalLayoutWidget);
	_subTitleScale->setObjectName(QStringLiteral("_subTitleScale"));
	_subTitleScale->setText(QStringLiteral("Scale"));
	_subTitleScale->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_subTitleScale->setFocusPolicy(tmpFocusPolicy);
	_subTitleScale->setAttribute(Qt::WA_DeleteOnClose);

	_horizontalLayoutSubTitleScale->addWidget(_subTitleScale);
	_mainVerticalLayout->addLayout(_horizontalLayoutSubTitleScale);

	// ~~~~~~~~~~~~~ Scale Value ~~~~~~~~~~~~~ //

	_horizontalLayoutScale = new QHBoxLayout(_mainVerticalLayoutWidget);
	_horizontalLayoutScale->setSpacing(6);
	_horizontalLayoutScale->setContentsMargins(11, 11, 11, 11);
	_horizontalLayoutScale->setObjectName(QStringLiteral("_horizontalLayoutScale"));
	_horizontalLayoutScale->setSizeConstraint(QLayout::SetFixedSize);
	_horizontalLayoutScale->setContentsMargins(0, 0, 0, 0);

	_xScaleLabel = new QLabel(_mainVerticalLayoutWidget);
	_xScaleLabel->setObjectName(QStringLiteral("_xScaleLabel"));
	_xScaleLabel->setText(QStringLiteral("X "));
	_xScaleLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_xScaleLabel->setFocusPolicy(tmpFocusPolicy);
	_xScaleLabel->setAttribute(Qt::WA_DeleteOnClose);
	  
	_xScaleLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_xScaleLineEdit->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_xScaleLineEdit->setFocusPolicy(tmpFocusPolicy);
	_xScaleLineEdit->setAttribute(Qt::WA_DeleteOnClose);
	  
	_yScaleLabel = new QLabel(_mainVerticalLayoutWidget);
	_yScaleLabel->setObjectName(QStringLiteral("_yScaleLabel"));
	_yScaleLabel->setText(QStringLiteral("Y "));
	_yScaleLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_yScaleLabel->setFocusPolicy(tmpFocusPolicy);
	_yScaleLabel->setAttribute(Qt::WA_DeleteOnClose);
	  
	_yScaleLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_yScaleLineEdit->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_yScaleLineEdit->setFocusPolicy(tmpFocusPolicy);
	_yScaleLineEdit->setAttribute(Qt::WA_DeleteOnClose);
	  
	_zScaleLabel = new QLabel(_mainVerticalLayoutWidget);
	_zScaleLabel->setObjectName(QStringLiteral("_zScaleLabel"));
	_zScaleLabel->setText(QStringLiteral("Z "));
	_zScaleLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_zScaleLabel->setFocusPolicy(tmpFocusPolicy);
	_zScaleLabel->setAttribute(Qt::WA_DeleteOnClose);
	  
	_zScaleLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_zScaleLineEdit->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_zScaleLineEdit->setFocusPolicy(tmpFocusPolicy);
	_zScaleLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_scaleFrameFiller = new QFrame(_mainVerticalLayoutWidget);
	_scaleFrameFiller->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVerticalFrame);
	_scaleFrameFiller->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	_scaleFrameFiller->setAttribute(Qt::WA_DeleteOnClose);

	_horizontalLayoutScale->addWidget(_xScaleLabel);
	_horizontalLayoutScale->addWidget(_xScaleLineEdit);
	_horizontalLayoutScale->addWidget(_yScaleLabel);
	_horizontalLayoutScale->addWidget(_yScaleLineEdit);
	_horizontalLayoutScale->addWidget(_zScaleLabel);
	_horizontalLayoutScale->addWidget(_zScaleLineEdit);
	_horizontalLayoutScale->addWidget(_scaleFrameFiller);
	_mainVerticalLayout->addLayout(_horizontalLayoutScale);

	//ConnectLineEdit();
}

QfeInspectorTransformWidget::~QfeInspectorTransformWidget()
{
	_widgetTitleLabel = nullptr;
	_horizontalLayoutTitle = nullptr;

	_subTitlePosition = nullptr;
	_horizontalLayoutSubTitlePosition = nullptr;

	_xPositionLabel = nullptr;
	_xPositionLineEdit = nullptr;
	_yPositionLabel = nullptr;
	_yPositionLineEdit = nullptr;
	_zPositionLabel = nullptr;
	_zPositionLineEdit = nullptr;
	_positionFrameFiller = nullptr;
	_horizontalLayoutPosition = nullptr;

	_subTitleRotation = nullptr;
	_horizontalLayoutSubTitleRotation = nullptr;

	_xRotationLabel = nullptr;
	_xRotationLineEdit = nullptr;
	_yRotationLabel = nullptr;
	_yRotationLineEdit = nullptr;
	_zRotationLabel = nullptr;
	_zRotationLineEdit = nullptr;
	_rotationFrameFiller = nullptr;
	_horizontalLayoutRotation = nullptr;
	
	_subTitleScale = nullptr;
	_horizontalLayoutSubTitleScale = nullptr;

	_xScaleLabel = nullptr;
	_xScaleLineEdit = nullptr;
	_yScaleLabel = nullptr;
	_yScaleLineEdit = nullptr;
	_zScaleLabel = nullptr;
	_zScaleLineEdit = nullptr;
	_scaleFrameFiller = nullptr;
	_horizontalLayoutScale = nullptr;

	_mainVerticalLayout = nullptr;
	_mainVerticalLayoutWidget = nullptr;

	_currentObjectTransform = nullptr;
}

void QfeInspectorTransformWidget::SetTransformValue(FrogEngine::Object::feTransform* ObjectTransform)
{
	_currentObjectTransform = ObjectTransform;
	ClearLineEdit();
	ConnectLineEdit();

	Math::Vector3d translation = ObjectTransform->GetTranslation();
	_xPositionLineEdit->insert(QString::number(translation.X()));
	_yPositionLineEdit->insert(QString::number(translation.Y()));
	_zPositionLineEdit->insert(QString::number(translation.Z()));
	
	Math::Vector3d rotation(0,0,0);
	_xRotationLineEdit->insert(QString::number(rotation.X()));
	_yRotationLineEdit->insert(QString::number(rotation.Y()));
	_zRotationLineEdit->insert(QString::number(rotation.Z()));

	Math::Vector3d scale = ObjectTransform->GetScale();
	_xScaleLineEdit->insert(QString::number(scale.X()));
	_yScaleLineEdit->insert(QString::number(scale.Y()));
	_zScaleLineEdit->insert(QString::number(scale.Z()));
}

void QfeInspectorTransformWidget::ClearLineEdit()
{
	_xPositionLineEdit->clear();
	_yPositionLineEdit->clear();
	_zPositionLineEdit->clear();

	_xRotationLineEdit->clear();
	_yRotationLineEdit->clear();
	_zRotationLineEdit->clear();

	_xScaleLineEdit->clear();
	_yScaleLineEdit->clear();
	_zScaleLineEdit->clear();
}

void QfeInspectorTransformWidget::ConnectLineEdit()
{
	connect(_xPositionLineEdit, &QLineEdit::returnPressed, this, [=]() {_currentObjectTransform->SetTranslation(Math::Vector3d(_xPositionLineEdit->text().toFloat(), _currentObjectTransform->GetTranslation().Y(), _currentObjectTransform->GetTranslation().Z()));});
	connect(_yPositionLineEdit, &QLineEdit::returnPressed, this, [=]() {_currentObjectTransform->SetTranslation(Math::Vector3d(_currentObjectTransform->GetTranslation().X(), _yPositionLineEdit->text().toFloat(), _currentObjectTransform->GetTranslation().Z()));});
	connect(_zPositionLineEdit, &QLineEdit::returnPressed, this, [=]() {_currentObjectTransform->SetTranslation(Math::Vector3d(_currentObjectTransform->GetTranslation().X(), _currentObjectTransform->GetTranslation().Y(), _zPositionLineEdit->text().toFloat()));});

	connect(_xRotationLineEdit, &QLineEdit::returnPressed, this, [=]() {_currentObjectTransform->RotateDeg(_xRotationLineEdit->text().toFloat(), 1, 0, 0);});
	connect(_yRotationLineEdit, &QLineEdit::returnPressed, this, [=]() {_currentObjectTransform->RotateDeg(_yRotationLineEdit->text().toFloat(), 0, 1, 0);});
	connect(_zRotationLineEdit, &QLineEdit::returnPressed, this, [=]() {_currentObjectTransform->RotateDeg(_zRotationLineEdit->text().toFloat(), 0, 0, 1);});

	connect(_xScaleLineEdit, &QLineEdit::returnPressed, this, [=]() {_currentObjectTransform->SetScale(Math::Vector3d(_xScaleLineEdit->text().toFloat(), _currentObjectTransform->GetScale().Y(), _currentObjectTransform->GetScale().Z())); });
	connect(_yScaleLineEdit, &QLineEdit::returnPressed, this, [=]() {_currentObjectTransform->SetScale(Math::Vector3d(_currentObjectTransform->GetScale().X(), _yScaleLineEdit->text().toFloat(), _currentObjectTransform->GetScale().Z())); });
	connect(_zScaleLineEdit, &QLineEdit::returnPressed, this, [=]() {_currentObjectTransform->SetScale(Math::Vector3d(_currentObjectTransform->GetScale().X(), _currentObjectTransform->GetScale().Y(), _zScaleLineEdit->text().toFloat())); });
}
