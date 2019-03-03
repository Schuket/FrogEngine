#include "Header\QfeInspectorLightWidget.h"
#include "Header\QfeEditorInspector.h"
#include "Header\QfeInspectorLightMaterialWidget.h"

#include "Core\Component\Light\feDirectionalLight.h"
#include "Core\Component\Light\feSpotLight.h"

QfeInspectorLightWidget::QfeInspectorLightWidget(QfeEditorInspector* parent)
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

	_mainTitleLabel = new QLabel(_mainVerticalLayoutWidget);
	_mainTitleLabel->setObjectName(QStringLiteral("_mainTitleLabel"));
	_mainTitleLabel->setText(QStringLiteral("Light:"));
	_mainTitleLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_mainTitleLabel->setFocusPolicy(tmpFocusPolicy);
	_mainTitleLabel->setAttribute(Qt::WA_DeleteOnClose);

	_hTitleLayout->addWidget(_mainTitleLabel);
	_vMainLayout->addLayout(_hTitleLayout);

	// ~~~~~~~~~~~~~ Direction Title ~~~~~~~~~~~~~ //

	_hDirectionTitleLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hDirectionTitleLayout->setSpacing(6);
	_hDirectionTitleLayout->setContentsMargins(11, 11, 11, 11);
	_hDirectionTitleLayout->setObjectName(QStringLiteral("_hDirectionTitleLayout"));
	_hDirectionTitleLayout->setSizeConstraint(QLayout::SetFixedSize);
	_hDirectionTitleLayout->setContentsMargins(0, 0, 0, 0);

	_directionLabel = new QLabel(_mainVerticalLayoutWidget);
	_directionLabel->setObjectName(QStringLiteral("_directionLabel"));
	_directionLabel->setText(QStringLiteral("Direction:"));
	_directionLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_directionLabel->setFocusPolicy(tmpFocusPolicy);
	_directionLabel->setAttribute(Qt::WA_DeleteOnClose);

	_hDirectionTitleLayout->addWidget(_directionLabel);
	_vMainLayout->addLayout(_hDirectionTitleLayout);

	// ~~~~~~~~~~~~~ Direction Data ~~~~~~~~~~~~~ //

	_hDirectionDataLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hDirectionDataLayout->setSpacing(6);
	_hDirectionDataLayout->setContentsMargins(11, 11, 11, 11);
	_hDirectionDataLayout->setObjectName(QStringLiteral("_hDirectionDataLayout"));
	_hDirectionDataLayout->setSizeConstraint(QLayout::SetFixedSize);
	_hDirectionDataLayout->setContentsMargins(0, 0, 0, 0);

	_directionXLabel = new QLabel(_mainVerticalLayoutWidget);
	_directionXLabel->setObjectName(QStringLiteral("_directionXLabel"));
	_directionXLabel->setText(QStringLiteral("X:"));
	_directionXLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_directionXLabel->setFocusPolicy(tmpFocusPolicy);
	_directionXLabel->setAttribute(Qt::WA_DeleteOnClose);

	_directionXLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_directionXLineEdit->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_directionXLineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	_directionXLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_directionYLabel = new QLabel(_mainVerticalLayoutWidget);
	_directionYLabel->setObjectName(QStringLiteral("_directionYLabel"));
	_directionYLabel->setText(QStringLiteral("Y:"));
	_directionYLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_directionYLabel->setFocusPolicy(tmpFocusPolicy);
	_directionYLabel->setAttribute(Qt::WA_DeleteOnClose);

	_directionYLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_directionYLineEdit->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_directionYLineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	_directionYLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_directionZLabel = new QLabel(_mainVerticalLayoutWidget);
	_directionZLabel->setObjectName(QStringLiteral("_directionZLabel"));
	_directionZLabel->setText(QStringLiteral("Z:"));
	_directionZLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_directionZLabel->setFocusPolicy(tmpFocusPolicy);
	_directionZLabel->setAttribute(Qt::WA_DeleteOnClose);

	_directionZLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_directionZLineEdit->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_directionZLineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	_directionZLineEdit->setAttribute(Qt::WA_DeleteOnClose);

	_frameFillerDirection = new QFrame(_mainVerticalLayoutWidget);
	_frameFillerDirection->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	_frameFillerDirection->setSizePolicy(tmpSizePolicyHorizontal, QSizePolicy::Preferred);
	_frameFillerDirection->setAttribute(Qt::WA_DeleteOnClose);

	_hDirectionDataLayout->addWidget(_directionXLabel);
	_hDirectionDataLayout->addWidget(_directionXLineEdit);

	_hDirectionDataLayout->addWidget(_directionYLabel);
	_hDirectionDataLayout->addWidget(_directionYLineEdit);

	_hDirectionDataLayout->addWidget(_directionZLabel);
	_hDirectionDataLayout->addWidget(_directionZLineEdit);

	_hDirectionDataLayout->addWidget(_frameFillerDirection);

	_vMainLayout->addLayout(_hDirectionDataLayout);

	// ~~~~~~~~~~~~~ FOV ~~~~~~~~~~~~~ //

	_hFOVLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_hFOVLayout->setSpacing(6);
	_hFOVLayout->setContentsMargins(11, 11, 11, 11);
	_hFOVLayout->setObjectName(QStringLiteral("_hFOVLayout"));
	_hFOVLayout->setSizeConstraint(QLayout::SetFixedSize);
	_hFOVLayout->setContentsMargins(0, 0, 0, 0);

	_fovLabel = new QLabel(_mainVerticalLayoutWidget);
	_fovLabel->setObjectName(QStringLiteral("_fovLabel"));
	_fovLabel->setText(QStringLiteral("FOV:"));
	_fovLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_fovLabel->setFocusPolicy(tmpFocusPolicy);

	_fovLineEdit = new QLineEdit(_mainVerticalLayoutWidget);
	_fovLineEdit->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_fovLineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

	_frameFillerFov = new QFrame(_mainVerticalLayoutWidget);
	_frameFillerFov->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	_frameFillerFov->setSizePolicy(tmpSizePolicyHorizontal, QSizePolicy::Preferred);

	_hFOVLayout->addWidget(_fovLabel);
	_hFOVLayout->addWidget(_fovLineEdit);
	_hFOVLayout->addWidget(_frameFillerFov);

	_vMainLayout->addLayout(_hFOVLayout);

	// ~~~~~~~~~~~~~ Light Material ~~~~~~~~~~~~~ //

	_lightMaterialWidget = new QfeInspectorLightMaterialWidget(this);
	_hFOVLayout->addWidget(_lightMaterialWidget->_mainVerticalLayoutWidget);

	_frameFiller = new QFrame(_mainVerticalLayoutWidget);
	_frameFiller->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	_hFOVLayout->addWidget(_frameFiller);
}

