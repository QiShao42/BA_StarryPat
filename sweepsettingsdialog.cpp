#include "sweepsettingsdialog.h"
#include <QRegularExpression>
#include <QTextEdit>
#include <QFont>

SweepSettingsDialog::SweepSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
}

SweepSettingsDialog::~SweepSettingsDialog()
{
}

void SweepSettingsDialog::setupUi()
{
    this->setWindowTitle("困难扫荡设置");
    this->setFixedSize(600, 500);
    this->setModal(true);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    
    // 说明标签
    QLabel *infoLabel = new QLabel("为每个窗口配置困难扫荡", this);
    infoLabel->setStyleSheet("font-size: 10pt; color: #666;");
    mainLayout->addWidget(infoLabel);
    
    // 创建标签页控件
    tabWidget = new QTabWidget(this);
    tabWidget->setStyleSheet("QTabWidget::pane { "
                            "border: 2px solid #2196F3; "
                            "border-radius: 5px; "
                            "} "
                            "QTabBar::tab { "
                            "background-color: rgba(33, 150, 243, 100); "
                            "color: #333; "
                            "padding: 8px 20px; "
                            "margin-right: 2px; "
                            "border-top-left-radius: 5px; "
                            "border-top-right-radius: 5px; "
                            "} "
                            "QTabBar::tab:selected { "
                            "background-color: #2196F3; "
                            "color: white; "
                            "font-weight: bold; "
                            "}");
    
    // 为每个窗口标题创建标签页
    for (const QString &title : windowTitles) {
        QWidget *tabPage = createTabPage(title);
        tabWidget->addTab(tabPage, title);
    }
    
    mainLayout->addWidget(tabWidget);
    
    // 底部按钮行
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    
    // 使用说明按钮（放在左侧）
    helpButton = new QPushButton("使用说明", this);
    helpButton->setMinimumHeight(35);
    helpButton->setStyleSheet("QPushButton { "
                             "background-color: rgba(33, 150, 243, 200); "
                             "color: white; "
                             "border: 2px solid rgba(33, 150, 243, 255); "
                             "border-radius: 5px; "
                             "font-weight: bold; "
                             "padding: 5px 20px; "
                             "} "
                             "QPushButton:hover { "
                             "background-color: #2196F3; "
                             "} "
                             "QPushButton:pressed { "
                             "background-color: #1976D2; "
                             "}");
    connect(helpButton, &QPushButton::clicked, this, &SweepSettingsDialog::onHelpButtonClicked);
    buttonLayout->addWidget(helpButton);
    
    // 添加弹簧，将保存和取消按钮推到右侧
    buttonLayout->addStretch();
    
    saveButton = new QPushButton("保存", this);
    saveButton->setMinimumHeight(35);
    saveButton->setStyleSheet("QPushButton { "
                             "background-color: rgba(76, 175, 80, 200); "
                             "color: white; "
                             "border: 2px solid rgba(76, 175, 80, 255); "
                             "border-radius: 5px; "
                             "font-weight: bold; "
                             "padding: 5px 20px; "
                             "} "
                             "QPushButton:hover { "
                             "background-color: #4CAF50; "
                             "} "
                             "QPushButton:pressed { "
                             "background-color: #388E3C; "
                             "}");
    connect(saveButton, &QPushButton::clicked, this, &SweepSettingsDialog::onSaveButtonClicked);
    buttonLayout->addWidget(saveButton);
    
    cancelButton = new QPushButton("取消", this);
    cancelButton->setMinimumHeight(35);
    cancelButton->setStyleSheet("QPushButton { "
                               "background-color: rgba(158, 158, 158, 200); "
                               "color: white; "
                               "border: 2px solid rgba(158, 158, 158, 255); "
                               "border-radius: 5px; "
                               "font-weight: bold; "
                               "padding: 5px 20px; "
                               "} "
                               "QPushButton:hover { "
                               "background-color: #9E9E9E; "
                               "} "
                               "QPushButton:pressed { "
                               "background-color: #757575; "
                               "}");
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    buttonLayout->addWidget(cancelButton);
    
    mainLayout->addLayout(buttonLayout);
}

