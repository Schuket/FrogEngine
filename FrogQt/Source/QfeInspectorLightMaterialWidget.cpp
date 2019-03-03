#include "Header\QfeInspectorLightMaterialWidget.h"
#include "Header\QfeInspectorLightWidget.h"
#include "Core\Component\Light\feLightMaterial.h"

QfeInspectorLightMaterialWidget::QfeInspectorLightMaterialWidget(QfeInspectorLightWidget* parent)
	: QWidget(parent)
{
	_mainVerticalLayoutWidget = new QWidget(parent->_mainVerticalLayoutWidget);
	_mainVerticalLayoutWidget->setObjectName(QStringLiteral("_mainVerticalLayoutWidget"));
	_mainVerticalLayoutWidget->setGeometry(QRect(0, 0, 50, 50));
	_mainVerticalLayoutWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	_VMainLayout = new QVBoxLayout(_mainVerticalLayoutWidget);
	_VMainLayout->setSpacing(6);
	_VMainLayout->setContentsMargins(11, 11, 11, 11);
	_VMainLayout->setObjectName(QStringLiteral("_VMainLayout"));
	_VMainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
	_VMainLayout->setContentsMargins(0, 0, 0, 0);

	// ~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~ //

	auto tmpSizePolicyVertical = QSizePolicy::Fixed;
	auto tmpSizePolicyHorizontal = QSizePolicy::Fixed;
	auto tmpSizePolicyVerticalFrame = QSizePolicy::Preferred;
	auto tmpFocusPolicy = Qt::FocusPolicy::ClickFocus;

	// ~~~~~~~~~~~~~ Title ~~~~~~~~~~~~~ //

	_HNameLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_HNameLayout->setSpacing(6);
	_HNameLayout->setContentsMargins(11, 11, 11, 11);
	_HNameLayout->setObjectName(QStringLiteral("_HNameLayout"));
	_HNameLayout->setSizeConstraint(QLayout::SetFixedSize);
	_HNameLayout->setContentsMargins(0, 0, 0, 0);

	_NameWidgetLabel = new QLabel(_mainVerticalLayoutWidget);
	_NameWidgetLabel->setObjectName(QStringLiteral("_NameWidgetLabel"));
	_NameWidgetLabel->setText(QStringLiteral("Light Material"));
	_NameWidgetLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_NameWidgetLabel->setFocusPolicy(tmpFocusPolicy);
	_NameWidgetLabel->setAttribute(Qt::WA_DeleteOnClose);

	_HNameLayout->addWidget(_NameWidgetLabel);
	_VMainLayout->addLayout(_HNameLayout);

	// ~~~~~~~~~~~~~ Color Title ~~~~~~~~~~~~~ //

	_HColorNameLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_HColorNameLayout->setSpacing(6);
	_HColorNameLayout->setContentsMargins(11, 11, 11, 11);
	_HColorNameLayout->setObjectName(QStringLiteral("_HColorNameLayout"));
	_HColorNameLayout->setSizeConstraint(QLayout::SetFixedSize);
	_HColorNameLayout->setContentsMargins(0, 0, 0, 0);

	_ColorNameLabel = new QLabel(_mainVerticalLayoutWidget);
	_ColorNameLabel->setObjectName(QStringLiteral("_ColorNameLabel"));
	_ColorNameLabel->setText(QStringLiteral("Color:"));
	_ColorNameLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_ColorNameLabel->setFocusPolicy(tmpFocusPolicy);
	_ColorNameLabel->setAttribute(Qt::WA_DeleteOnClose);

	_HColorNameLayout->addWidget(_ColorNameLabel);
	_VMainLayout->addLayout(_HColorNameLayout);

	// ~~~~~~~~~~~~~ Color Line Edit ~~~~~~~~~~~~~ //

	_HColorLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_HColorLayout->setSpacing(6);
	_HColorLayout->setContentsMargins(11, 11, 11, 11);
	_HColorLayout->setObjectName(QStringLiteral("_horizontalLayoutTitle"));
	_HColorLayout->setSizeConstraint(QLayout::SetFixedSize);
	_HColorLayout->setContentsMargins(0, 0, 0, 0);

	_ColorRLabel = new QLabel(_mainVerticalLayoutWidget);
	_ColorRLabel->setObjectName(QStringLiteral("_ColorRLabel"));
	_ColorRLabel->setText(QStringLiteral("R:"));
	_ColorRLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_ColorRLabel->setFocusPolicy(tmpFocusPolicy);
	_ColorRLabel->setAttribute(Qt::WA_DeleteOnClose);

	_ColorRSpinBox = new QDoubleSpinBox(_mainVerticalLayoutWidget);
	_ColorRSpinBox->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_ColorRSpinBox->setFocusPolicy(tmpFocusPolicy);
	_ColorRSpinBox->setMinimum(0);
	_ColorRSpinBox->setMaximum(1);
	_ColorRSpinBox->setDecimals(2);
	_ColorRSpinBox->setSingleStep(0.1);
	_ColorRSpinBox->setKeyboardTracking(false);
	_ColorRSpinBox->setAccelerated(false);
	_ColorRSpinBox->setAttribute(Qt::WA_DeleteOnClose);

	_ColorGLabel = new QLabel(_mainVerticalLayoutWidget);
	_ColorGLabel->setObjectName(QStringLiteral("_ColorGLabel"));
	_ColorGLabel->setText(QStringLiteral("G:"));
	_ColorGLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_ColorGLabel->setFocusPolicy(tmpFocusPolicy);
	_ColorGLabel->setAttribute(Qt::WA_DeleteOnClose);

	_ColorGSpinBox = new QDoubleSpinBox(_mainVerticalLayoutWidget);
	_ColorGSpinBox->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_ColorGSpinBox->setFocusPolicy(tmpFocusPolicy);
	_ColorGSpinBox->setMinimum(0);
	_ColorGSpinBox->setMaximum(1);
	_ColorGSpinBox->setDecimals(2);
	_ColorGSpinBox->setSingleStep(0.1);
	_ColorGSpinBox->setKeyboardTracking(false);
	_ColorGSpinBox->setAccelerated(false);
	_ColorGSpinBox->setAttribute(Qt::WA_DeleteOnClose);

	_ColorBLabel = new QLabel(_mainVerticalLayoutWidget);
	_ColorBLabel->setObjectName(QStringLiteral("_ColorBLabel"));
	_ColorBLabel->setText(QStringLiteral("B:"));
	_ColorBLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_ColorBLabel->setFocusPolicy(tmpFocusPolicy);
	_ColorBLabel->setAttribute(Qt::WA_DeleteOnClose);

	_ColorBSpinBox = new QDoubleSpinBox(_mainVerticalLayoutWidget);
	_ColorBSpinBox->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_ColorBSpinBox->setFocusPolicy(tmpFocusPolicy);
	_ColorBSpinBox->setMinimum(0);
	_ColorBSpinBox->setMaximum(1);
	_ColorBSpinBox->setDecimals(2);
	_ColorBSpinBox->setSingleStep(0.1);
	_ColorBSpinBox->setKeyboardTracking(false);
	_ColorBSpinBox->setAccelerated(false);
	_ColorBSpinBox->setAttribute(Qt::WA_DeleteOnClose);

	_ColorALabel = new QLabel(_mainVerticalLayoutWidget);
	_ColorALabel->setObjectName(QStringLiteral("_ColorALabel"));
	_ColorALabel->setText(QStringLiteral("A:"));
	_ColorALabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_ColorALabel->setFocusPolicy(tmpFocusPolicy);
	_ColorALabel->setAttribute(Qt::WA_DeleteOnClose);

	_ColorASpinBox = new QDoubleSpinBox(_mainVerticalLayoutWidget);
	_ColorASpinBox->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_ColorASpinBox->setFocusPolicy(tmpFocusPolicy);
	_ColorASpinBox->setMinimum(0);
	_ColorASpinBox->setMaximum(1);
	_ColorASpinBox->setDecimals(2);
	_ColorASpinBox->setSingleStep(0.1);
	_ColorASpinBox->setKeyboardTracking(false);
	_ColorASpinBox->setAccelerated(false);
	_ColorASpinBox->setAttribute(Qt::WA_DeleteOnClose);
	
	_ColorFrameFiller = new QFrame(_mainVerticalLayoutWidget);
	_ColorFrameFiller->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVerticalFrame);
	_ColorFrameFiller->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	_ColorFrameFiller->setAttribute(Qt::WA_DeleteOnClose);

	_HColorLayout->addWidget(_ColorRLabel);
	_HColorLayout->addWidget(_ColorRSpinBox);

	_HColorLayout->addWidget(_ColorGLabel);
	_HColorLayout->addWidget(_ColorGSpinBox);

	_HColorLayout->addWidget(_ColorBLabel);
	_HColorLayout->addWidget(_ColorBSpinBox);

	_HColorLayout->addWidget(_ColorALabel);
	_HColorLayout->addWidget(_ColorASpinBox);

	_HColorLayout->addWidget(_ColorFrameFiller);

	_VMainLayout->addLayout(_HColorLayout);

	// ~~~~~~~~~~~~~ Intensity ~~~~~~~~~~~~~ //

	_HIntensityLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_HIntensityLayout->setSpacing(6);
	_HIntensityLayout->setContentsMargins(11, 11, 11, 11);
	_HIntensityLayout->setObjectName(QStringLiteral("_HIntensityLayout"));
	_HIntensityLayout->setSizeConstraint(QLayout::SetFixedSize);
	_HIntensityLayout->setContentsMargins(0, 0, 0, 0);

	_IntensityLabel = new QLabel(_mainVerticalLayoutWidget);
	_IntensityLabel->setObjectName(QStringLiteral("IntensityLabel"));
	_IntensityLabel->setText(QStringLiteral("intensity:"));
	_IntensityLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_IntensityLabel->setFocusPolicy(tmpFocusPolicy);
	_IntensityLabel->setAttribute(Qt::WA_DeleteOnClose);

	_IntensitySpinBox = new QDoubleSpinBox(_mainVerticalLayoutWidget);
	_IntensitySpinBox->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_IntensitySpinBox->setFocusPolicy(tmpFocusPolicy);
	_IntensitySpinBox->setMinimum(0);
	_IntensitySpinBox->setMaximum(1000);
	_IntensitySpinBox->setDecimals(2);
	_IntensitySpinBox->setSingleStep(1);
	_IntensitySpinBox->setKeyboardTracking(false);
	_IntensitySpinBox->setAccelerated(false);
	_IntensitySpinBox->setAttribute(Qt::WA_DeleteOnClose);

	_HIntensityLayout->addWidget(_IntensityLabel);
	_HIntensityLayout->addWidget(_IntensitySpinBox);
	_VMainLayout->addLayout(_HIntensityLayout);

	// ~~~~~~~~~~~~~ Ambiant ~~~~~~~~~~~~~ //

	_HAmbiantLayout = new QHBoxLayout(_mainVerticalLayoutWidget);
	_HAmbiantLayout->setSpacing(6);
	_HAmbiantLayout->setContentsMargins(11, 11, 11, 11);
	_HAmbiantLayout->setObjectName(QStringLiteral("_HIntensityLayout"));
	_HAmbiantLayout->setSizeConstraint(QLayout::SetFixedSize);
	_HAmbiantLayout->setContentsMargins(0, 0, 0, 0);

	_AmbiantLabel = new QLabel(_mainVerticalLayoutWidget);
	_AmbiantLabel->setObjectName(QStringLiteral("_AmbiantLabel"));
	_AmbiantLabel->setText(QStringLiteral("Ambiant:"));
	_AmbiantLabel->setSizePolicy(tmpSizePolicyHorizontal, tmpSizePolicyVertical);
	_AmbiantLabel->setFocusPolicy(tmpFocusPolicy);
	_IntensitySpinBox->setAttribute(Qt::WA_DeleteOnClose);

	_AmbiantSpinBox = new QDoubleSpinBox(_mainVerticalLayoutWidget);
	_AmbiantSpinBox->setSizePolicy(QSizePolicy::Preferred, tmpSizePolicyVertical);
	_AmbiantSpinBox->setFocusPolicy(tmpFocusPolicy);
	_AmbiantSpinBox->setMinimum(0);
	_AmbiantSpinBox->setMaximum(1000);
	_AmbiantSpinBox->setDecimals(2);
	_AmbiantSpinBox->setSingleStep(1);
	_AmbiantSpinBox->setKeyboardTracking(false);
	_AmbiantSpinBox->setAccelerated(false);
	_AmbiantSpinBox->setAttribute(Qt::WA_DeleteOnClose);

	_HAmbiantLayout->addWidget(_AmbiantLabel);
	_HAmbiantLayout->addWidget(_AmbiantSpinBox);
	_VMainLayout->addLayout(_HAmbiantLayout);
}