QfeInspectorLightWidget::~QfeInspectorLightWidget()
{
	_vMainLayout = nullptr;

	_hTitleLayout = nullptr;
	_hDirectionTitleLayout = nullptr;
	_hDirectionDataLayout = nullptr;
	_hFOVLayout = nullptr;

	_mainTitleLabel = nullptr;
	_directionLabel = nullptr;
	_directionXLabel = nullptr;
	_directionYLabel = nullptr;
	_directionZLabel = nullptr;
	_fovLabel = nullptr;

	_directionXLineEdit = nullptr;
	_directionYLineEdit = nullptr;
	_directionZLineEdit = nullptr;
	_fovLineEdit = nullptr;

	_frameFillerDirection = nullptr;
	_frameFillerFov = nullptr;
	_frameFiller = nullptr;

	_lightMaterialWidget = nullptr;
	_dirLight = nullptr;
	_spotLight = nullptr;
}

void QfeInspectorLightWidget::SetupLight(FrogEngine::Component::Light::feDirectionalLight* dir_light, FrogEngine::Component::Light::feSpotLight* spot_light)
{
	_dirLight = dir_light;
	_spotLight = spot_light;
	ConnectWidget();
}

void QfeInspectorLightWidget::ConnectWidget()
{
	if (_dirLight)
	{
		_directionXLineEdit->setText(QString::number(_dirLight->GetDirection().X()));
		_directionYLineEdit->setText(QString::number(_dirLight->GetDirection().Y()));
		_directionZLineEdit->setText(QString::number(_dirLight->GetDirection().Z()));

		connect(_directionXLineEdit, &QLineEdit::returnPressed, this, [=]() {_dirLight->SetDirection(Math::Vector3d(_directionXLineEdit->text().toFloat(), _dirLight->GetDirection().Y(), _dirLight->GetDirection().Z())); });
		connect(_directionYLineEdit, &QLineEdit::returnPressed, this, [=]() {_dirLight->SetDirection(Math::Vector3d(_dirLight->GetDirection().X(), _directionYLineEdit->text().toFloat(), _dirLight->GetDirection().Z())); });
		connect(_directionZLineEdit, &QLineEdit::returnPressed, this, [=]() {_dirLight->SetDirection(Math::Vector3d(_dirLight->GetDirection().X(), _dirLight->GetDirection().Y(), _directionZLineEdit->text().toFloat())); });
		_fovLineEdit->setDisabled(true);
		_lightMaterialWidget->SetupLightMaterial(&_dirLight->GetMaterial());
	}
	else if (_spotLight)
	{
		_directionXLineEdit->setText(QString::number(_spotLight->GetDirection().X()));
		_directionYLineEdit->setText(QString::number(_spotLight->GetDirection().Y()));
		_directionZLineEdit->setText(QString::number(_spotLight->GetDirection().Z()));
		_fovLineEdit->setText(QString::number(_spotLight->GetFov()));

		connect(_directionXLineEdit, &QLineEdit::returnPressed, this, [=]() {_spotLight->SetDirection(Math::Vector3d(_directionXLineEdit->text().toFloat(), _spotLight->GetDirection().Y(), _spotLight->GetDirection().Z())); });
		connect(_directionYLineEdit, &QLineEdit::returnPressed, this, [=]() {_spotLight->SetDirection(Math::Vector3d(_spotLight->GetDirection().X(), _directionYLineEdit->text().toFloat(), _spotLight->GetDirection().Z())); });
		connect(_directionZLineEdit, &QLineEdit::returnPressed, this, [=]() {_spotLight->SetDirection(Math::Vector3d(_spotLight->GetDirection().X(), _spotLight->GetDirection().Y(), _directionZLineEdit->text().toFloat())); });
		connect(_fovLineEdit, &QLineEdit::returnPressed, this, [=]() {_spotLight->SetFov(_fovLineEdit->text().toFloat()); });
		_lightMaterialWidget->SetupLightMaterial(&_spotLight->GetMaterial());
	}
}