QWidget* SweepSettingsDialog::createTabPage(const QString &windowTitle)
{
    QWidget *page = new QWidget();
    QVBoxLayout *mainPageLayout = new QVBoxLayout(page);
    mainPageLayout->setSpacing(15);
    mainPageLayout->setContentsMargins(10, 10, 10, 10);
    
    TabWidgets widgets;
    
    // 启用困难扫荡复选框
    widgets.enabledCheckBox = new QCheckBox(QString("启用困难扫荡（窗口: %1）").arg(windowTitle), page);
    widgets.enabledCheckBox->setStyleSheet("QCheckBox { "
                                          "font-weight: bold; "
                                          "font-size: 11pt; "
                                          "color: #2196F3; "
                                          "}");
    mainPageLayout->addWidget(widgets.enabledCheckBox);
    
    // 扫荡关卡列表组
    QGroupBox *stageGroup = new QGroupBox("扫荡关卡列表", page);
    stageGroup->setStyleSheet("QGroupBox { "
                             "border: 2px solid #2196F3; "
                             "border-radius: 5px; "
                             "margin-top: 10px; "
                             "font-weight: bold; "
                             "color: #2196F3; "
                             "} "
                             "QGroupBox::title { "
                             "subcontrol-origin: margin; "
                             "subcontrol-position: top center; "
                             "padding: 0 5px; "
                             "}");
    QVBoxLayout *stageLayout = new QVBoxLayout(stageGroup);
    stageLayout->setSpacing(10);
    
    // 关卡列表
    widgets.stageList = new QListWidget(stageGroup);
    widgets.stageList->setStyleSheet("QListWidget { "
                                    "border: 1px solid #ddd; "
                                    "border-radius: 3px; "
                                    "background-color: white; "
                                    "} "
                                    "QListWidget::item { "
                                    "padding: 5px; "
                                    "} "
                                    "QListWidget::item:selected { "
                                    "background-color: #2196F3; "
                                    "color: white; "
                                    "}");
    stageLayout->addWidget(widgets.stageList);
    
    // 删除关卡按钮
    widgets.removeStageButton = new QPushButton("删除选中关卡", stageGroup);
    widgets.removeStageButton->setMinimumHeight(30);
    widgets.removeStageButton->setStyleSheet("QPushButton { "
                                            "background-color: rgba(244, 67, 54, 150); "
                                            "color: white; "
                                            "border: 1px solid #F44336; "
                                            "border-radius: 3px; "
                                            "padding: 5px 10px; "
                                            "} "
                                            "QPushButton:hover { "
                                            "background-color: #F44336; "
                                            "}");
    connect(widgets.removeStageButton, &QPushButton::clicked, this, &SweepSettingsDialog::onRemoveStageButtonClicked);
    stageLayout->addWidget(widgets.removeStageButton);
    
    mainPageLayout->addWidget(stageGroup);
    
    // 添加关卡组
    QGroupBox *addStageGroup = new QGroupBox("添加新关卡", page);
    addStageGroup->setStyleSheet("QGroupBox { "
                                "border: 2px solid #FF9800; "
                                "border-radius: 5px; "
                                "margin-top: 10px; "
                                "font-weight: bold; "
                                "color: #FF9800; "
                                "} "
                                "QGroupBox::title { "
                                "subcontrol-origin: margin; "
                                "subcontrol-position: top center; "
                                "padding: 0 5px; "
                                "}");
    QVBoxLayout *addStageLayout = new QVBoxLayout(addStageGroup);
    addStageLayout->setSpacing(10);
    
    // 参数输入行
    QHBoxLayout *paramsLayout = new QHBoxLayout();
    paramsLayout->setSpacing(15);
    
    // 任务索引
    QLabel *taskIndexLabel = new QLabel("任务索引:", addStageGroup);
    taskIndexLabel->setStyleSheet("font-weight: normal; color: #333;");
    paramsLayout->addWidget(taskIndexLabel);
    
    widgets.taskIndexSpinBox = new QSpinBox(addStageGroup);
    widgets.taskIndexSpinBox->setRange(0, 32);
    widgets.taskIndexSpinBox->setValue(0);
    widgets.taskIndexSpinBox->setMinimumWidth(60);
    widgets.taskIndexSpinBox->setStyleSheet("QSpinBox { "
                                           "border: 2px solid #FF9800; "
                                           "border-radius: 3px; "
                                           "padding: 3px; "
                                           "background-color: white; "
                                           "}");
    paramsLayout->addWidget(widgets.taskIndexSpinBox);
    
    paramsLayout->addSpacing(20);
    
    // 子任务索引
    QLabel *subTaskIndexLabel = new QLabel("子任务索引:", addStageGroup);
    subTaskIndexLabel->setStyleSheet("font-weight: normal; color: #333;");
    paramsLayout->addWidget(subTaskIndexLabel);
    
    widgets.subTaskIndexSpinBox = new QSpinBox(addStageGroup);
    widgets.subTaskIndexSpinBox->setRange(0, 2);
    widgets.subTaskIndexSpinBox->setValue(0);
    widgets.subTaskIndexSpinBox->setMinimumWidth(60);
    widgets.subTaskIndexSpinBox->setStyleSheet("QSpinBox { "
                                              "border: 2px solid #FF9800; "
                                              "border-radius: 3px; "
                                              "padding: 3px; "
                                              "background-color: white; "
                                              "}");
    paramsLayout->addWidget(widgets.subTaskIndexSpinBox);
    
    paramsLayout->addStretch();
    
    // 提示信息
    QLabel *hintLabel = new QLabel("(任务索引=负的任务序号, 子任务索引=关卡序号-1)", addStageGroup);
    hintLabel->setStyleSheet("font-weight: normal; color: #888; font-size: 9pt;");
    paramsLayout->addWidget(hintLabel);
    
    addStageLayout->addLayout(paramsLayout);
    
    // 添加按钮
    widgets.addStageButton = new QPushButton("添加关卡", addStageGroup);
    widgets.addStageButton->setMinimumHeight(30);
    widgets.addStageButton->setStyleSheet("QPushButton { "
                                         "background-color: rgba(255, 152, 0, 150); "
                                         "color: white; "
                                         "border: 1px solid #FF9800; "
                                         "border-radius: 3px; "
                                         "padding: 5px 10px; "
                                         "} "
                                         "QPushButton:hover { "
                                         "background-color: #FF9800; "
                                         "}");
    connect(widgets.addStageButton, &QPushButton::clicked, this, &SweepSettingsDialog::onAddStageButtonClicked);
    addStageLayout->addWidget(widgets.addStageButton);
    
    mainPageLayout->addWidget(addStageGroup);
    mainPageLayout->addStretch();
    
    // 保存控件引用
    tabWidgetsMap[windowTitle] = widgets;
    
    return page;
}