QfeInspectorLightMaterialWidget::~QfeInspectorLightMaterialWidget()
{
	_VMainLayout = nullptr;

	_HNameLayout = nullptr;
	_HColorNameLayout = nullptr;
	_HColorLayout = nullptr;
	_HIntensityLayout = nullptr;
	_HAmbiantLayout = nullptr;

	_NameWidgetLabel = nullptr;
	_ColorNameLabel = nullptr;
	_ColorRLabel = nullptr;
	_ColorGLabel = nullptr;
	_ColorBLabel = nullptr;
	_ColorALabel = nullptr;
	_IntensityLabel = nullptr;
	_AmbiantLabel = nullptr;

	_ColorRSpinBox = nullptr;
	_ColorGSpinBox = nullptr;
	_ColorBSpinBox = nullptr;
	_ColorASpinBox = nullptr;
	_IntensitySpinBox = nullptr;
	_AmbiantSpinBox = nullptr;

	_ColorFrameFiller = nullptr;

	_lightMaterial = nullptr;
}

void QfeInspectorLightMaterialWidget::SetupLightMaterial(FrogEngine::Material::feLightMaterial* lightMaterial)
{
	_lightMaterial = lightMaterial;
	_ColorRSpinBox->setValue(_lightMaterial->GetColor().X());
	_ColorGSpinBox->setValue(_lightMaterial->GetColor().Y());
	_ColorBSpinBox->setValue(_lightMaterial->GetColor().Z());
	_ColorASpinBox->setValue(_lightMaterial->GetColor().W());

	_IntensitySpinBox->setValue(_lightMaterial->GetIntensity());
	_AmbiantSpinBox->setValue(_lightMaterial->GetAmbiant());

	ConnectWidget();
}

void QfeInspectorLightMaterialWidget::ConnectWidget()
{
	connect(_ColorRSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=](double d) {_lightMaterial->SetColor(Math::Vector4d(d, _lightMaterial->GetColor().Y(), _lightMaterial->GetColor().Z(), _lightMaterial->GetColor().W())); });
	connect(_ColorGSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=](double d) {_lightMaterial->SetColor(Math::Vector4d(_lightMaterial->GetColor().X(), d, _lightMaterial->GetColor().Z(), _lightMaterial->GetColor().W())); });
	connect(_ColorBSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=](double d) {_lightMaterial->SetColor(Math::Vector4d(_lightMaterial->GetColor().X(), _lightMaterial->GetColor().Y(), d, _lightMaterial->GetColor().W())); });
	connect(_ColorASpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=](double d) {_lightMaterial->SetColor(Math::Vector4d(_lightMaterial->GetColor().X(), _lightMaterial->GetColor().Y(), _lightMaterial->GetColor().Z(), d)); });

	connect(_IntensitySpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=](double d) {_lightMaterial->SetIntensity(d); });
	connect(_AmbiantSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [=](double d) {	_lightMaterial->SetAmbiant(d); });
}
