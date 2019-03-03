#include "Header\QfeInspectorCameraWidget.h"
#include "Header\QfeEditorInspector.h"
#include "Core\Component\Video\feCamera.h"


QfeInspectorCameraWidget::QfeInspectorCameraWidget(QfeEditorInspector* parent)
	: QWidget(parent)
{
	_mainVerticalLayoutWidget = new QWidget(parent->_verticalLayoutWidget);
	_mainVerticalLayoutWidget->setObjectName(QStringLiteral("_mainVerticalLayoutWidget"));
	_mainVerticalLayoutWidget->setGeometry(QRect(0, 0, 50, 50));
	_mainVerticalLayoutWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	_vMainLayout = new QVBoxLayout(_mainVerticalLayoutWidget);
	_vMainLayout->setSpacing(6);
	_vMainLayout->setContentsMargins(11, 11, 11, 11);
	_vMainLayout->setObjectName(QStringLiteral("_vMainLayout"));
	_vMainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
	_vMainLayout->setContentsMargins(0, 0, 0, 0);

	// ~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~ //

	auto tmpSizePolicyVertical = QSizePolicy::Fixed;
	auto tmpSizePolicyHorizontal = QSizePolicy::Fixed;
	auto tmpSizePolicyVerticalFrame = QSizePolicy::Preferred;
	auto tmpFocusPolicy = Qt::FocusPolicy::ClickFocus;

	// ~~~~~~~~~~~~~ Title ~~~~~~~~~~~~~ //

	_hTitleLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hTitleLayout->setSpacing(6);
	_hTitleLayout->setContentsMargins(11, 11, 11, 11);
	_hTitleLayout->setObjectName(QStringLiteral("_hTitleLayout"));
	_hTitleLayout->setSizeConstraint(QLayout::SetFixedSize);
	_hTitleLayout->setContentsMargins(0, 0, 0, 0);

	_TitleLabel = new QLabel(_mainVerticalLayoutWidget);
	_TitleLabel->setObjectName(QStringLiteral("Title Label"));
	_TitleLabel->setText(QStringLiteral("Camera:"));
	_TitleLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_TitleLabel->setFocusPolicy(tmpFocusPolicy);

	_hTitleLayout->addWidget(_TitleLabel);
	_vMainLayout->addLayout(_hTitleLayout);

	// ~~~~~~~~~~~~~ FOV ~~~~~~~~~~~~~ //

	_hFOVLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hFOVLayout->setSpacing(6);
	_hFOVLayout->setContentsMargins(11, 11, 11, 11);
	_hFOVLayout->setObjectName(QStringLiteral("_hFOVLayout"));
	_hFOVLayout->setSizeConstraint(QLayout::SetFixedSize);
	_hFOVLayout->setContentsMargins(0, 0, 0, 0);

	_FOVLabel = new QLabel(_mainVerticalLayoutWidget);
	_FOVLabel->setObjectName(QStringLiteral("FOVLabel"));
	_FOVLabel->setText(QStringLiteral("FOV:"));
	_FOVLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_FOVLabel->setFocusPolicy(tmpFocusPolicy);

	_FOVSpinBox = new QDoubleSpinBox(_mainVerticalLayoutWidget);
	_FOVSpinBox->setObjectName(QStringLiteral("_FOVSpinBox"));
	_FOVSpinBox->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_FOVSpinBox->setMinimum(0);
	_FOVSpinBox->setMaximum(200);
	_FOVSpinBox->setKeyboardTracking(false);
	_FOVSpinBox->setDecimals(2);
	_FOVSpinBox->setSingleStep(0.1);

	_hFOVLayout->addWidget(_FOVLabel);
	_hFOVLayout->addWidget(_FOVSpinBox);
	_vMainLayout->addLayout(_hFOVLayout);

	// ~~~~~~~~~~~~~ Near ~~~~~~~~~~~~~ //

	_hNearLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hNearLayout->setSpacing(6);
	_hNearLayout->setContentsMargins(11, 11, 11, 11);
	_hNearLayout->setObjectName(QStringLiteral("_hNearLayout"));
	_hNearLayout->setSizeConstraint(QLayout::SetFixedSize);
	_hNearLayout->setContentsMargins(0, 0, 0, 0);

	_NearLabel = new QLabel(_mainVerticalLayoutWidget);
	_NearLabel->setObjectName(QStringLiteral("_NearLabel"));
	_NearLabel->setText(QStringLiteral("Near:"));
	_NearLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_NearLabel->setFocusPolicy(tmpFocusPolicy);

	_NearSpinBox = new QDoubleSpinBox(_mainVerticalLayoutWidget);
	_NearSpinBox->setObjectName(QStringLiteral("_NearSpinBox"));
	_NearSpinBox->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_NearSpinBox->setMinimum(0);
	_NearSpinBox->setMaximum(200);
	_NearSpinBox->setKeyboardTracking(false);
	_NearSpinBox->setDecimals(2);
	_NearSpinBox->setSingleStep(0.1);

	_hNearLayout->addWidget(_NearLabel);
	_hNearLayout->addWidget(_NearSpinBox);
	_vMainLayout->addLayout(_hNearLayout);

	// ~~~~~~~~~~~~~ Far ~~~~~~~~~~~~~ //

	_hFarLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hFarLayout->setSpacing(6);
	_hFarLayout->setContentsMargins(11, 11, 11, 11);
	_hFarLayout->setObjectName(QStringLiteral("_hFarLayout"));
	_hFarLayout->setSizeConstraint(QLayout::SetFixedSize);
	_hFarLayout->setContentsMargins(0, 0, 0, 0);

	_FarLabel = new QLabel(_mainVerticalLayoutWidget);
	_FarLabel->setObjectName(QStringLiteral("_FarLabel"));
	_FarLabel->setText(QStringLiteral("Far:"));
	_FarLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_FarLabel->setFocusPolicy(tmpFocusPolicy);

	_FarSpinBox = new QDoubleSpinBox(_mainVerticalLayoutWidget);
	_FarSpinBox->setObjectName(QStringLiteral("_FarSpinBox"));
	_FarSpinBox->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_FarSpinBox->setMinimum(0);
	_FarSpinBox->setMaximum(200);
	_FarSpinBox->setKeyboardTracking(false);
	_FarSpinBox->setDecimals(2);
	_FarSpinBox->setSingleStep(1);

	_hFarLayout->addWidget(_FarLabel);
	_hFarLayout->addWidget(_FarSpinBox);
	_vMainLayout->addLayout(_hFarLayout);
}

QfeInspectorCameraWidget::~QfeInspectorCameraWidget()
{
}

void QfeInspectorCameraWidget::SetupCamera(FrogEngine::Component::Video::feCamera* camera)
{
	_cam = camera;
	_FOVSpinBox->setValue(_cam->GetFov());
	_NearSpinBox->setValue(_cam->GetNear());
	_FarSpinBox->setValue(_cam->GetFar());
	ConnectWidget();
}

void QfeInspectorCameraWidget::ConnectWidget()
{
	connect(_FOVSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=](double d) {_cam->SetFOV(d); });
	connect(_NearSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=](double d) {_cam->SetNear(d); });
	connect(_FarSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=](double d) {_cam->SetFar(d); });
}