QListWidget* SweepSettingsDialog::getCurrentStageList()
{
    int index = tabWidget->currentIndex();
    if (index >= 0 && index < windowTitles.size()) {
        return tabWidgetsMap[windowTitles[index]].stageList;
    }
    return nullptr;
}

QCheckBox* SweepSettingsDialog::getCurrentEnabledCheckBox()
{
    int index = tabWidget->currentIndex();
    if (index >= 0 && index < windowTitles.size()) {
        return tabWidgetsMap[windowTitles[index]].enabledCheckBox;
    }
    return nullptr;
}

void SweepSettingsDialog::onAddStageButtonClicked()
{
    int index = tabWidget->currentIndex();
    if (index < 0 || index >= windowTitles.size()) return;
    
    QString windowTitle = windowTitles[index];
    TabWidgets &widgets = tabWidgetsMap[windowTitle];
    
    int taskIndex = widgets.taskIndexSpinBox->value();
    int subTaskIndex = widgets.subTaskIndexSpinBox->value();
    
    // 添加到列表
    QString stageText = QString("任务%1-关卡%2").arg(taskIndex).arg(subTaskIndex + 1);
    widgets.stageList->addItem(stageText);
}

void SweepSettingsDialog::onRemoveStageButtonClicked()
{
    QListWidget *stageList = getCurrentStageList();
    if (!stageList) return;
    
    QListWidgetItem *item = stageList->currentItem();
    if (item) {
        delete stageList->takeItem(stageList->row(item));
    }
}

void SweepSettingsDialog::onSaveButtonClicked()
{
    this->accept();
}

void SweepSettingsDialog::onHelpButtonClicked()
{
    QDialog *helpDialog = new QDialog(this);
    helpDialog->setWindowTitle("困难扫荡使用说明");
    helpDialog->setFixedSize(550, 450);
    
    QVBoxLayout *layout = new QVBoxLayout(helpDialog);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);
    
    // 标题
    QLabel *titleLabel = new QLabel("困难扫荡功能使用说明", helpDialog);
    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("QLabel { color: #2196F3; }");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);
    
    // 说明内容
    QTextEdit *contentEdit = new QTextEdit(helpDialog);
    contentEdit->setReadOnly(true);
    contentEdit->setStyleSheet("QTextEdit { "
                              "border: 1px solid #ddd; "
                              "border-radius: 5px; "
                              "padding: 10px; "
                              "background-color: #f9f9f9; "
                              "font-size: 10pt; "
                              "}");
    
    QString helpText = 
        // "<h3 style='color: #2196F3;'>什么是困难扫荡？</h3>"
        // "<p>困难扫荡功能用于自动扫荡游戏中的困难任务关卡。</p>"
        
        "<h3 style='color: #2196F3;'>任务索引说明</h3>"
        "<p><b>任务索引</b>是指到达当前最高任务关卡后，需要<b>往左返回的次数</b>。</p>"
        
        "<h3 style='color: #2196F3;'>使用示例</h3>"
        "<p>假设当前游戏中最高只有 <b>26 关</b>：</p>"
        "<ul>"
        "<li><b>任务0-关卡1</b>：表示扫荡 <b>第26任务的第1个关卡</b></li>"
        "<li><b>任务1-关卡2</b>：表示扫荡 <b>第25任务的第2个关卡</b></li>"
        "<li><b>任务2-关卡3</b>：表示扫荡 <b>第24任务的第3个关卡</b></li>"
        "</ul>"
        
        // "<h3 style='color: #2196F3;'>如何设置</h3>"
        // "<ol>"
        // "<li>勾选<b>启用困难扫荡</b>复选框</li>"
        // "<li>输入<b>任务索引</b>（往左返回几个任务）</li>"
        // "<li>输入<b>子任务索引</b>（关卡序号-1，如关卡1输入0）</li>"
        // "<li>点击<b>添加关卡</b>按钮</li>"
        // "<li>重复步骤2-4添加更多关卡</li>"
        // "<li>点击<b>保存</b>按钮保存设置</li>"
        // "</ol>"
        
        "<h3 style='color: #FF9800;'>注意事项</h3>"
        "<ul>"
        "<li>子任务索引从0开始，索引0对应关卡1，索引1对应关卡2，以此类推</li>"
        "<li>当开放27区域时，任务0-关卡1变为第27任务的第1个关卡（预计是这样）</li>"
        "<li>检查机制保护，扫荡过程中不会使用清辉石</li>"
        "</ul>";
    
    contentEdit->setHtml(helpText);
    layout->addWidget(contentEdit);
    
    // 关闭按钮
    QPushButton *closeButton = new QPushButton("关闭", helpDialog);
    closeButton->setMinimumHeight(35);
    closeButton->setStyleSheet("QPushButton { "
                              "background-color: #2196F3; "
                              "color: white; "
                              "border: none; "
                              "border-radius: 5px; "
                              "font-weight: bold; "
                              "padding: 5px 20px; "
                              "} "
                              "QPushButton:hover { "
                              "background-color: #1976D2; "
                              "} "
                              "QPushButton:pressed { "
                              "background-color: #0D47A1; "
                              "}");
    connect(closeButton, &QPushButton::clicked, helpDialog, &QDialog::accept);
    layout->addWidget(closeButton);
    
    helpDialog->exec();
    delete helpDialog;
}

WindowSweepConfig SweepSettingsDialog::getSweepConfig(const QString &windowTitle) const
{
    WindowSweepConfig config;
    config.enabled = false;
    
    if (tabWidgetsMap.contains(windowTitle)) {
        const TabWidgets &widgets = tabWidgetsMap[windowTitle];
        
        // 获取启用状态
        config.enabled = widgets.enabledCheckBox->isChecked();
        
        // 获取关卡列表
        for (int i = 0; i < widgets.stageList->count(); i++) {
            QString stageText = widgets.stageList->item(i)->text();
            // 解析 "任务X-关卡Y" 格式
            QRegularExpression re("任务(\\d+)-关卡(\\d+)");
            QRegularExpressionMatch match = re.match(stageText);
            if (match.hasMatch()) {
                SweepStageConfig stageConfig;
                stageConfig.taskIndex = match.captured(1).toInt();
                stageConfig.subTaskIndex = match.captured(2).toInt() - 1;  // 关卡序号-1
                config.stages.append(stageConfig);
            }
        }
    }
    
    return config;
}

void SweepSettingsDialog::setSweepConfig(const QString &windowTitle, const WindowSweepConfig &config)
{
    if (tabWidgetsMap.contains(windowTitle)) {
        TabWidgets &widgets = tabWidgetsMap[windowTitle];
        
        // 设置启用状态
        widgets.enabledCheckBox->setChecked(config.enabled);
        
        // 设置关卡列表
        widgets.stageList->clear();
        for (const SweepStageConfig &stage : config.stages) {
            QString stageText = QString("任务%1-关卡%2").arg(stage.taskIndex).arg(stage.subTaskIndex + 1);
            widgets.stageList->addItem(stageText);
        }
    }
}

QHash<QString, WindowSweepConfig> SweepSettingsDialog::getAllSweepConfigs() const
{
    QHash<QString, WindowSweepConfig> configs;
    for (const QString &title : windowTitles) {
        configs[title] = getSweepConfig(title);
    }
    return configs;
}

void SweepSettingsDialog::setAllSweepConfigs(const QHash<QString, WindowSweepConfig> &configs)
{
    for (auto it = configs.constBegin(); it != configs.constEnd(); ++it) {
        setSweepConfig(it.key(), it.value());
    }
}

void SweepSettingsDialog::setWindowTitles(const QStringList &titles)
{
    // 如果标题列表没有变化，不需要重建
    if (titles == windowTitles) {
        return;
    }
    
    // 保存旧的设置
    QHash<QString, WindowSweepConfig> oldConfigs = getAllSweepConfigs();
    
    // 更新窗口标题列表
    windowTitles = titles;
    
    // 清空现有的标签页
    while (tabWidget->count() > 0) {
        QWidget *widget = tabWidget->widget(0);
        tabWidget->removeTab(0);
        delete widget;
    }
    tabWidgetsMap.clear();
    
    // 为新的窗口标题创建标签页
    for (const QString &title : windowTitles) {
        QWidget *tabPage = createTabPage(title);
        tabWidget->addTab(tabPage, title);
    }
    
    // 恢复旧的设置（如果存在）
    for (const QString &title : windowTitles) {
        if (oldConfigs.contains(title)) {
            setSweepConfig(title, oldConfigs[title]);
        }
    }
}
